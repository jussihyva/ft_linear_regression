/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 07:43:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/02 07:52:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static t_gradient_descent_data	*gradient_descent_data_initialize(void)
{
	t_gradient_descent_data		*gradient_descent_data;

	gradient_descent_data = (t_gradient_descent_data *)
		ft_memalloc(sizeof(*gradient_descent_data));
	gradient_descent_data->theta_file = "/tmp/theta.yml";
	gradient_descent_data->alpha = 0.1;
	gradient_descent_data->theta = theta_initialize();
	return (gradient_descent_data);
}

t_gradient_descent_data	*unknown_variables_iterate_values(
												t_variable *input_variable,
												t_variable *measured_variable)
{
	t_gradient_descent_data		*gradient_descent_data;
	t_matrix					*new_theta;
	size_t						i;

	new_theta = ft_vector_create(sizeof(double), 2);
	gradient_descent_data = gradient_descent_data_initialize();
	FT_LOG_INFO("ALPHA: %f", gradient_descent_data->alpha);
	i = -1;
	while (++i < 1000)
	{
		calculate_new_theta(gradient_descent_data, input_variable,
			measured_variable, (double **)new_theta->values);
		((double **)gradient_descent_data->theta->values)[0][0]
			= ((double **)new_theta->values)[0][0];
		((double **)gradient_descent_data->theta->values)[1][0]
			= ((double **)new_theta->values)[1][0];
	}
	ft_vector_remove(&new_theta);
	return (gradient_descent_data);
}
