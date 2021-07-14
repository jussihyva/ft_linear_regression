/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_regression.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:34:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/14 14:02:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	linear_regression_add_data_record(
							t_lin_reg_data *linear_regression_data,
							t_data_record *data_record)
{
	t_list						*elem;

	linear_regression_data->num_of_records++;
	linear_regression_data->sum_km += data_record->km;
	linear_regression_data->sum_price += data_record->price;
	elem = ft_lstnew(&data_record, sizeof(data_record));
	ft_lstadd(linear_regression_data->data_record_lst, elem);
	return ;
}

static void	create_vector_of_observed_values_price(
										t_lin_reg_data *linear_regression_data)
{
	int				i;
	t_list			*elem;
	t_data_record	*data_record;

	linear_regression_data->vec_observed_values_price
		= (int *)ft_memalloc(sizeof(*linear_regression_data
				->vec_observed_values_price)
			* linear_regression_data->num_of_records);
	elem = *linear_regression_data->data_record_lst;
	i = linear_regression_data->num_of_records;
	ft_printf("PRICE: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		i--;
		linear_regression_data->vec_observed_values_price[i]
			= data_record->price;
		ft_printf(" %d", data_record->price);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	FT_LOG_INFO("Value of CNT is %d", i);
	return ;
}

static void	create_vector_of_input_variables(
										t_lin_reg_data *linear_regression_data)
{
	int				i;
	t_list			*elem;
	t_data_record	*data_record;

	linear_regression_data->input_variables
		= (int *)ft_memalloc(sizeof(*linear_regression_data
				->input_variables)
			* linear_regression_data->num_of_records * 2);
	elem = *linear_regression_data->data_record_lst;
	i = linear_regression_data->num_of_records * 2;
	ft_printf("KM: ");
	while (elem)
	{
		data_record = *(t_data_record **)elem->content;
		i--;
		linear_regression_data->input_variables[i]
			= data_record->km;
		i--;
		linear_regression_data->input_variables[i] = 1;
		ft_printf(" %d", data_record->km);
		if (i)
			ft_printf(",");
		elem = elem->next;
	}
	ft_printf("\n");
	FT_LOG_INFO("Value of CNT is %d", i);
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
	ft_printf("   KM AVG: %.2f\n", linear_regression_data->sum_km / (double)linear_regression_data->num_of_records);
	ft_printf("PRICE AVG: %.2f\n", linear_regression_data->sum_price / (double)linear_regression_data->num_of_records);
	create_vector_of_input_variables(linear_regression_data);
	create_vector_of_observed_values_price(linear_regression_data);
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
