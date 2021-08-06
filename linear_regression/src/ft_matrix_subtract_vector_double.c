/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_subtract_vector_double.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:31:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 12:26:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	ft_matrix_subtract_vector_double(t_matrix *matrix, t_matrix *vector,
														t_matrix *new_vector)
{
	size_t			i;
	size_t			j;

	if (matrix->size.rows != vector->size.rows
		&& vector->size.rows != 1)
		FT_LOG_FATAL("Invalid matrix vector subtract request!");
	i = -1;
	while (++i < matrix->size.rows)
	{
		j = -1;
		while (++j < matrix->size.columns)
			((double **)new_vector->values)[i][j]
				= ((double **)matrix->values)[i][j]
				- ((double **)vector->values)[i % vector->size.rows][0];
	}
	return ;
}
