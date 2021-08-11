/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:56:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 18:38:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	*initialize_cmd_args(t_argc_argv *argc_argv)
{
	t_input_params			*input_params;

	input_params = (t_input_params *)ft_memalloc(sizeof(*input_params));
	input_params->argc = argc_argv->argc;
	input_params->argv = argc_argv->argv;
	input_params->event_logging_level = LOG_WARN;
	input_params->is_limited = E_TRUE;
	input_params->alpha = 0.1;
	input_params->cost_limit = COST_LIMIT;
	return ((void *)input_params);
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
		params->event_logging_level = ft_logging_level_param_validate(next_arg);
	else if (opt == 'A')
		params->alpha = alpha_param_validate(next_arg);
	else if (opt == 'C')
		params->cost_limit = cost_param_validate(next_arg);
	else if (opt == 'F')
		params->is_limited = E_FALSE;
	else if (opt == 'l')
		params->is_print_leaks = E_TRUE;
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
