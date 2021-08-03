/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_record.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 08:01:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/03 22:19:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	statistics_save_records(t_statistics *statistics)
{
	char				*body;
	t_list				*elem;
	t_stat_counters		*stat_counters;

	stat_set_end_time(statistics);
	statistics->data_type = "input";
	statistics->id = 0;
	elem = statistics->stat_counters_lst;
	while (elem)
	{
		stat_counters = *(t_stat_counters **)elem->content;
		body = create_influxdb_query_string(stat_counters,
				statistics->end_time, statistics->data_type, statistics->id);
		ft_influxdb_write(statistics->connection, body, "Hive");
		ft_strdel(&body);
		elem = elem->next;
		statistics->id++;
	}
	return ;
}

t_stat_counters	*stat_counters_initialize(void)
{
	t_stat_counters		*stat_counters;

	stat_counters = (t_stat_counters *)ft_memalloc(sizeof(*stat_counters));
	stat_counters->counter_names[E_INDEPENDENT]
		= ft_strdup("independent=%d");
	stat_counters->counter_names[E_DEPENDENT]
		= ft_strdup("dependent=%d");
	stat_counters->counter_names[E_PREDICTED_PRICE]
		= ft_strdup("predicted_price=%d");
	stat_counters->is_active[E_INDEPENDENT] = 1;
	stat_counters->is_active[E_DEPENDENT] = 1;
	stat_counters->is_active[E_PREDICTED_PRICE] = 1;
	return (stat_counters);
}

void	statistics_create_records(t_list **stat_counters_lst,
											t_lin_reg *linear_regression_data)
{
	size_t				i;
	t_stat_counters		*stat_counters;
	t_list				*elem;
	t_variable			*input_variable;
	t_variable			*measured_variable;

	input_variable = &linear_regression_data->input_variables.km;
	measured_variable = &linear_regression_data->measured_variables.price;
	i = -1;
	while (++i < input_variable->size)
	{
		stat_counters = stat_counters_initialize();
		stat_counters->value[E_INDEPENDENT]
			= ((int *)input_variable->values)[i];
		stat_counters->value[E_DEPENDENT]
			= ((int *)measured_variable->values)[i];
		stat_counters->value[E_PREDICTED_PRICE]
			= ((double *)linear_regression_data->predicted_price.values)[i];
		elem = ft_lstnew(&stat_counters, sizeof(stat_counters));
		ft_lstadd(stat_counters_lst, elem);
	}
	return ;
}

void	statistics_release_record(void *content, size_t size)
{
	t_data_record	**data_record;

	(void)size;
	data_record = content;
	ft_memdel((void **)data_record);
	ft_memdel((void **)&content);
	return ;
}
