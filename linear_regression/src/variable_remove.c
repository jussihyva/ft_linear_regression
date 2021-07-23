/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:08:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/23 17:13:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	variable_remove(t_variable *variable)
{
	size_t		i;

	ft_memdel((void **)&variable->min_max_value.min_value);
	ft_memdel((void **)&variable->min_max_value.max_value);
	ft_memdel((void **)&variable->values);
	ft_vector_remove((void ***)&variable->normalized_values,
		variable->size);
	if (variable->matrix)
	{
		i = -1;
		while (++i < variable->size)
			ft_memdel((void **)&variable->matrix[i]);
		ft_memdel((void **)&variable->matrix);
	}
	return ;
}
