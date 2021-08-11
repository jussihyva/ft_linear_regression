/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 10:57:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

#if DARWIN
static void	print_leaks(void)
{
	system("leaks ft_linear_regression");
	return ;
}
#else

static void	print_leaks(void)
{
	return ;
}
#endif

static t_arg_parser	*arg_parser_initialize(int argc, char **argv)
{
	t_arg_parser	*arg_parser;

	arg_parser = (t_arg_parser *)ft_memalloc(sizeof(*arg_parser));
	arg_parser->argc_argv.argc = argc;
	arg_parser->argc_argv.argv = argv;
	arg_parser->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser->fn_save_cmd_argument = save_cmd_argument;
	arg_parser->fn_usage = print_usage;
	arg_parser->options = ft_strdup("C:A:L:f:hFll");
	return (arg_parser);
}

static void	main_remove(t_arg_parser *arg_parser,
			t_statistics *statistics, t_event_logging_data *event_logging_data)
{
	t_bool		is_print_leaks;

	is_print_leaks
		= ((t_input_params *)arg_parser->input_params)->is_print_leaks;
	statistics_remove(&statistics);
	release_input_params((t_input_params **)&arg_parser->input_params);
	ft_event_logging_release(&event_logging_data);
	ft_memdel((void **)&arg_parser->options);
	ft_memdel((void **)&arg_parser);
	if (is_print_leaks)
		print_leaks();
	return ;
}

static double	statistics_price_prediction(int km, double **theta_values,
									t_statistics *statistics, t_bool is_limited)
{
	t_stat_counters		*stat_counters;
	t_list				*elem;

	stat_counters = stat_counters_initialize();
	stat_counters->value[E_INDEPENDENT] = km;
	stat_counters->value[E_PREDICTED_PRICE]
		= calculate_price(km, theta_values);
	stat_counters->value[E_DEPENDENT]
		= stat_counters->value[E_PREDICTED_PRICE];
	if (is_limited)
	{
		if (km < 0)
			FT_LOG_ERROR("km is below 0.");
		if (stat_counters->value[E_PREDICTED_PRICE] < 0)
			FT_LOG_ERROR("Predicted price is below 0.");
	}
	elem = ft_lstnew(&stat_counters, sizeof(stat_counters));
	ft_lstadd(&statistics->stat_counters_lst, elem);
	return (stat_counters->value[E_PREDICTED_PRICE]);
}

static void	unknown_variables_calculate(t_lin_reg *linear_regression,
					char *dataset_file, t_statistics *statistics)
{
	if (linear_regression->dataset->num_of_records)
		create_linear_regression_model(linear_regression, statistics);
	else
		FT_LOG_ERROR("No records in the input file (%s)", dataset_file);
	ft_printf("THETA0: %12.4f\n",
		((double **)linear_regression->gradient_descent->theta->values)[0][0]);
	ft_printf("THETA1: %12.4f\n",
		((double **)linear_regression->gradient_descent->theta->values)[1][0]);
	coefficient_of_determination_calculate(linear_regression);
	return ;
}

static void	dependent_variable_calculate(t_input_params *input_params,
													t_statistics *statistics)
{
	double		price;
	t_matrix	*theta;

	theta = unknown_variables_read();
	price = statistics_price_prediction(input_params->km,
			(double **)theta->values, statistics, input_params->is_limited);
	ft_printf("Estimated price: $%.0f\n", price);
	ft_matrix_remove(&theta);
	return ;
}

static int	read_mileage_of_the_car(t_input_params *input_params)
{
	char	*endptr;
	char	*line;
	int		km;

	input_params->order = E_CALCULATE_PRICE;
	line = NULL;
	ft_printf("Type mileage (int) of the car: ");
	ft_get_next_line(0, &line);
	errno = 0;
	km = ft_strtoi(line, &endptr, 10);
	if (*endptr != '\0' || errno != 0)
	{
		ft_printf("km param (%s) is not valid\n", line);
		exit(42);
	}
	ft_strdel(&line);
	return (km);
}

int	main(int argc, char **argv)
{
	t_arg_parser			*arg_parser;
	t_lin_reg				*linear_regression;
	t_event_logging_data	*event_logging_data;
	t_statistics			*statistics;
	t_input_params			*input_params;

	arg_parser = arg_parser_initialize(argc, argv);
	ft_arg_parser(arg_parser);
	input_params = (t_input_params *)arg_parser->input_params;
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	statistics = ft_statistics_initialize();
	if (!input_params->order)
		input_params->km = read_mileage_of_the_car(input_params);
	linear_regression = linear_regression_initialize(input_params);
	if (input_params->order & E_CALCULATE_UNKNOWN_VARIABLES)
		unknown_variables_calculate(linear_regression,
			input_params->dataset_file, statistics);
	if (input_params->order & E_CALCULATE_PRICE)
		dependent_variable_calculate(input_params, statistics);
	statistics_save_records(statistics);
	linear_regression_release(&linear_regression);
	main_remove(arg_parser, statistics, event_logging_data);
	return (0);
}
