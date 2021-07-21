/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_subtrack_vector_double.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:31:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/21 13:59:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	ft_matrix_subtrack_vector_double(t_matrix_size *matrix_size,
						double **matrix, double *vector, double **new_vector)
{
	size_t			i;
	size_t			j;

	i = -1;
	while (++i < matrix_size->rows)
	{
		new_vector[i][0] = 0;
		j = -1;
		while (++j < matrix_size->columns)
			new_vector[i][0] += matrix[i][j] - vector[i];
	}
	return ;
}
