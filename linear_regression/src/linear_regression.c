/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/03 11:49:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

double	calculate_price(int km, double theta0, double theta1)
{
	double		price;

	price = theta0 + (theta1 * km);
	return (price);
}

static void	calculate_prices(t_variable *input_variable,
							t_variable *predicted_price, double **theta_values)
{
	size_t		i;

	i = -1;
	while (++i < input_variable->size)
	{
		((double *)predicted_price->values)[i]
			= calculate_price(((int *)input_variable->values)[i],
				theta_values[0][0], theta_values[1][0]);
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

void	create_linear_regression_model(t_lin_reg *linear_regression,
													t_statistics *statistics)
{
	t_variable					*input_variable;
	t_variable					*measured_variable;
	t_gradient_descent			*gradient_descent;
	double						*theta_values;

	theta_values = linear_regression->theta_values;
	input_variable = &linear_regression->input_variables.km;
	measured_variable = &linear_regression->measured_variables.price;
	pre_process_input_variables(linear_regression);
	gradient_descent = unknown_variables_iterate_values(input_variable,
			measured_variable);
	save_unknown_variables((double **)gradient_descent->theta->values);
	estimate_prize(input_variable, measured_variable,
		(double **)gradient_descent->theta->values,
		&linear_regression->predicted_price);
	statistics_create_records(&statistics->stat_counters_lst,
		linear_regression);
	stat_set_end_time(statistics);
	theta_values[0] = ((double **)gradient_descent->theta->values)[0][0];
	theta_values[1] = ((double **)gradient_descent->theta->values)[1][0];
	ft_vector_remove(&gradient_descent->theta);
	ft_memdel((void **)&gradient_descent);
	return ;
}

void	linear_regression_release(
							t_lin_reg **linear_regression)
{
	if ((*linear_regression)->dataset->data_record_lst)
	{
		ft_lstdel(&(*linear_regression)->dataset->data_record_lst,
			statistics_release_record);
		ft_memdel((void **)&(*linear_regression)->dataset
			->data_record_lst);
	}
	ft_memdel((void **)&(*linear_regression)->dataset);
	variable_remove(&(*linear_regression)->predicted_price);
	variable_remove(&(*linear_regression)->input_variables.km);
	variable_remove(&(*linear_regression)->measured_variables.price);
	ft_memdel((void **)&(*linear_regression)->theta_values);
	ft_memdel((void **)linear_regression);
	return ;
}
