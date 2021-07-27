/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/27 08:12:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_matrix	*ft_vector_create(size_t size, size_t vector_size)
{
	t_matrix	*vector;
	size_t		i;

	vector = (t_matrix *)ft_memalloc(sizeof(*vector));
	vector->values
		= (void **)ft_memalloc(sizeof(*vector->values) * vector_size);
	i = -1;
	while (++i < vector_size)
		vector->values[i] = (void *)ft_memalloc(size);
	vector->size.rows = vector_size;
	vector->size.columns = 1;
	return (vector);
}

void	ft_vector_remove(t_matrix **vector)
{
	size_t	i;

	i = -1;
	while (++i < (*vector)->size.rows)
		ft_memdel(&(*vector)->values[i]);
	ft_memdel((void **)&(*vector)->values);
	ft_memdel((void **)vector);
	return ;
}
