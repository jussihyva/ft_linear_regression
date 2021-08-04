/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/04 07:59:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static t_arg_parser	*arg_parser_initialize(int argc, char **argv)
{
	t_arg_parser	*arg_parser;

	arg_parser = (t_arg_parser *)ft_memalloc(sizeof(*arg_parser));
	arg_parser->argc_argv.argc = argc;
	arg_parser->argc_argv.argv = argv;
	arg_parser->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser->fn_save_cmd_argument = save_cmd_argument;
	arg_parser->fn_usage = print_usage;
	arg_parser->options = ft_strdup("L:f:h");
	ft_arg_parser(arg_parser);
	return (arg_parser);
}

static void	main_remove(t_arg_parser *arg_parser,
			t_statistics *statistics, t_event_logging_data *event_logging_data)
{
	statistics_remove(&statistics);
	release_input_params((t_input_params **)&arg_parser->input_params);
	ft_event_logging_release(&event_logging_data);
	ft_memdel((void **)&arg_parser->options);
	ft_memdel((void **)&arg_parser);
	return ;
}

static void	statistics_price_prediction(int km, double **theta_values,
													t_statistics *statistics)
{
	t_stat_counters		*stat_counters;
	t_list				*elem;

	stat_counters = stat_counters_initialize();
	stat_counters->value[E_INDEPENDENT] = km;
	stat_counters->value[E_PREDICTED_PRICE]
		= calculate_price(km, theta_values);
	stat_counters->value[E_DEPENDENT]
		= stat_counters->value[E_PREDICTED_PRICE];
	elem = ft_lstnew(&stat_counters, sizeof(stat_counters));
	ft_lstadd(&statistics->stat_counters_lst, elem);
	return ;
}

int	main(int argc, char **argv)
{
	t_arg_parser			*arg_parser;
	t_lin_reg				*linear_regression;
	t_event_logging_data	*event_logging_data;
	t_statistics			*statistics;
	t_input_params			*input_params;

	arg_parser = arg_parser_initialize(argc, argv);
	input_params = (t_input_params *)arg_parser->input_params;
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	statistics = ft_statistics_initialize();
	linear_regression = linear_regression_initialize();
	if (input_params->order & E_CALCULATE_UNKNOWN_VARIABLES)
	{
		linear_regression->dataset
			= read_dataset_file(input_params->dataset_file);
		if (linear_regression->dataset->num_of_records)
		{
			create_linear_regression_model(linear_regression, statistics);
			if (input_params->km)
				statistics_price_prediction(input_params->km,
					(double **)linear_regression->gradient_descent->theta
					->values, statistics);
		}
		else
			FT_LOG_ERROR("No record in the input file (%s)",
				input_params->dataset_file);
	}
	if (input_params->order & E_CALCULATE_PRICE)
	{
		linear_regression->gradient_descent = gradient_descent_initialize();
		linear_regression->gradient_descent->theta = unknown_variables_read();
		statistics_price_prediction(input_params->km,
			(double **)linear_regression->gradient_descent->theta->values,
			statistics);
	}
	if (statistics->stat_counters_lst)
		statistics_save_records(statistics);
	linear_regression_release(&linear_regression);
	main_remove(arg_parser, statistics, event_logging_data);
	return (0);
}
