/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:14:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/29 14:02:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	set_total_cpu_usage_time(t_statistics *statistics)
{
	statistics->cpu_usage_ms = clock() / (CLOCKS_PER_SEC / 1000);
	FT_LOG_INFO("Used CPU time (ms): %ld", statistics->cpu_usage_ms);
	return ;
}

void	set_solver_start_time(t_statistics *statistics)
{
	statistics->solver_start_time_ms = clock() / (CLOCKS_PER_SEC / 1000);
	return ;
}

void	set_solver_end_time(t_statistics *statistics)
{
	statistics->solver_end_time_ms = clock() / (CLOCKS_PER_SEC / 1000);
	FT_LOG_INFO("Solver CPU time (ms): %ld",
		statistics->solver_end_time_ms - statistics->solver_start_time_ms);
	return ;
}

int	check_is_limit_reached(int *counter_values)
{
	int		is_limit_reached;

	(void)counter_values;
	is_limit_reached = 0;
	return (is_limit_reached);
}
