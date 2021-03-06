/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dot_vector_double.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:31:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 10:10:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	ft_matrix_dot_vector_double(t_matrix *matrix, t_matrix *vector,
	t_matrix *new_vector)
{
	size_t			i;
	size_t			j;

	i = -1;
	if (matrix->size.columns != vector->size.rows
		&& vector->size.rows != 1)
		FT_LOG_FATAL("Invalid matrix vector dot request!");
	while (++i < matrix->size.rows)
	{
		((double **)new_vector->values)[i][0] = (double)0;
		j = -1;
		while (++j < matrix->size.columns)
			((double **)new_vector->values)[i][0]
				+= ((double **)matrix->values)[i][j]
				* ((double **)vector->values)[j % vector->size.rows][0];
	}
	return ;
}
