/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coefficient_of_determination.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:58:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 13:32:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static double	variable_denormalize_int(t_min_max_value *min_max_value,
													double normalized_value)
{
	double		denormalized_value;

	denormalized_value = (normalized_value * *(int *)min_max_value->range)
		+ *(int *)min_max_value->min_value;
	return (denormalized_value);
}

void	coefficient_of_determination_calculate(t_lin_reg *linear_regression)
{
	t_variable	*price;
	double		sum;
	double		sum_of_error_squared;
	t_matrix	*average;
	t_matrix	*average_denormalized;
	t_matrix	*error;
	t_matrix	*error_squared;

	price = &linear_regression->measured_variables.price;
	ft_printf("%u\n", linear_regression->predicted_price
		.normalized_values->size.rows);
	ft_printf("%u\n", linear_regression->predicted_price
		.normalized_values->size.columns);
	sum = ft_matrix_sum(price->normalized_values);
	average = ft_vector_create(sizeof(double), 1);
	average_denormalized = ft_vector_create(sizeof(double), 1);
	error = ft_vector_create(sizeof(double), price->size);
	error_squared = ft_vector_create(sizeof(double), price->size);
	((double **)average->values)[0][0]
		= sum / linear_regression->measured_variables.price.size;
	((double **)average_denormalized->values)[0][0]
		= variable_denormalize_int(&price->min_max_value,
			((double **)average->values)[0][0]);
	ft_printf("AVERAGE: %.4f\n",
		((double **)average->values)[0][0]);
	ft_matrix_subtract_vector_double(price->normalized_values, average, error);
	ft_matrix_multiply_vector_double(error, error, error_squared);
	ft_matrix_print("PRICE", price->normalized_values, E_DOUBLE);
	ft_matrix_print("ERROR", error, E_DOUBLE);
	ft_matrix_print("ERROR SQUARED", error_squared, E_DOUBLE);
	sum_of_error_squared = ft_matrix_sum(error_squared);
	ft_printf("SUM OF ERROR SQUARED: %.4f\n", sum_of_error_squared);
	return ;
}
