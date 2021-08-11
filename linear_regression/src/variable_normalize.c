/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_normalize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:59:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 17:30:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_matrix	*variable_normalize(t_variable *variable)
{
	size_t		i;
	double		value_range;
	t_matrix	*normalized_values;
	int			max_value;
	int			min_value;

	min_value = *(int *)variable->min_max_value.min_value;
	max_value = *(int *)variable->min_max_value.max_value;
	normalized_values = ft_vector_create(sizeof(double), variable->size);
	value_range = (double)(max_value - min_value);
	i = -1;
	while (++i < variable->size)
		((double **)normalized_values->values)[i][0]
			= (((int *)variable->values)[i] - min_value) / value_range;
	return (normalized_values);
}
