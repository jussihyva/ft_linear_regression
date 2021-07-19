/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:02:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/19 18:29:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

double	*theta_initialize(void)
{
	double			*theta;

	theta = (double *)ft_memalloc(sizeof(*theta) * 2);
	theta[0] = 0.4;
	theta[1] = -0.8;
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
		matrix[i][1] = km->normalized_values[i];
	}
	return (matrix);
}

void	calculate_error(double *theta, double **matrix,
													t_matrix_size *matrix_size)
{
	size_t			i;
	double			*error;

	error = (double *)ft_memalloc(sizeof(*error) * matrix_size->rows);
	ft_matrix_x_vector_double(matrix_size, matrix, theta, error);
	i = -1;
	printf("Error: ");
	while (++i < matrix_size->rows)
	{
		printf("%.3f ", error[i]);
	}
	printf("\n");
	return ;
}
