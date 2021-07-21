/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/21 13:33:16 by jkauppi          ###   ########.fr       */
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
	double				*theta;
	double				**matrix;
	t_variable			*variable;
	t_matrix_size		matrix_size;
	size_t				i;

	variable = &linear_regression_data->input_variables.km;
	pre_process_input_variables(linear_regression_data);
	pre_process_observed_values(linear_regression_data);
	matrix = matrix_initialize(variable, &matrix_size);
	theta = theta_initialize();
	ft_printf("   KM MIN=%d MAX=%d\n", *(int *)variable->min_max_value
		.min_value, *(int *)variable->min_max_value.max_value);
	variable = &linear_regression_data->measured_variables.price;
	ft_printf("PRICE MIN=%d MAX=%d\n", *(int *)variable->min_max_value
		.min_value, *(int *)variable->min_max_value.max_value);
	calculate_error(theta, matrix, &matrix_size, variable);
	ft_memdel((void **)&theta);
	variable = &linear_regression_data->input_variables.km;
	i = -1;
	while (++i < variable->size)
		ft_memdel((void **)&matrix[i]);
	ft_memdel((void **)&matrix);
	return ;
}

void	linear_regression_data_release(
							t_lin_reg_data **linear_regression_data)
{
	ft_lstdel((*linear_regression_data)->data_record_lst, release_data_record);
	ft_memdel((void **)&(*linear_regression_data)->data_record_lst);
	ft_memdel((void **)&(*linear_regression_data)->input_variables.km
		.min_max_value.min_value);
	ft_memdel((void **)&(*linear_regression_data)->input_variables.km
		.min_max_value.max_value);
	ft_memdel((void **)&(*linear_regression_data)->input_variables.km
		.values);
	ft_memdel((void **)&(*linear_regression_data)->input_variables.km
		.normalized_values);
	ft_memdel((void **)&(*linear_regression_data)->measured_variables.price
		.min_max_value.min_value);
	ft_memdel((void **)&(*linear_regression_data)->measured_variables.price
		.min_max_value.max_value);
	ft_memdel((void **)&(*linear_regression_data)->measured_variables.price
		.values);
	ft_memdel((void **)&(*linear_regression_data)->measured_variables.price
		.normalized_values);
	ft_memdel((void **)linear_regression_data);
	return ;
}
