/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:05:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/20 09:40:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	set_level_strings(const char **level_strings)
{
	level_strings[LOG_TRACE] = ft_strdup("TRACE");
	level_strings[LOG_DEBUG] = ft_strdup("DEBUG");
	level_strings[LOG_INFO] = ft_strdup("INFO");
	level_strings[LOG_WARN] = ft_strdup("WARN");
	level_strings[LOG_ERROR] = ft_strdup("ERROR");
	level_strings[LOG_FATAL] = ft_strdup("FATAL");
	return ;
}

static void	set_level_colors(const char **level_colors)
{
	level_colors[LOG_TRACE] = ft_strdup("\x1b[94m");
	level_colors[LOG_DEBUG] = ft_strdup("\x1b[36m");
	level_colors[LOG_INFO] = ft_strdup("\x1b[32m");
	level_colors[LOG_WARN] = ft_strdup("\x1b[33m");
	level_colors[LOG_ERROR] = ft_strdup("\x1b[31m");
	level_colors[LOG_FATAL] = ft_strdup("\x1b[35m");
	return ;
}

t_event_logging_data	*ft_event_logging_init(t_loging_level event_type)
{
	t_event_logging_data	*event_logging_data;

	event_logging_data
		= (t_event_logging_data *)ft_memalloc(sizeof(*event_logging_data));
	event_logging_data->level_strings = (const char **)ft_memalloc(
			sizeof(*event_logging_data->level_strings) * 6);
	event_logging_data->level_colors = (const char **)ft_memalloc(
			sizeof(*event_logging_data->level_strings) * 6);
	set_level_colors(event_logging_data->level_colors);
	set_level_strings(event_logging_data->level_strings);
	ft_log_set_params(event_logging_data->level_strings,
		event_logging_data->level_colors);
	ft_log_set_level(event_type);
	return (event_logging_data);
}

/**
// ft_log_add_callback(influxdb_plugin, (void *)statistics, LOG_INFO);
**/
