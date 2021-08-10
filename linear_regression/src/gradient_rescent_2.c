/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 07:43:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/10 16:02:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_gradient_descent	*gradient_descent_initialize(size_t num_of_records)
{
	t_gradient_descent		*gradient_descent;

	gradient_descent = (t_gradient_descent *)
		ft_memalloc(sizeof(*gradient_descent));
	gradient_descent->theta_file = "/tmp/theta.yml";
	gradient_descent->alpha = 0.1;
	gradient_descent->reg_residual.residual = ft_vector_create(sizeof(double),
			num_of_records);
	gradient_descent->reg_residual.residual_squares
		= ft_vector_create(sizeof(double), num_of_records);
	return (gradient_descent);
}

static t_matrix	*theta_values_denormalize(double **theta_values,
					t_variable *input_variable, t_variable *measured_variable)
{
	t_matrix	*theta;

	theta = theta_initialize();
	((double **)theta->values)[1][0] = theta_values[1][0]
		* *(int *)measured_variable->min_max_value.range
		/ (double)*(int *)input_variable->min_max_value.range;
	((double **)theta->values)[0][0] = theta_values[0][0]
		* *(int *)measured_variable->min_max_value.range;
	((double **)theta->values)[0][0]
		+= *(int *)measured_variable->min_max_value.min_value;
	((double **)theta->values)[0][0] -= ((double **)theta->values)[1][0]
		* *(int *)input_variable->min_max_value.min_value;
	return (theta);
}

t_gradient_descent	*unknown_variables_iterate_values(
												t_variable *input_variable,
												t_variable *measured_variable)
{
	t_gradient_descent		*gradient_descent;
	t_matrix				*new_theta;
	double					**theta_values;
	double					prev_residual_sum_of_squares;

	new_theta = ft_vector_create(sizeof(double), 2);
	gradient_descent = gradient_descent_initialize(input_variable->size);
	gradient_descent->theta_normalized = theta_initialize();
	theta_values = (double **)gradient_descent->theta_normalized->values;
	FT_LOG_INFO("ALPHA: %f", gradient_descent->alpha);
	prev_residual_sum_of_squares = (double)INT_MAX;
	calculate_new_theta(gradient_descent, input_variable,
		measured_variable, (double **)new_theta->values);
	theta_values[0][0] = ((double **)new_theta->values)[0][0];
	theta_values[1][0] = ((double **)new_theta->values)[1][0];
	while (prev_residual_sum_of_squares
		- gradient_descent->reg_residual.residual_sum_of_squares > COST_LIMIT)
	{
		FT_LOG_INFO("DIFF: %.10f", prev_residual_sum_of_squares
			- gradient_descent->reg_residual.residual_sum_of_squares);
		prev_residual_sum_of_squares
			= gradient_descent->reg_residual.residual_sum_of_squares;
		calculate_new_theta(gradient_descent, input_variable,
			measured_variable, (double **)new_theta->values);
		theta_values[0][0] = ((double **)new_theta->values)[0][0];
		theta_values[1][0] = ((double **)new_theta->values)[1][0];
		FT_LOG_INFO("Sum of residual: %f(%f)",
			gradient_descent->reg_residual.residual_sum_of_squares,
			gradient_descent->reg_residual.residual_sum);
	}
	FT_LOG_INFO("DIFF: %.10f", prev_residual_sum_of_squares
		- gradient_descent->reg_residual.residual_sum_of_squares);
	gradient_descent->theta = theta_values_denormalize(theta_values,
			input_variable, measured_variable);
	ft_vector_remove(&new_theta);
	return (gradient_descent);
}
