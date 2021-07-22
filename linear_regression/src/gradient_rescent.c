/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:02:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/22 11:21:46 by jkauppi          ###   ########.fr       */
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
	theta[1][0] = 0.0;
	return (theta);
}

double	**matrix_initialize(t_variable *km, t_matrix_size *matrix_size)
{
	static size_t	num_of_columns = 2;
	double			**matrix;
	size_t			i;

	matrix = (double **)ft_memalloc(sizeof(*matrix) * km->size);
	matrix_size->rows = km->size;
	matrix_size->columns = num_of_columns;
	i = -1;
	while (++i < km->size)
	{
		matrix[i] = (double *)ft_memalloc(sizeof(*matrix[i]) * num_of_columns);
		matrix[i][0] = 1;
		matrix[i][1] = km->normalized_values[i][0];
	}
	return (matrix);
}

void	calculate_error(double **theta, double **matrix,
					t_matrix_size *matrix_size, t_variable *measured_variable)
{
	static size_t	columns = 1;
	static double	alpha = 0.8;
	size_t			i;
	double			**response_variable;
	double			**error;
	double			error_sum;
	double			new_theta[2][1];

	response_variable = (double **)ft_create_vector(sizeof(double),
			matrix_size->rows);
	ft_matrix_dot_vector_double(matrix_size, matrix, theta, response_variable);
	matrix_size->columns = columns;
	error = (double **)ft_create_vector(sizeof(double),
			matrix_size->rows);
	ft_matrix_subtrack_vector_double(matrix_size, response_variable,
		measured_variable->normalized_values, error);
	error_sum = ft_matrix_sum(matrix_size, error);
	new_theta[0][0] = theta[0][0] - (alpha * error_sum) / matrix_size->rows;
	i = -1;
	printf("response_variable: ");
	while (++i < matrix_size->rows)
		printf("%6.3f ", response_variable[i][0]);
	printf("\n");
	i = -1;
	printf("            Error: ");
	while (++i < matrix_size->rows)
		printf("%6.3f ", error[i][0]);
	printf("\n");
	ft_printf("Error SUM: %f\n", error_sum);
	ft_printf("New theta[0]: %f\n", new_theta[0][0]);
	ft_memdel((void **)&error[0]);
	ft_memdel((void **)&error);
	return ;
}
