/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_normalize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:59:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/04 11:33:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_matrix	*variable_normalize(int *values, t_min_max_value *min_max_value,
														size_t num_of_records)
{
	size_t		i;
	double		value_range;
	t_matrix	*normalized_values;
	int			max_value;
	int			min_value;

	min_value = *(int *)min_max_value->min_value;
	max_value = *(int *)min_max_value->max_value;
	normalized_values = ft_vector_create(sizeof(double), num_of_records);
	value_range = (double)(max_value - min_value);
	i = -1;
	while (++i < num_of_records)
		((double **)normalized_values->values)[i][0]
			= (values[i] - min_value) / value_range;
	return (normalized_values);
}
