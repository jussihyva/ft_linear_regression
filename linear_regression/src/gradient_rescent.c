/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:02:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/25 12:06:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

double	**theta_initialize(void)
{
	double			**theta;

	theta = (double **)ft_memalloc(sizeof(*theta) * 2);
	theta[0] = (double *)ft_memalloc(sizeof(**theta));
	theta[1] = (double *)ft_memalloc(sizeof(**theta));
	theta[0][0] = 0.0;
	theta[1][0] = -0.0;
	return (theta);
}

double	**matrix_initialize(t_variable *variable)
{
	static size_t	num_of_columns = 2;
	double			**matrix;
	size_t			i;

	matrix = (double **)ft_memalloc(sizeof(*matrix) * variable->size);
	variable->matrix_size.rows = variable->size;
	variable->matrix_size.columns = num_of_columns;
	i = -1;
	while (++i < variable->size)
	{
		matrix[i] = (double *)ft_memalloc(sizeof(*matrix[i]) * num_of_columns);
		matrix[i][0] = 1;
		matrix[i][1] = variable->normalized_values[i][0];
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
		printf("%6.3f ", error_data->error[i][0]);
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
	static size_t	columns = 1;
	double			**response_variable;
	t_error_data	error_data;
	double			alpha;
	double			**theta;
	double			range;

	alpha = gradient_descent_data->alpha;
	theta = gradient_descent_data->theta;
	range = (double)(*(int *)measured_variable->min_max_value.max_value - *(int *)measured_variable->min_max_value.min_value);
	printf("Theta: %f  %f\n", *(int *)measured_variable->min_max_value.min_value + range * theta[0][0], theta[1][0]);
	response_variable = (double **)ft_vector_create(sizeof(double),
			input_variable->matrix_size.rows);
	ft_matrix_dot_vector_double(&input_variable->matrix_size,
		input_variable->matrix, theta, response_variable);
	input_variable->matrix_size.columns = columns;
	error_data.error = (double **)ft_vector_create(sizeof(double),
			input_variable->matrix_size.rows);
	ft_matrix_subtrack_vector_double(&input_variable->matrix_size,
		response_variable, measured_variable->normalized_values,
		error_data.error);
	error_data.error_sum = ft_matrix_sum(&input_variable->matrix_size,
			error_data.error);
	new_theta[0][0] = theta[0][0] - (alpha * error_data.error_sum)
		/ input_variable->matrix_size.rows;
	// print_error_result(input_variable->matrix_size.rows, response_variable,
	// 	&error_data, new_theta);
	ft_matrix_dot_vector_double(&input_variable->matrix_size,
		input_variable->normalized_values, error_data.error, response_variable);
	// print_error_result(input_variable->matrix_size.rows, response_variable,
	// 	&error_data, new_theta);
	error_data.error_sum = ft_matrix_sum(&input_variable->matrix_size,
			response_variable);
	new_theta[1][0] = theta[1][0] - (alpha * error_data.error_sum)
		/ input_variable->matrix_size.rows;
	ft_vector_remove((void ***)&error_data.error,
		input_variable->matrix_size.rows);
	ft_vector_remove((void ***)&response_variable,
		input_variable->matrix_size.rows);
	input_variable->matrix_size.columns = 2;
	return ;
}
