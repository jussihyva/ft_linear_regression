/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/29 22:25:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	linear_regression_add_data_record(
							t_lin_reg_data *linear_regression_data,
							t_data_record *data_record)
{
	t_list						*elem;

	linear_regression_data->num_of_records++;
	elem = ft_lstnew(&data_record, sizeof(data_record));
	ft_lstadd(linear_regression_data->data_record_lst, elem);
	return ;
}

static void	release_data_record(void *content, size_t size)
{
	t_data_record	**data_record;

	(void)size;
	data_record = content;
	ft_memdel((void **)data_record);
	ft_memdel((void **)&content);
	return ;
}

static void	save_result(t_statistics *statistics)
{
	char				*body;
	t_list				*elem;
	t_stat_counters		*stat_counters;

	statistics->data_type = "input";
	statistics->id = 0;
	elem = *statistics->stat_counters_lst;
	while (elem)
	{
		stat_counters = (t_stat_counters *)elem->content;
		body = create_influxdb_query_string(stat_counters,
				statistics->end_time, statistics->data_type, statistics->id);
		ft_influxdb_write(statistics->connection, body, "Hive");
		ft_strdel(&body);
		elem = elem->next;
		statistics->id++;
	}
	return ;
}

static void	create_statistics(t_list **stat_counters_lst,
										t_lin_reg_data *linear_regression_data)
{
	size_t				i;
	t_stat_counters		stat_counters;
	t_list				*elem;
	t_variable			*input_variable;
	t_variable			*measured_variable;

	input_variable = &linear_regression_data->input_variables.km;
	measured_variable = &linear_regression_data->measured_variables.price;
	i = -1;
	while (++i < linear_regression_data->num_of_records)
	{
		stat_counters.counter_names[E_INDEPENDENT]
			= ft_strdup("independent=%d");
		stat_counters.counter_names[E_DEPENDENT]
			= ft_strdup("dependent=%d");
		stat_counters.counter_names[E_PREDICTED_PRICE]
			= ft_strdup("predicted_price=%d");
		stat_counters.is_active[E_INDEPENDENT] = 1;
		stat_counters.is_active[E_DEPENDENT] = 1;
		stat_counters.is_active[E_PREDICTED_PRICE] = 1;
		stat_counters.value[E_INDEPENDENT]
			= ((int *)input_variable->values)[i];
		stat_counters.value[E_DEPENDENT]
			= ((int *)measured_variable->values)[i];
		stat_counters.value[E_PREDICTED_PRICE]
			= ((double *)linear_regression_data->predicted_price.values)[i];
		elem = ft_lstnew(&stat_counters, sizeof(stat_counters));
		ft_lstadd(stat_counters_lst, elem);
	}
	return ;
}

static void	calculate_prices(t_variable *input_variable,
							t_variable *predicted_price, double **theta_values)
{
	size_t				i;

	i = -1;
	while (++i < input_variable->size)
	{
		((double **)predicted_price->normalized_values->values)[i][0]
			= theta_values[0][0] + theta_values[1][0]
			* ((double **)input_variable->normalized_values->values)[i][0];
		((double *)predicted_price->values)[i]
			= *(double *)predicted_price->min_max_value.min_value
			+ (*(double *)predicted_price->min_max_value.range
				* ((double **)predicted_price->normalized_values
					->values)[i][0]);
	}
	return ;
}

static void	estimate_prize(t_variable *input_variable,
							t_variable *measured_variable,
							t_gradient_descent_data *gradient_descent_data,
							t_variable *predicted_price)
{
	double				**theta_values;
	t_min_max_value		*min_max_value;

	min_max_value = &predicted_price->min_max_value;
	theta_values = (double **)gradient_descent_data->theta->values;
	initalize_variable(predicted_price, input_variable->size, sizeof(double));
	*(double *)min_max_value->min_value
		= (double)(*(int *)measured_variable->min_max_value.min_value);
	*(double *)min_max_value->max_value
		= *(int *)measured_variable->min_max_value.max_value;
	*(double *)min_max_value->range
		= *(int *)measured_variable->min_max_value.range;
	predicted_price->normalized_values = ft_vector_create(sizeof(double),
			input_variable->size);
	calculate_prices(input_variable, predicted_price, theta_values);
	return ;
}

void	create_linear_regression_model(t_lin_reg_data *linear_regression_data,
													t_statistics *statistics)
{
	t_gradient_descent_data		gradient_descent_data;
	t_matrix					*new_theta;
	t_variable					*input_variable;
	t_variable					*measured_variable;
	size_t						i;

	new_theta = ft_vector_create(sizeof(double), 2);
	gradient_descent_data.alpha = 0.1;
	gradient_descent_data.theta = theta_initialize();
	input_variable = &linear_regression_data->input_variables.km;
	measured_variable = &linear_regression_data->measured_variables.price;
	pre_process_input_variables(linear_regression_data);
	FT_LOG_INFO("ALPHA: %f", gradient_descent_data.alpha);
	i = -1;
	while (++i < 1000)
	{
		calculate_new_theta(&gradient_descent_data, input_variable,
			measured_variable, (double **)new_theta->values);
		((double **)gradient_descent_data.theta->values)[0][0]
			= ((double **)new_theta->values)[0][0];
		((double **)gradient_descent_data.theta->values)[1][0]
			= ((double **)new_theta->values)[1][0];
	}
	estimate_prize(input_variable, measured_variable, &gradient_descent_data,
		&linear_regression_data->predicted_price);
	create_statistics(statistics->stat_counters_lst, linear_regression_data);
	stat_set_end_time(statistics);
	if (*statistics->stat_counters_lst)
		save_result(statistics);
	ft_vector_remove(&gradient_descent_data.theta);
	ft_vector_remove(&new_theta);
	return ;
}

void	linear_regression_data_release(
							t_lin_reg_data **linear_regression_data)
{
	ft_lstdel((*linear_regression_data)->data_record_lst, release_data_record);
	ft_memdel((void **)&(*linear_regression_data)->data_record_lst);
	variable_remove(&(*linear_regression_data)->predicted_price);
	variable_remove(&(*linear_regression_data)->input_variables.km);
	variable_remove(&(*linear_regression_data)->measured_variables.price);
	ft_memdel((void **)linear_regression_data);
	return ;
}
