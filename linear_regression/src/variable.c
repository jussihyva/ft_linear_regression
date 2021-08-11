/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:16:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 17:37:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static void	variable_calculate_range_int(t_min_max_value *min_max_value)
{
	*(int *)min_max_value->range = *(int *)min_max_value->max_value
		- *(int *)min_max_value->min_value;
	return ;
}

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

static void	initialize_independent_variables(t_variable *variable1,
								t_variable *variable2, t_list **data_record_lst)
{
	int					i;
	t_list				*elem;
	t_data_record		*data_record;

	*(int *)variable1->min_max_value.min_value = INT_MAX;
	*(int *)variable1->min_max_value.max_value = INT_MIN;
	*(int *)variable2->min_max_value.min_value = INT_MAX;
	*(int *)variable2->min_max_value.max_value = INT_MIN;
	elem = *data_record_lst;
	i = variable1->size;
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		i--;
		save_int_variable(variable1, i, data_record->km);
		save_int_variable(variable2, i, data_record->price);
		elem = elem->next;
	}
	variable_calculate_range_int(&variable1->min_max_value);
	variable_calculate_range_int(&variable2->min_max_value);
	variable1->normalized_values = variable_normalize(variable1);
	variable2->normalized_values = variable_normalize(variable2);
	variable1->matrix = matrix_initialize(variable1);
	return ;
}

void	pre_process_input_variables(t_lin_reg *linear_regression)
{
	t_variable			*variable1;
	t_variable			*variable2;
	size_t				num_of_records;

	num_of_records = linear_regression->dataset->num_of_records;
	variable1 = &linear_regression->input_variables.km;
	variable2 = &linear_regression->measured_variables.price;
	initalize_variable(variable1, num_of_records, sizeof(int));
	initalize_variable(variable2, num_of_records, sizeof(int));
	initialize_independent_variables(variable1, variable2,
		&linear_regression->dataset->data_record_lst);
	FT_LOG_INFO("   KM MIN=%d MAX=%d", *(int *)variable1->min_max_value
		.min_value, *(int *)variable1->min_max_value.max_value);
	FT_LOG_INFO("PRICE MIN=%d MAX=%d", *(int *)variable1->min_max_value
		.min_value, *(int *)variable2->min_max_value.max_value);
}
