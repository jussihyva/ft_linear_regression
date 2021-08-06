/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 12:29:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 12:43:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	ft_matrix_print(char *matrix_name, t_matrix *matrix,
													t_content_type content_type)
{
	size_t		i;
	size_t		j;

	ft_printf("%s\n", matrix_name);
	i = -1;
	while (++i < matrix->size.rows)
	{
		j = -1;
		while (++j < matrix->size.columns)
		{
			if (content_type == E_INT)
				ft_printf("%d ", ((int **)matrix->values)[i][j]);
			else if (content_type == E_DOUBLE)
				ft_printf("%f ", ((double **)matrix->values)[i][j]);
		}
		ft_printf("\n");
	}
	return ;
}
