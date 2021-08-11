/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:38:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 11:14:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static void	stat_counters_remove(void *content, size_t size)
{
	t_stat_counters		*stat_counters;
	size_t				i;

	(void)size;
	stat_counters = *(t_stat_counters **)content;
	i = -1;
	while (++i < NUM_OF_STAT_COUNTERS)
		ft_strdel(&stat_counters->counter_names[i]);
	ft_memdel((void **)&stat_counters);
	ft_memdel(&content);
	return ;
}

void	statistics_remove(t_statistics **statistics)
{
	t_influxdb		*influxdb;

	influxdb = (*statistics)->influxdb;
	if (statistics && *statistics)
	{
		ft_lstdel(&(*statistics)->stat_counters_lst, stat_counters_remove);
		if (influxdb)
			influxdb_remove(influxdb);
		ft_memdel((void **)statistics);
	}
	return ;
}
