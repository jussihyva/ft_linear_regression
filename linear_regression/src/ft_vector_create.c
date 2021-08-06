/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 10:27:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_matrix	*ft_vector_create(size_t size, size_t number_fo_rows)
{
	t_matrix	*vector;
	size_t		i;

	vector = (t_matrix *)ft_memalloc(sizeof(*vector));
	vector->values
		= (void **)ft_memalloc(sizeof(*vector->values) * number_fo_rows);
	i = -1;
	while (++i < number_fo_rows)
		vector->values[i] = (void *)ft_memalloc(size);
	vector->size.rows = number_fo_rows;
	vector->size.columns = 1;
	return (vector);
}

void	ft_matrix_remove(t_matrix **matrix)
{
	size_t	i;

	if (*matrix)
	{
		i = -1;
		while (++i < (*matrix)->size.rows)
			ft_memdel(&(*matrix)->values[i]);
		ft_memdel((void **)&(*matrix)->values);
		ft_memdel((void **)matrix);
	}
	return ;
}

void	ft_vector_remove(t_matrix **vector)
{
	ft_matrix_remove(vector);
	return ;
}
