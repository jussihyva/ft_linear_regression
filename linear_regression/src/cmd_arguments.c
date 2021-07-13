/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:56:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/13 11:49:01 by jkauppi          ###   ########.fr       */
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

void	*initialize_cmd_args(int argc, char **argv)
{
	t_input_params			*input_params;

	input_params = (t_input_params *)ft_memalloc(sizeof(*input_params));
	input_params->argc = argc;
	input_params->argv = argv;
	return ((void *)input_params);
}

void	save_cmd_argument(void *input_params, char opt, char *next_arg)
{
	t_input_params		*params;
	char				*endptr;

	params = (t_input_params *)input_params;
	if (opt == 'f')
		params->dataset_file = next_arg;
	else if (opt == 'L')
	{
		params->event_logging_level
			= (t_loging_level)ft_strtoi(next_arg, &endptr, 10);
		if (params->event_logging_level >= 6 || params->event_logging_level < 0
			|| *endptr != '\0' || errno != 0)
		{
			ft_printf("Value of cmd line attribute -L (%d) is not valid\n",
				params->event_logging_level);
			exit(42);
		}
	}
	else if (opt == 'h')
		print_usage();
	return ;
}

void	release_input_params(t_input_params **input_params)
{
	ft_memdel((void **)input_params);
	return ;
}
