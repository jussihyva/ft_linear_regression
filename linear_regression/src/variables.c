/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:16:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/23 16:25:43 by jkauppi          ###   ########.fr       */
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

static void	initalize_int_variable(t_variable *variable, size_t num_of_records)
{
	variable->values = (int *)ft_memalloc(sizeof(int) * num_of_records);
	variable->size = num_of_records;
	variable->min_max_value.min_value = (int *)ft_memalloc(sizeof(int));
	*(int *)variable->min_max_value.min_value = INT_MAX;
	variable->min_max_value.max_value = (int *)ft_memalloc(sizeof(int));
	*(int *)variable->min_max_value.max_value = INT_MIN;
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
	variable->normalized_values = variable_normalize(variable->values,
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
	initalize_int_variable(variable, num_of_records);
	initialize_independent_variables(variable,
		linear_regression_data->data_record_lst);
	variable = &linear_regression_data->measured_variables.price;
	initalize_int_variable(variable, num_of_records);
	initialize_dependent_variables(variable,
		linear_regression_data->data_record_lst);
}
