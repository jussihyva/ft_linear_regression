/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:02:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/27 08:10:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_matrix	*theta_initialize(void)
{
	t_matrix	*theta;

	theta = (t_matrix *)ft_memalloc(sizeof(*theta));
	theta->size.rows = 2;
	theta->size.columns = 1;
	theta->values = ft_memalloc(sizeof(*theta->values) * 2);
	theta->values[0] = ft_memalloc(sizeof(double));
	theta->values[1] = ft_memalloc(sizeof(double));
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

void	print_error_result(size_t size, double **response_variable,
							t_error_data *error_data, double new_theta[2][1])
{
	size_t			i;

	i = -1;
	printf("response_variable: ");
	while (++i < size)
		printf("%6.3f ", response_variable[i][0]);
	printf("\n");
	i = -1;
	printf("            Error: ");
	while (++i < size)
		printf("%6.3f ", ((double **)error_data->error->values)[i][0]);
	printf("\n");
	ft_printf("Error SUM: %f\n", error_data->error_sum);
	ft_printf("New theta[0]: %f\n", new_theta[0][0]);
	return ;
}

void	calculate_error(t_gradient_descent_data *gradient_descent_data,
						t_variable *input_variable,
						t_variable *measured_variable,
						double new_theta[2][1])
{
	t_matrix		*response_variable;
	t_error_data	error_data;
	double			alpha;
	double			**theta_values;
	double			range;

	alpha = gradient_descent_data->alpha;
	theta_values = (double **)gradient_descent_data->theta->values;
	range = (double)(*(int *)measured_variable->min_max_value.max_value - *(int *)measured_variable->min_max_value.min_value);
	printf("Theta: %f  %f\n", *(int *)measured_variable->min_max_value.min_value
		+ range * theta_values[0][0], theta_values[1][0]);
	response_variable = ft_vector_create(sizeof(double), input_variable->size);
	ft_matrix_dot_vector_double(input_variable->matrix, gradient_descent_data->theta,
		response_variable);
	error_data.error = ft_vector_create(sizeof(double), input_variable->size);
	ft_matrix_subtrack_vector_double(response_variable,
		measured_variable->normalized_values, error_data.error);
	error_data.error_sum = ft_matrix_sum(error_data.error);
	new_theta[0][0] = theta_values[0][0] - (alpha * error_data.error_sum)
		/ input_variable->size;
	// print_error_result(input_variable->matrix_size.rows, response_variable,
	// 	&error_data, new_theta);
	ft_matrix_dot_vector_double(input_variable->normalized_values,
		error_data.error, response_variable);
	// print_error_result(input_variable->matrix_size.rows, response_variable,
	// 	&error_data, new_theta);
	error_data.error_sum = ft_matrix_sum(response_variable);
	new_theta[1][0] = theta_values[1][0] - (alpha * error_data.error_sum)
		/ input_variable->size;
	ft_vector_remove(&error_data.error);
	ft_vector_remove(&response_variable);
	return ;
}
