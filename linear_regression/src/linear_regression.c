/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/23 17:14:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	linear_regression_add_data_record(
							t_lin_reg_data *linear_regression_data,
							t_data_record *data_record)
{
	t_list						*elem;

	linear_regression_data->num_of_records++;
	elem = ft_lstnew(&data_record, sizeof(data_record));
	ft_lstadd(linear_regression_data->data_record_lst, elem);
	return ;
}

static void	release_data_record(void *content, size_t size)
{
	t_data_record	**data_record;

	(void)size;
	data_record = content;
	ft_memdel((void **)data_record);
	ft_memdel((void **)&content);
	return ;
}

void	perform_linear_regression_data(t_lin_reg_data *linear_regression_data)
{
	static double		alpha = 0.8;
	double				**theta;
	t_variable			*input_variable;
	t_variable			*measured_variable;

	input_variable = &linear_regression_data->input_variables.km;
	pre_process_input_variables(linear_regression_data);
	theta = theta_initialize();
	ft_printf("   KM MIN=%d MAX=%d\n", *(int *)input_variable->min_max_value
		.min_value, *(int *)input_variable->min_max_value.max_value);
	measured_variable = &linear_regression_data->measured_variables.price;
	ft_printf("PRICE MIN=%d MAX=%d\n", *(int *)measured_variable->min_max_value
		.min_value, *(int *)measured_variable->min_max_value.max_value);
	calculate_error(alpha, theta, input_variable, measured_variable);
	ft_memdel((void **)&theta[0]);
	ft_memdel((void **)&theta[1]);
	ft_memdel((void **)&theta);
	return ;
}

void	linear_regression_data_release(
							t_lin_reg_data **linear_regression_data)
{
	ft_lstdel((*linear_regression_data)->data_record_lst, release_data_record);
	ft_memdel((void **)&(*linear_regression_data)->data_record_lst);
	variable_remove(&(*linear_regression_data)->input_variables.km);
	variable_remove(&(*linear_regression_data)->measured_variables.price);
	ft_memdel((void **)linear_regression_data);
	return ;
}
