/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:23:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/27 07:40:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

double	ft_matrix_sum(t_matrix *matrix)
{
	double		sum;
	size_t		i;
	size_t		j;

	sum = 0;
	i = -1;
	while (++i < matrix->size.rows)
	{
		j = -1;
		while (++j < matrix->size.columns)
			sum += ((double **)matrix->values)[i][j];
	}
	return (sum);
}
