/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/13 15:37:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

int	main(int argc, char **argv)
{
	t_arg_parser_data			*arg_parser_data;
	char						*options;
	t_lin_reg_data				*linear_regression_data;
	t_event_logging_data		*event_logging_data;

	options = ft_strdup("L:f:h");
	arg_parser_data
		= (t_arg_parser_data *)ft_memalloc(sizeof(*arg_parser_data));
	arg_parser_data->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser_data->fn_save_cmd_argument = save_cmd_argument;
	arg_parser_data->fn_usage = print_usage;
	arg_parser_data->input_params = NULL;
	ft_arg_parser(arg_parser_data, argc, argv, options);
	event_logging_data = ft_event_logging_init(((t_input_params *)
				arg_parser_data->input_params)->event_logging_level);
	linear_regression_data = read_dataset_file(
			((t_input_params *)arg_parser_data->input_params)->dataset_file);
	perform_linear_regression_data(linear_regression_data);
	release_input_params((t_input_params **)&arg_parser_data->input_params);
	ft_event_logging_release(&event_logging_data);
	linear_regression_data_release(&linear_regression_data);
	ft_memdel((void **)&arg_parser_data);
	ft_memdel((void **)&options);
	return (0);
}
