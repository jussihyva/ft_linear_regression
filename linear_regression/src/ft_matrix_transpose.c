/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transpose.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 10:00:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/26 10:25:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

double	**ft_matrix_transpose(t_matrix_size *matrix_size, double **matrix)
{
	double		**new_matrix;
	size_t		i;
	size_t		j;

	new_matrix = (double **)ft_memalloc(sizeof(*matrix) * matrix_size->columns);
	i = -1;
	while (++i < matrix_size->columns)
	{
		new_matrix[i]
			= (double *)ft_memalloc(sizeof(**matrix) * matrix_size->rows);
		j = -1;
		while (++j < matrix_size->rows)
		{
			new_matrix[i][j] = matrix[j][i];
		}
	}
	return (new_matrix);
}
