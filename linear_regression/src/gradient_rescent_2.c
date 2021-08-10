/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_rescent_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 07:43:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/10 23:22:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_gradient_descent	*gradient_descent_initialize(size_t num_of_records,
												double alpha, double cost_limit)
{
	t_gradient_descent		*gradient_descent;

	gradient_descent = (t_gradient_descent *)
		ft_memalloc(sizeof(*gradient_descent));
	gradient_descent->alpha = alpha;
	gradient_descent->cost_limit = cost_limit;
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

void	unknown_variables_iterate_values(t_gradient_descent *gradient_descent,
										t_variable *input_variable,
										t_variable *measured_variable)
{
	t_matrix				*new_theta;
	double					**theta_values;
	double					prev_residual_sum_of_squares;
	t_reg_residual			*reg_residual;
	size_t					i;

	reg_residual = &gradient_descent->reg_residual;
	new_theta = ft_vector_create(sizeof(double), 2);
	gradient_descent->theta_normalized = theta_initialize();
	theta_values = (double **)gradient_descent->theta_normalized->values;
	FT_LOG_INFO("ALPHA: %f", gradient_descent->alpha);
	FT_LOG_INFO("COST_LIMIT: %f", gradient_descent->cost_limit);
	prev_residual_sum_of_squares = (double)INT_MAX;
	calculate_new_theta(gradient_descent, input_variable,
		measured_variable, (double **)new_theta->values);
	theta_values[0][0] = ((double **)new_theta->values)[0][0];
	theta_values[1][0] = ((double **)new_theta->values)[1][0];
	i = 1;
	while (prev_residual_sum_of_squares - reg_residual->residual_sum_of_squares
		> gradient_descent->cost_limit)
	{
		FT_LOG_TRACE("DIFF: %.10f", prev_residual_sum_of_squares
			- reg_residual->residual_sum_of_squares);
		prev_residual_sum_of_squares = reg_residual->residual_sum_of_squares;
		calculate_new_theta(gradient_descent, input_variable,
			measured_variable, (double **)new_theta->values);
		theta_values[0][0] = ((double **)new_theta->values)[0][0];
		theta_values[1][0] = ((double **)new_theta->values)[1][0];
		FT_LOG_TRACE("Sum of residual: %f(%f)",
			reg_residual->residual_sum_of_squares, reg_residual->residual_sum);
		i++;
	}
	FT_LOG_TRACE("DIFF: %.10f", prev_residual_sum_of_squares
		- gradient_descent->reg_residual.residual_sum_of_squares);
	FT_LOG_INFO("Num of iteration loops for calculagting theta values: %u", i);
	gradient_descent->theta = theta_values_denormalize(theta_values,
			input_variable, measured_variable);
	ft_vector_remove(&new_theta);
	return ;
}
