/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:16:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/20 12:22:00 by jkauppi          ###   ########.fr       */
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
	variable->normalized_values
		= (double *)ft_memalloc(sizeof(*variable->normalized_values)
			* num_of_records);
	variable->min_max_value.min_value = (int *)ft_memalloc(sizeof(int));
	*(int *)variable->min_max_value.min_value = INT_MAX;
	variable->min_max_value.max_value = (int *)ft_memalloc(sizeof(int));
	*(int *)variable->min_max_value.max_value = INT_MIN;
	return ;
}

void	normalize_variable(t_variable *variable, size_t num_of_records)
{
	size_t		i;
	double		value_range;

	value_range = (double)(*(int *)variable->min_max_value.max_value
			- *(int *)variable->min_max_value.min_value);
	i = -1;
	while (++i < num_of_records)
	{
		variable->normalized_values[i] = (((int *)variable->values)[i]
				- *(int *)variable->min_max_value.min_value) / value_range;
		if (i)
			ft_printf(",");
		ft_printf(" %.2f", variable->normalized_values[i]);
	}
	return ;
}

void	pre_process_input_variables(t_lin_reg_data *linear_regression_data)
{
	int					i;
	t_list				*elem;
	t_data_record		*data_record;
	t_variable			*variable;
	size_t				num_of_records;

	num_of_records = linear_regression_data->num_of_records;
	variable = &linear_regression_data->input_variables.km;
	initalize_int_variable(variable, num_of_records);
	elem = *linear_regression_data->data_record_lst;
	variable->size = num_of_records;
	i = variable->size;
	ft_printf("KM: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		save_int_variable(variable, --i, data_record->km);
		ft_printf(" %d", data_record->km);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	normalize_variable(variable, num_of_records);
	return ;
}

void	pre_process_observed_values(t_lin_reg_data *linear_regression_data)
{
	size_t				i;
	t_list				*elem;
	t_data_record		*data_record;
	t_variable			*variable;
	size_t				num_of_records;

	num_of_records = linear_regression_data->num_of_records;
	variable = &linear_regression_data->measured_variables.price;
	initalize_int_variable(variable, num_of_records);
	elem = *linear_regression_data->data_record_lst;
	variable->size = linear_regression_data->num_of_records;
	i = linear_regression_data->num_of_records;
	ft_printf("PRICE: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		save_int_variable(variable, --i, data_record->price);
		ft_printf(" %d", data_record->price);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	normalize_variable(variable, num_of_records);
	return ;
}