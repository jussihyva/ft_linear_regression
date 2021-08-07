/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coefficient_of_determination.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:58:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/07 10:39:25 by jkauppi          ###   ########.fr       */
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

static t_matrix	*average_calculate(t_variable *variable)
{
	t_matrix	*average;
	double		sum;

	sum = ft_matrix_sum(variable->normalized_values);
	average = ft_vector_create(sizeof(double), 1);
	((double **)average->values)[0][0] = sum / variable->size;
	return (average);
}

static t_reg_error	*reg_error_calulate(t_variable *variable)
{
	t_reg_error		*reg_error;
	t_matrix		*average;

	reg_error = (t_reg_error *)ft_memalloc(sizeof(*reg_error));
	reg_error->error = ft_vector_create(sizeof(double), variable->size);
	average = average_calculate(variable);
	variable_denormalize_int(&variable->min_max_value,
		((double **)average->values)[0][0]);
	ft_printf("AVERAGE: %.4f\n", ((double **)average->values)[0][0]);
	ft_matrix_subtract_vector_double(variable->normalized_values, average,
		reg_error->error);
	reg_error->error_squares = ft_vector_create(sizeof(double), variable->size);
	ft_matrix_multiply_vector_double(reg_error->error, reg_error->error,
		reg_error->error_squares);
	// ft_matrix_print("ERROR SQUARED", reg_error->error_squares, E_DOUBLE);
	reg_error->error_sum_of_squares = ft_matrix_sum(reg_error->error_squares);
	ft_matrix_remove(&average);
	return (reg_error);
}

void	coefficient_of_determination_calculate(t_lin_reg *linear_regression)
{
	t_variable	*price;

	price = &linear_regression->measured_variables.price;
	linear_regression->reg_error = reg_error_calulate(price);
	// ft_matrix_print("PRICE", price->normalized_values, E_DOUBLE);
	// ft_matrix_print("ERROR", linear_regression->reg_error->error, E_DOUBLE);
	ft_printf("ERROR SUM OF SQUARES: %.4f\n",
		linear_regression->reg_error->error_sum_of_squares);
	ft_printf("RESIDUAL SUM OF SQUARES: %.4f\n",
		linear_regression->reg_residual.residual_sum_of_squares);
	ft_printf("r2: %f\n", 1 - linear_regression->reg_residual
		.residual_sum_of_squares / linear_regression->reg_error
		->error_sum_of_squares);
	return ;
}
