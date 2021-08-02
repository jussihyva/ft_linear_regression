/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/02 08:09:08 by jkauppi          ###   ########.fr       */
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
	ft_lstadd(&linear_regression_data->data_record_lst, elem);
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
							double **theta_values,
							t_variable *predicted_price)
{
	t_min_max_value		*min_max_value;

	min_max_value = &predicted_price->min_max_value;
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
	t_variable					*input_variable;
	t_variable					*measured_variable;
	t_gradient_descent_data		*gradient_descent_data;

	input_variable = &linear_regression_data->input_variables.km;
	measured_variable = &linear_regression_data->measured_variables.price;
	pre_process_input_variables(linear_regression_data);
	gradient_descent_data = unknown_variables_iterate_values(input_variable,
			measured_variable);
	estimate_prize(input_variable, measured_variable,
		(double **)gradient_descent_data->theta->values,
		&linear_regression_data->predicted_price);
	statistics_create_records(&statistics->stat_counters_lst,
		linear_regression_data);
	stat_set_end_time(statistics);
	if (statistics->stat_counters_lst)
		statistics_save_records(statistics);
	ft_vector_remove(&gradient_descent_data->theta);
	ft_memdel((void **)&gradient_descent_data);
	return ;
}

void	linear_regression_data_release(
							t_lin_reg_data **linear_regression_data)
{
	if ((*linear_regression_data)->data_record_lst)
	{
		ft_lstdel(&(*linear_regression_data)->data_record_lst,
			statistics_release_record);
		ft_memdel((void **)&(*linear_regression_data)->data_record_lst);
	}
	variable_remove(&(*linear_regression_data)->predicted_price);
	variable_remove(&(*linear_regression_data)->input_variables.km);
	variable_remove(&(*linear_regression_data)->measured_variables.price);
	ft_memdel((void **)linear_regression_data);
	return ;
}
