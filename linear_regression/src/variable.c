/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:16:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/29 13:55:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static void	save_int_variable(t_variable *variable, size_t i, int new_value)
{
	((int *)variable->values)[i] = new_value;
	*(int *)variable->min_max_value.min_value
		= ft_min_int(new_value,
			*(int *)variable->min_max_value.min_value);
	*(int *)variable->min_max_value.max_value
		= ft_max_int(new_value,
			*(int *)variable->min_max_value.max_value);
	return ;
}

void	initalize_variable(t_variable *variable, size_t num_of_records,
																	size_t size)
{
	variable->values = ft_memalloc(size * num_of_records);
	variable->size = num_of_records;
	variable->min_max_value.min_value = ft_memalloc(size);
	variable->min_max_value.max_value = ft_memalloc(size);
	variable->min_max_value.range = ft_memalloc(size);
	return ;
}

static void	initialize_independent_variables(t_variable *variable,
													t_list **data_record_lst)
{
	int					i;
	t_list				*elem;
	t_data_record		*data_record;

	elem = *data_record_lst;
	i = variable->size;
	ft_printf("   KM: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		save_int_variable(variable, --i, data_record->km);
		ft_printf(" %6d", data_record->km);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	*(int *)variable->min_max_value.range
		= *(int *)variable->min_max_value.max_value
		- *(int *)variable->min_max_value.min_value;
	variable->normalized_values = variable_normalize((int *)variable->values,
			&variable->min_max_value, variable->size);
	variable->matrix = matrix_initialize(variable);
	return ;
}

static void	initialize_dependent_variables(t_variable *variable,
													t_list **data_record_lst)
{
	int					i;
	t_list				*elem;
	t_data_record		*data_record;

	elem = *data_record_lst;
	i = variable->size;
	ft_printf("PRICE: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		save_int_variable(variable, --i, data_record->price);
		ft_printf(" %6d", data_record->price);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	*(int *)variable->min_max_value.range
		= *(int *)variable->min_max_value.max_value
		- *(int *)variable->min_max_value.min_value;
	variable->normalized_values = variable_normalize(variable->values,
			&variable->min_max_value, variable->size);
	return ;
}

void	pre_process_input_variables(t_lin_reg_data *linear_regression_data)
{
	t_variable			*variable;
	size_t				num_of_records;

	num_of_records = linear_regression_data->num_of_records;
	variable = &linear_regression_data->input_variables.km;
	initalize_variable(variable, num_of_records, sizeof(int));
	*(int *)variable->min_max_value.min_value = INT_MAX;
	*(int *)variable->min_max_value.max_value = INT_MIN;
	*(int *)variable->min_max_value.range = 0;
	initialize_independent_variables(variable,
		linear_regression_data->data_record_lst);
	FT_LOG_INFO("   KM MIN=%d MAX=%d", *(int *)variable->min_max_value
		.min_value, *(int *)variable->min_max_value.max_value);
	variable = &linear_regression_data->measured_variables.price;
	initalize_variable(variable, num_of_records, sizeof(int));
	*(int *)variable->min_max_value.min_value = INT_MAX;
	*(int *)variable->min_max_value.max_value = INT_MIN;
	*(int *)variable->min_max_value.range = 0;
	initialize_dependent_variables(variable,
		linear_regression_data->data_record_lst);
	FT_LOG_INFO("PRICE MIN=%d MAX=%d", *(int *)variable->min_max_value
		.min_value, *(int *)variable->min_max_value.max_value);
}
