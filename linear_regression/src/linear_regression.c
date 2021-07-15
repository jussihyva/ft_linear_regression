/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/15 15:05:03 by jkauppi          ###   ########.fr       */
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

static void	save_int_variable(t_variable *variable, int i, int new_value)
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

static void	initalize_int_variable(t_variable *variable, int num_of_records)
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

static void	create_vector_of_observed_values_price(
										t_lin_reg_data *linear_regression_data)
{
	int					i;
	t_list				*elem;
	t_data_record		*data_record;
	t_variable			*price;

	price = &linear_regression_data->measured_variables.price;
	initalize_int_variable(price, linear_regression_data->num_of_records);
	elem = *linear_regression_data->data_record_lst;
	i = linear_regression_data->num_of_records;
	ft_printf("PRICE: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		i--;
		save_int_variable(price, i, data_record->price);
		ft_printf(" %d", data_record->price);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	return ;
}

static void	create_vector_of_input_variables(
										t_lin_reg_data *linear_regression_data)
{
	int					i;
	t_list				*elem;
	t_data_record		*data_record;
	t_variable			*km;

	km = &linear_regression_data->input_variables.km;
	initalize_int_variable(km, linear_regression_data->num_of_records);
	elem = *linear_regression_data->data_record_lst;
	i = linear_regression_data->num_of_records;
	ft_printf("KM: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		i--;
		save_int_variable(km, i, data_record->km);
		ft_printf(" %d", data_record->km);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	return ;
}

void	normalize_variable(t_variable *variable, int num_of_records)
{
	int			i;
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

void	normalize_variables(t_input_variables *input_variables,
									t_measured_variables *measured_variables,
															int num_of_records)
{
	t_variable		*variable;

	ft_printf("KM (normalized): ");
	variable = &input_variables->km;
	normalize_variable(variable, num_of_records);
	ft_printf("\n");
	ft_printf("PRIZE (normalized): ");
	variable = &measured_variables->price;
	normalize_variable(variable, num_of_records);
	ft_printf("\n");
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
	t_min_max_value		*min_max_value;

	create_vector_of_input_variables(linear_regression_data);
	create_vector_of_observed_values_price(linear_regression_data);
	normalize_variables(&linear_regression_data->input_variables,
		&linear_regression_data->measured_variables,
		linear_regression_data->num_of_records);
	min_max_value
		= &linear_regression_data->input_variables.km.min_max_value;
	ft_printf("   KM MIN=%d MAX=%d\n", *(int *)min_max_value->min_value,
		*(int *)min_max_value->max_value);
	min_max_value
		= &linear_regression_data->measured_variables.price.min_max_value;
	ft_printf("PRICE MIN=%d MAX=%d\n", *(int *)min_max_value->min_value,
		*(int *)min_max_value->max_value);
	return ;
}

void	linear_regression_data_release(
							t_lin_reg_data **linear_regression_data)
{
	ft_lstdel((*linear_regression_data)->data_record_lst, release_data_record);
	ft_memdel((void **)(*linear_regression_data)->data_record_lst);
	ft_memdel((void **)linear_regression_data);
	return ;
}
