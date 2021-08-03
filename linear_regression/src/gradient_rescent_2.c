/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 07:43:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/03 11:41:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static t_gradient_descent	*gradient_descent_initialize(void)
{
	t_gradient_descent		*gradient_descent;

	gradient_descent = (t_gradient_descent *)
		ft_memalloc(sizeof(*gradient_descent));
	gradient_descent->theta_file = "/tmp/theta.yml";
	gradient_descent->alpha = 0.1;
	gradient_descent->theta = theta_initialize();
	return (gradient_descent);
}

t_gradient_descent	*unknown_variables_iterate_values(
												t_variable *input_variable,
												t_variable *measured_variable)
{
	t_gradient_descent		*gradient_descent;
	t_matrix				*new_theta;
	double					**theta_values;
	size_t					i;

	new_theta = ft_vector_create(sizeof(double), 2);
	gradient_descent = gradient_descent_initialize();
	theta_values = (double **)gradient_descent->theta->values;
	FT_LOG_INFO("ALPHA: %f", gradient_descent->alpha);
	i = -1;
	while (++i < 1000)
	{
		calculate_new_theta(gradient_descent, input_variable,
			measured_variable, (double **)new_theta->values);
		theta_values[0][0] = ((double **)new_theta->values)[0][0];
		theta_values[1][0] = ((double **)new_theta->values)[1][0];
	}
	theta_values[1][0] *= *(int *)measured_variable->min_max_value.range
		/ (double)*(int *)input_variable->min_max_value.range;
	theta_values[0][0] *= *(int *)measured_variable->min_max_value.range;
	theta_values[0][0] += *(int *)measured_variable->min_max_value.min_value;
	theta_values[0][0] -= theta_values[1][0]
		* *(int *)input_variable->min_max_value.min_value;
	ft_vector_remove(&new_theta);
	return (gradient_descent);
}
