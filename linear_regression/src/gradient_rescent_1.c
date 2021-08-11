/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:02:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 14:30:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_matrix	*theta_initialize(void)
{
	t_matrix	*theta;

	theta = ft_vector_create(sizeof(double), 2);
	((double **)theta->values)[0][0] = 0.0;
	((double **)theta->values)[1][0] = -0.0;
	return (theta);
}

t_matrix	*matrix_initialize(t_variable *variable)
{
	static size_t	num_of_columns = 2;
	t_matrix		*matrix;
	size_t			i;

	matrix = (t_matrix *)ft_memalloc(sizeof(*matrix));
	matrix->values = ft_memalloc(sizeof(*matrix->values) * variable->size);
	matrix->size.rows = variable->size;
	matrix->size.columns = num_of_columns;
	i = -1;
	while (++i < variable->size)
	{
		matrix->values[i] = ft_memalloc(sizeof(double) * num_of_columns);
		((double **)matrix->values)[i][0] = (double)1;
		((double **)matrix->values)[i][1]
			= ((double **)variable->normalized_values->values)[i][0];
	}
	return (matrix);
}

static double	calculate_theta_1_delta(t_variable *input_variable,
											t_matrix *residual, double alpha)
{
	t_matrix		*normalized_values_transposed;
	t_matrix		*predicted;
	double			predicted_sum;
	double			theta1_delta;

	normalized_values_transposed
		= ft_matrix_transpose(input_variable->normalized_values);
	predicted = ft_vector_create(sizeof(double),
			normalized_values_transposed->size.rows);
	ft_matrix_dot_vector_double(normalized_values_transposed, residual,
		predicted);
	predicted_sum = ft_matrix_sum(predicted);
	theta1_delta = (alpha * predicted_sum) / input_variable->size;
	ft_vector_remove(&predicted);
	ft_matrix_remove(&normalized_values_transposed);
	return (theta1_delta);
}

double	calculate_new_theta(t_gradient_descent *gradient_descent,
					t_variable *input_variable, t_variable *measured_variable)
{
	double				**theta_values;
	t_reg_residual		*reg_residual;
	double				prev_residual_sum_of_squares;
	double				cost_change;

	reg_residual = &gradient_descent->reg_residual;
	prev_residual_sum_of_squares = reg_residual->residual_sum_of_squares;
	theta_values = (double **)gradient_descent->theta_normalized->values;
	residual_calculate(input_variable, gradient_descent->theta_normalized,
		measured_variable, reg_residual);
	reg_residual->residual_sum = ft_matrix_sum(reg_residual->residual);
	theta_values[0][0] -= (gradient_descent->alpha
			* reg_residual->residual_sum) / input_variable->size;
	theta_values[1][0] -= calculate_theta_1_delta(input_variable,
			reg_residual->residual, gradient_descent->alpha);
	cost_change = prev_residual_sum_of_squares
		- reg_residual->residual_sum_of_squares;
	FT_LOG_TRACE("DIFF: %.10f", cost_change);
	FT_LOG_TRACE("Sum of residual: %f(%f)",
		reg_residual->residual_sum_of_squares, reg_residual->residual_sum);
	return (cost_change);
}
