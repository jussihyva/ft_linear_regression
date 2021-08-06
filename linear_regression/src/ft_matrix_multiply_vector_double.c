/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multiply_vector_double.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:10:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 13:26:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	ft_matrix_multiply_vector_double(t_matrix *matrix, t_matrix *vector,
														t_matrix *new_vector)
{
	size_t			i;
	size_t			j;

	i = -1;
	if (matrix->size.rows != vector->size.rows
		&& vector->size.rows != 1)
		FT_LOG_FATAL("Invalid matrix vector dot request!");
	while (++i < matrix->size.rows)
	{
		((double **)new_vector->values)[i][0] = (double)0;
		j = -1;
		while (++j < matrix->size.columns)
			((double **)new_vector->values)[i][j]
				= ((double **)matrix->values)[i][j]
				* ((double **)vector->values)[i % vector->size.rows][0];
	}
	return ;
}
