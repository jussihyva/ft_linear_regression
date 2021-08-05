/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coefficient_of_determination.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:58:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/05 14:41:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static double	variable_denormalize_int(t_min_max_value *min_max_value,
													double normalized_value)
{
	double		denormalized_value;

	denormalized_value = (normalized_value * *(int *)min_max_value->range)
		+ *(int *)min_max_value->min_value;
	return (denormalized_value);
}

void	coefficient_of_determination_calculate(t_lin_reg *linear_regression)
{
	t_variable	*price;
	double		sum;
	double		average;
	double		average_denormalized;

	price = &linear_regression->measured_variables.price;
	ft_printf("%u\n", linear_regression->predicted_price
		.normalized_values->size.rows);
	ft_printf("%u\n", linear_regression->predicted_price
		.normalized_values->size.columns);
	sum = ft_matrix_sum(price->normalized_values);
	average = sum / linear_regression->measured_variables.price.size;
	average_denormalized = variable_denormalize_int(&price->min_max_value,
			average);
	ft_printf("AVERAGE: %.4f\n", average_denormalized);
	// linear_regression->predicted_price.normalized_values
	return ;
}
