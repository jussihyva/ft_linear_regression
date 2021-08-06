/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 22:23:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/06 22:40:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	residual_calculate(t_variable *input_variable, t_matrix *theta,
					t_variable *measured_variable, t_reg_residual *reg_residual)
{
	t_matrix		*predicted;

	predicted = ft_vector_create(sizeof(double), input_variable->size);
	ft_matrix_dot_vector_double(input_variable->matrix, theta, predicted);
	ft_matrix_subtract_vector_double(predicted,
		measured_variable->normalized_values, reg_residual->residual);
	ft_matrix_multiply_vector_double(reg_residual->residual,
		reg_residual->residual, reg_residual->residual_squares);
	reg_residual->residual_sum_of_squares
		= ft_matrix_sum(reg_residual->residual_squares);
	ft_vector_remove(&predicted);
	return ;
}
