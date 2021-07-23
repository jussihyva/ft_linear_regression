/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_normalize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:59:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/23 16:36:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

double	**variable_normalize(void *values, t_min_max_value *min_max_value,
														size_t num_of_records)
{
	size_t		i;
	double		value_range;
	double		**normalized_values;
	int			max_value;
	int			min_value;

	min_value = *(int *)min_max_value->min_value;
	max_value = *(int *)min_max_value->max_value;
	normalized_values = (double **)ft_vector_create(sizeof(double),
			num_of_records);
	value_range = (double)(max_value - min_value);
	i = -1;
	while (++i < num_of_records)
	{
		normalized_values[i][0] = (((int *)values)[i] - min_value)
			/ value_range;
		if (i)
			ft_printf(",");
		ft_printf(" %.2f", normalized_values[i][0]);
	}
	ft_printf("\n");
	return (normalized_values);
}
