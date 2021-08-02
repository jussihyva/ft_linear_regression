/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/02 20:24:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static t_arg_parser_data	*arg_parser_data_initialize(int argc, char **argv)
{
	t_arg_parser_data			*arg_parser_data;

	arg_parser_data
		= (t_arg_parser_data *)ft_memalloc(sizeof(*arg_parser_data));
	arg_parser_data->argc_argv.argc = argc;
	arg_parser_data->argc_argv.argv = argv;
	arg_parser_data->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser_data->fn_save_cmd_argument = save_cmd_argument;
	arg_parser_data->fn_usage = print_usage;
	arg_parser_data->options = ft_strdup("L:f:h");
	ft_arg_parser(arg_parser_data);
	return (arg_parser_data);
}

static void	main_remove(t_arg_parser_data *arg_parser_data,
			t_statistics *statistics, t_event_logging_data *event_logging_data)
{
	statistics_remove(&statistics);
	release_input_params((t_input_params **)&arg_parser_data->input_params);
	ft_event_logging_release(&event_logging_data);
	ft_memdel((void **)&arg_parser_data->options);
	ft_memdel((void **)&arg_parser_data);
	return ;
}

int	main(int argc, char **argv)
{
	t_arg_parser_data			*arg_parser_data;
	t_lin_reg_data				*linear_regression_data;
	t_event_logging_data		*event_logging_data;
	t_statistics				*statistics;
	t_input_params				*input_params;
	double						*theta_values;

	arg_parser_data = arg_parser_data_initialize(argc, argv);
	input_params = (t_input_params *)arg_parser_data->input_params;
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	statistics = ft_statistics_initialize();
	if (input_params->dataset_file)
	{
		linear_regression_data = read_dataset_file(input_params->dataset_file);
		if (linear_regression_data->num_of_records)
		{
			theta_values = create_linear_regression_model(
					linear_regression_data, statistics);
			linear_regression_data_release(&linear_regression_data);
		}
		else
			FT_LOG_ERROR("No record in the input file (%s)",
				input_params->dataset_file);
	}
	main_remove(arg_parser_data, statistics, event_logging_data);
	return (0);
}
