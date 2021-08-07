/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:02:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/07 10:38:37 by jkauppi          ###   ########.fr       */
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

void	calculate_new_theta(t_gradient_descent *gradient_descent,
					t_variable *input_variable, t_variable *measured_variable,
					double **new_theta_values)
{
	t_matrix		*predicted;
	t_matrix		*normalized_values_transposed;
	double			alpha;
	double			**theta_values;
	t_reg_residual	reg_residual;
	double			residual_sum;
	double			predicted_sum;

	alpha = gradient_descent->alpha;
	theta_values = (double **)gradient_descent->theta_normalized->values;
	reg_residual.residual = ft_vector_create(sizeof(double),
			input_variable->size);
	reg_residual.residual_squares = ft_vector_create(sizeof(double),
			input_variable->size);
	residual_calculate(input_variable, gradient_descent->theta_normalized,
		measured_variable, &reg_residual);
	residual_sum = ft_matrix_sum(reg_residual.residual);
	new_theta_values[0][0] = theta_values[0][0] - (alpha * residual_sum)
		/ input_variable->size;
	normalized_values_transposed
		= ft_matrix_transpose(input_variable->normalized_values);
	predicted = ft_vector_create(sizeof(double),
			normalized_values_transposed->size.rows);
	ft_matrix_dot_vector_double(normalized_values_transposed,
		reg_residual.residual, predicted);
	predicted_sum = ft_matrix_sum(predicted);
	new_theta_values[1][0] = theta_values[1][0] - (alpha * predicted_sum)
		/ input_variable->size;
	ft_vector_remove(&reg_residual.residual);
	ft_vector_remove(&reg_residual.residual_squares);
	ft_vector_remove(&predicted);
	ft_matrix_remove(&normalized_values_transposed);
}
