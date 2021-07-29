/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/29 14:01:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_statistics	*ft_statistics_initialize(void)
{
	t_statistics	*statistics;

	statistics = (t_statistics *)ft_memalloc(sizeof(*statistics));
	statistics->stat_counters_lst
		= (t_list **)ft_memalloc(sizeof(*statistics->stat_counters_lst));
	statistics->influxdb = ft_influxdb_connect("127.0.0.1", "8086", statistics);
	return (statistics);
}

#if DARWIN

void	check_mem_usage(t_memory_info *memory_info, t_statistics *statistics)
{
	(void)statistics;
	memory_info->av_phys_pages = 0;
	memory_info->tot_phys_pages = 0;
	memory_info->mem_usage = (int)memory_info->rusage.ru_maxrss / 1000;
	return ;
}
#else

void	check_mem_usage(t_memory_info *memory_info, t_statistics *statistics)
{
	struct sysinfo		info;

	(void)statistics;
	sysinfo(&info);
	memory_info->av_phys_pages = get_avphys_pages();
	memory_info->tot_phys_pages = get_phys_pages();
	memory_info->mem_usage = (int)memory_info->rusage.ru_maxrss;
	return ;
}

#endif

void	stat_update_mem_usage(t_statistics *statistics)
{
	static t_memory_info	memory_info;

	if (!memory_info.mem_limit)
		memory_info.mem_limit = 1000000;
	getrusage(RUSAGE_SELF, &memory_info.rusage);
	getrlimit(RLIMIT_MEMLOCK, &memory_info.rlim);
	check_mem_usage(&memory_info, statistics);
	if (memory_info.mem_usage > memory_info.mem_limit)
	{
		FT_LOG_WARN("Mem usage: %ld (+%5ld)", memory_info.mem_usage,
			memory_info.mem_usage - memory_info.usage_prev);
		FT_LOG_WARN("Available phys pages: %ld(%ld)", memory_info.av_phys_pages,
			memory_info.tot_phys_pages);
		memory_info.mem_limit += 200000;
		memory_info.usage_prev = memory_info.mem_usage;
	}
	return ;
}
