/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/30 07:58:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

int	main(int argc, char **argv)
{
	t_arg_parser_data			*arg_parser_data;
	char						*options;
	t_lin_reg_data				*linear_regression_data;
	t_event_logging_data		*event_logging_data;
	t_statistics				*statistics;
	t_gradient_descent_data		gradient_descent_data;
	t_input_params				*input_params;

	options = ft_strdup("L:f:h");
	arg_parser_data
		= (t_arg_parser_data *)ft_memalloc(sizeof(*arg_parser_data));
	arg_parser_data->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser_data->fn_save_cmd_argument = save_cmd_argument;
	arg_parser_data->fn_usage = print_usage;
	arg_parser_data->input_params = NULL;
	ft_arg_parser(arg_parser_data, argc, argv, options);
	input_params = (t_input_params *)arg_parser_data->input_params;
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	statistics = ft_statistics_initialize();
	gradient_descent_data.theta_file = "/tmp/theta.yml";
	if (input_params->dataset_file)
	{
		linear_regression_data = read_dataset_file(input_params->dataset_file);
		gradient_descent_data.alpha = 0.1;
		gradient_descent_data.theta = theta_initialize();
		create_linear_regression_model(linear_regression_data,
			&gradient_descent_data, statistics);
		ft_vector_remove(&gradient_descent_data.theta);
		linear_regression_data_release(&linear_regression_data);
	}
	statistics_remove(&statistics);
	release_input_params(&input_params);
	ft_event_logging_release(&event_logging_data);
	ft_memdel((void **)&arg_parser_data);
	ft_memdel((void **)&options);
	return (0);
}
