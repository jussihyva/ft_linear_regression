/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:56:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/10 19:36:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./ft_linear_regression\n");
	ft_printf("\n\n Example:\n");
	ft_printf("  ./ft_linear_regression\n");
	ft_printf("  Type mileage (int) of the car: 10000\n");
	ft_printf("  Estimated price: $8280\n");
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  None\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h                            Help printout\n");
	ft_printf("  -f    <data set file>         %s\n",
		"Calculates unknown variables (Theta values)");
	ft_printf("  -F                            %s\n",
		"Allow calculation of negative inpput values and results");
	ft_printf("  -A    <learning rate>         %s\n",
		"Learning rate (alpha) for gradient descent. Default value is 0.1");
	ft_printf("  -L    <logging level>         %s\n",
		"Logging details for trouble shoooting. Valid values 0-4");
	exit(42);
}

void	*initialize_cmd_args(t_argc_argv *argc_argv)
{
	t_input_params			*input_params;

	input_params = (t_input_params *)ft_memalloc(sizeof(*input_params));
	input_params->argc = argc_argv->argc;
	input_params->argv = argc_argv->argv;
	input_params->event_logging_level = LOG_WARN;
	input_params->is_limited = E_TRUE;
	input_params->alpha = 0.1;
	return ((void *)input_params);
}

static t_loging_level	logging_level_param_validate(char *next_arg)
{
	char				*endptr;
	t_loging_level		event_logging_level;

	errno = 0;
	event_logging_level = (t_loging_level)ft_strtoi(next_arg, &endptr, 10);
	if (event_logging_level >= 5 || event_logging_level < 0
		|| *endptr != '\0' || errno != 0)
	{
		ft_printf("Value of cmd line attribute -L (%s) is not valid\n",
			next_arg);
		exit(42);
	}
	return (event_logging_level);
}

static double	alpha_param_validate(char *next_arg)
{
	char		*endptr;
	double		alpha;

	errno = 0;
	alpha = strtod(next_arg, &endptr);
	if (alpha >= 50000 || alpha < -50000 || *endptr != '\0' || errno != 0)
	{
		ft_printf("Value of cmd line attribute -A (%s) is not valid\n",
			next_arg);
		exit(42);
	}
	return (alpha);
}

void	save_cmd_argument_short(void *input_params, char opt,
														t_argc_argv *argc_argv)
{
	t_input_params		*params;
	char				*next_arg;

	next_arg = *argc_argv->argv;
	params = (t_input_params *)input_params;
	if (opt == 'f')
	{
		params->dataset_file = next_arg;
		params->order |= E_CALCULATE_UNKNOWN_VARIABLES;
	}
	else if (opt == 'L')
		params->event_logging_level = logging_level_param_validate(next_arg);
	else if (opt == 'A')
		params->alpha = alpha_param_validate(next_arg);
	else if (opt == 'F')
		params->is_limited = E_FALSE;
	else if (opt == 'h')
		print_usage();
	return ;
}

void	save_cmd_argument_mandatory(void *input_params, char opt,
														t_argc_argv *argc_argv)
{
	t_input_params		*params;
	char				*endptr;

	(void)opt;
	params = (t_input_params *)input_params;
	if (argc_argv->argc == 1)
	{
		errno = 0;
		params->km = ft_strtoi(*argc_argv->argv, &endptr, 10);
		if (*endptr != '\0' || errno != 0)
		{
			ft_printf("km param (%s) is not valid\n", *argc_argv->argv);
			exit(42);
		}
		params->order |= E_CALCULATE_PRICE;
	}
	else
		print_usage();
	return ;
}

void	save_cmd_argument(void *input_params, char opt, t_argc_argv *argc_argv,
												t_cmd_param_type cmd_param_type)
{
	if (cmd_param_type == E_OPTIONAL_SHORT)
		save_cmd_argument_short(input_params, opt, argc_argv);
	else
		save_cmd_argument_mandatory(input_params, opt, argc_argv);
	return ;
}

void	release_input_params(t_input_params **input_params)
{
	ft_memdel((void **)input_params);
	return ;
}
