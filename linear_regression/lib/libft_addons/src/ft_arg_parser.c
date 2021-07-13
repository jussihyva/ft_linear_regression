/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:42:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/13 15:29:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	param_error(const char *error_string, const char s)
{
	ft_printf(error_string, s);
	ft_printf("\n");
	exit(42);
	return ;
}

static char	*pre_analyse_argument(char *options, char arg, int *argc,
																char ***argv)
{
	char					*opt_ptr;

	opt_ptr = ft_strchr(options, arg);
	if (opt_ptr)
	{
		if (*(opt_ptr + 1) == ':')
		{
			if (*argc < 2)
				param_error("Missing argument for parameter: -%c", arg);
			(*argc)--;
			(*argv)++;
		}
	}
	else
		param_error("Unknown parameter: -%c", arg);
	return (opt_ptr);
}

static void	split_cmd_argument(
							t_arg_parser_data *arg_parser_data,
							int *argc,
							char ***argv,
							char *options)
{
	t_save_cmd_argument		fn_save_cmd_argument;
	char					*arg;
	void					*input_params;
	char					*opt_ptr;

	input_params = arg_parser_data->input_params;
	fn_save_cmd_argument = arg_parser_data->fn_save_cmd_argument;
	arg = **argv;
	arg++;
	opt_ptr = arg;
	while (*arg && *opt_ptr != ':')
	{
		opt_ptr = pre_analyse_argument(options, *arg, argc, argv);
		fn_save_cmd_argument(input_params, *arg, **argv);
		arg++;
	}
}

void	ft_arg_parser(
					t_arg_parser_data *arg_parser_data,
					int argc,
					char **argv,
					char *options)
{
	int						arg_index;
	t_initialize_cmd_args	initialize_cmd_args;

	initialize_cmd_args = arg_parser_data->fn_initialize_cmd_args;
	arg_parser_data->input_params = (void *)initialize_cmd_args(argc, argv);
	arg_index = 0;
	argc--;
	while (argc)
	{
		argv++;
		if ((*argv)[0] == '-' && ft_strlen(*argv) > 1)
			split_cmd_argument(arg_parser_data, &argc, &argv, options);
		else
			arg_parser_data->fn_usage();
		argc--;
	}
	return ;
}
