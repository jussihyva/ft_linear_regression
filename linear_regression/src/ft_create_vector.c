/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/21 11:54:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	**ft_create_vector(size_t size, size_t vector_size)
{
	void	**vector;
	size_t	i;

	vector = (void **)ft_memalloc(sizeof(*vector) * vector_size);
	i = -1;
	while (++i < vector_size)
		vector[i] = (void *)ft_memalloc(size);
	return (vector);
}
