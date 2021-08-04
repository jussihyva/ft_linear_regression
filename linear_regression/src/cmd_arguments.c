/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:56:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/04 07:57:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./fractol -F <type_of_fractal>\n");
	ft_printf("\n\n Example:   ./fractol -F j\n");
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  -F <type_of_fractal>\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h    Help printout\n");
	ft_printf("\n\n   <type_of_fractal>\n");
	ft_printf("  j     Julia      (z = z^2 + C.");
	ft_printf(" C = Constant values + mouse locaation on the image.)\n");
	ft_printf("  m     Mandelbrot (z = z^2 + C.");
	ft_printf(" C = Mouse Distance from the origin of the image.)\n");
	ft_printf("  p     Polynomial (z = z^2 - C.");
	ft_printf(" C = 1 + mouse locaation on the image.)\n");
	exit(42);
}

void	*initialize_cmd_args(t_argc_argv *argc_argv)
{
	t_input_params			*input_params;

	input_params = (t_input_params *)ft_memalloc(sizeof(*input_params));
	input_params->argc = argc_argv->argc;
	input_params->argv = argc_argv->argv;
	input_params->event_logging_level = LOG_WARN;
	return ((void *)input_params);
}

void	save_cmd_argument_short(void *input_params, char opt,
														t_argc_argv *argc_argv)
{
	t_input_params		*params;
	char				*endptr;
	char				*next_arg;

	next_arg = *argc_argv->argv;
	params = (t_input_params *)input_params;
	if (opt == 'f')
	{
		params->dataset_file = next_arg;
		params->order |= E_CALCULATE_UNKNOWN_VARIABLES;
	}
	else if (opt == 'L')
	{
		params->event_logging_level
			= (t_loging_level)ft_strtoi(next_arg, &endptr, 10);
		if (params->event_logging_level >= 6 || params->event_logging_level < 0
			|| *endptr != '\0' || errno != 0)
		{
			ft_printf("Value of cmd line attribute -L (%s) is not valid\n",
				next_arg);
			exit(42);
		}
	}
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
