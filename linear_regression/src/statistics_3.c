/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:08:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/24 11:33:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	release_statistics_params(t_statistics *statistics)
{
	int		i;

	if (statistics)
	{
		ft_strdel(&statistics->algorithm);
		ft_strdel(&statistics->algorithm_substring);
		i = -1;
		// while (++i < NUM_OF_STAT_COUNTERS)
		// 	ft_memdel((void **)&statistics->stat_counters.counter_names[i]);
		// ft_memdel((void **)&statistics->stat_counters.counter_names);
		ft_memdel((void **)&statistics);
	}
	return ;
}

static void	add_counter_to_string(char **string_ptr, char *counter_name,
											int counter_value, char sep_char)
{
	char	format_string[100000];
	char	counter_string[100000];

	*counter_string = '\0';
	*format_string = sep_char;
	*(format_string + 1) = '\0';
	ft_strcat(format_string, counter_name);
	ft_sprintf(counter_string, format_string, counter_value);
	ft_strcat(*string_ptr, counter_string);
	*string_ptr += ft_strlen(counter_string);
	return ;
}

static char	*add_counters_to_string(char *format_string_ptr,
				t_stat_counters *stat_counters, char *influxdb_query_string)
{
	int		i;
	char	*string_ptr;
	char	sep_char;

	sep_char = ' ';
	i = -1;
	string_ptr = influxdb_query_string;
	ft_strcat(string_ptr, format_string_ptr);
	string_ptr += ft_strlen(format_string_ptr);
	while (++i < NUM_OF_STAT_COUNTERS)
	{
		if (stat_counters->is_active[i])
		{
			add_counter_to_string(&string_ptr, stat_counters->counter_names[i],
				stat_counters->value[i], sep_char);
			sep_char = ',';
		}
	}
	return (string_ptr);
}

char	*create_influxdb_query_string(t_stat_counters *stat_counters,
													struct timespec end_time)
{
	char	*influxdb_query_string;
	char	*string;
	char	*tag_format_string;
	char	*tag_string;
	char	*offset_ptr;

	influxdb_query_string
		= (char *)ft_memalloc(sizeof(*influxdb_query_string) * 100000);
	string = (char *)ft_memalloc(sizeof(*string) * 100000);
	tag_string = (char *)ft_memalloc(sizeof(*tag_string) * 100000);
	tag_format_string = (char *)ft_memalloc(sizeof(*tag_format_string)
			* 100000);
	ft_strcat(string, "project=%s");
	ft_strcat(tag_format_string, string);
	ft_sprintf(tag_string, tag_format_string, "ft_linear_regression");
	ft_memdel((void **)&tag_format_string);
	offset_ptr = add_counters_to_string(tag_string, stat_counters,
			influxdb_query_string);
	ft_memdel((void **)&tag_string);
	ft_sprintf(offset_ptr, " %d\n", end_time);
	ft_memdel((void **)&string);
	return (influxdb_query_string);
}

// void	influxdb_plugin(t_log_event *event)
// {
// 	t_statistics	*statistics;
// 	char			*influxdb_query_string;
// 	int				*counter_values;

// 	statistics = (t_statistics *)event->additional_event_data;
// 	counter_values = statistics->stat_counters.value;
// 	statistics->stat_counters.is_active[E_EXECUTION_TIME] = 1;
// 	counter_values[E_EXECUTION_TIME] = (int)get_execution_time(statistics);
// 	influxdb_query_string = create_influxdb_query_string(statistics);
// 	ft_influxdb_write(statistics->connection, influxdb_query_string, "Hive");
// 	ft_memdel((void **)&influxdb_query_string);
// 	return ;
// }
