/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:08:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/27 15:24:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	variable_remove(t_variable *variable)
{
	size_t		i;

	ft_memdel((void **)&variable->min_max_value.min_value);
	ft_memdel((void **)&variable->min_max_value.max_value);
	ft_memdel((void **)&variable->values);
	ft_vector_remove(&variable->normalized_values);
	if (variable->matrix)
	{
		i = -1;
		while (++i < variable->matrix->size.rows)
			ft_memdel((void **)&variable->matrix->values[i]);
		ft_memdel((void **)&variable->matrix->values);
		ft_memdel((void **)&variable->matrix);
	}
	return ;
}
