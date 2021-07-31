/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:38:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/31 19:04:58 by jkauppi          ###   ########.fr       */
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
	if (statistics && *statistics)
	{
		ft_lstdel(&(*statistics)->stat_counters_lst, stat_counters_remove);
		SSL_shutdown(((t_tls_connection *)(*statistics)
				->influxdb->connection)->ssl_bio);
		SSL_free(((t_tls_connection *)(*statistics)
				->influxdb->connection)->ssl_bio);
		SSL_CTX_free(((t_tls_connection *)(*statistics)
				->influxdb->connection)->ctx);
		ft_memdel((void **)&(*statistics)->influxdb->connection);
		ft_memdel((void **)&(*statistics)->influxdb);
		ft_memdel((void **)statistics);
	}
	return ;
}
