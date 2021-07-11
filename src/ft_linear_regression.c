/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/11 17:12:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

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

static t_loging_data	*set_loging_parameters(t_loging_level event_type)
{
	t_loging_data	*loging_data;

	loging_data = (t_loging_data *)ft_memalloc(sizeof(*loging_data));
	loging_data->level_strings = (const char **)ft_memalloc(
			sizeof(*loging_data->level_strings) * 6);
	loging_data->level_colors = (const char **)ft_memalloc(
			sizeof(*loging_data->level_strings) * 6);
	set_level_strings(loging_data->level_strings);
	loging_data->level_colors[LOG_TRACE] = ft_strdup("\x1b[94m");
	loging_data->level_colors[LOG_DEBUG] = ft_strdup("\x1b[36m");
	loging_data->level_colors[LOG_INFO] = ft_strdup("\x1b[32m");
	loging_data->level_colors[LOG_WARN] = ft_strdup("\x1b[33m");
	loging_data->level_colors[LOG_ERROR] = ft_strdup("\x1b[31m");
	loging_data->level_colors[LOG_FATAL] = ft_strdup("\x1b[35m");
	ft_log_set_params(loging_data->level_strings, loging_data->level_colors);
	ft_log_set_level(event_type);
	// ft_log_add_callback(influxdb_plugin, (void *)statistics, LOG_INFO);
	return (loging_data);
}

static void	release_loging_parameters(t_loging_data **loging_data)
{
	int		i;

	i = -1;
	while (++i < 6)
		ft_memdel((void **)&(*loging_data)->level_colors[i]);
	ft_memdel((void **)&(*loging_data)->level_colors);
	i = -1;
	while (++i < 6)
		ft_memdel((void **)&(*loging_data)->level_strings[i]);
	ft_memdel((void **)&(*loging_data)->level_strings);
	ft_memdel((void **)loging_data);
	ft_release_loging_params();
}

int	main(int argc, char **argv)
{
	t_arg_parser_data		*arg_parser_data;
	char					*options;
	t_data_set				*data_set;
	t_loging_data			*loging_data;

	options = ft_strdup("f:h");
	arg_parser_data
		= (t_arg_parser_data *)ft_memalloc(sizeof(*arg_parser_data));
	arg_parser_data->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser_data->fn_save_cmd_argument = save_cmd_argument;
	arg_parser_data->fn_usage = print_usage;
	arg_parser_data->input_params = NULL;
	ft_arg_parser(arg_parser_data, argc, argv, options);
	loging_data = set_loging_parameters(LOG_INFO);
	data_set = read_dataset_file(
			((t_input_params *)arg_parser_data->input_params)->dataset_file);
	ft_memdel((void **)&data_set);
	release_input_params((t_input_params **)&arg_parser_data->input_params);
	release_loging_parameters(&loging_data);
	ft_memdel((void **)&arg_parser_data);
	ft_memdel((void **)&options);
	return (0);
}
