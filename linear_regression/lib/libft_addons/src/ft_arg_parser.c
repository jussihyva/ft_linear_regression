/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:42:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/03 11:49:15 by jkauppi          ###   ########.fr       */
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

static void	pre_analyse_argument(char *options, char arg,
														t_argc_argv *argc_argv)
{
	char					*opt_ptr;

	opt_ptr = ft_strchr(options, arg);
	if (opt_ptr)
	{
		if (*(opt_ptr + 1) == ':')
		{
			if (argc_argv->argc < 2)
				param_error("Missing argument for parameter: -%c", arg);
			argc_argv->argc--;
			argc_argv->argv++;
		}
	}
	else
		param_error("Unknown parameter: -%c", arg);
	return ;
}

static void	split_cmd_argument(t_arg_parser *arg_parser,
							t_argc_argv *argc_argv,
							t_cmd_param_type cmd_param_type)
{
	t_save_cmd_argument		fn_save_cmd_argument;
	char					*arg;
	void					*input_params;

	input_params = arg_parser->input_params;
	fn_save_cmd_argument = arg_parser->fn_save_cmd_argument;
	arg = *argc_argv->argv;
	if (cmd_param_type == E_OPTIONAL_SHORT)
	{
		arg++;
		while (*arg)
		{
			pre_analyse_argument(arg_parser->options, *arg, argc_argv);
			fn_save_cmd_argument(input_params, *arg, argc_argv, cmd_param_type);
			arg++;
		}
	}
	else if (cmd_param_type == E_MANDATORY)
		fn_save_cmd_argument(input_params, *arg, argc_argv, cmd_param_type);
	return ;
}

void	ft_arg_parser(t_arg_parser *arg_parser)
{
	int						arg_index;
	t_initialize_cmd_args	initialize_cmd_args;
	t_cmd_param_type		cmd_param_type;
	t_argc_argv				*argc_argv;

	argc_argv = &arg_parser->argc_argv;
	initialize_cmd_args = arg_parser->fn_initialize_cmd_args;
	arg_parser->input_params
		= (void *)initialize_cmd_args(&arg_parser->argc_argv);
	arg_index = 0;
	argc_argv->argc--;
	while (argc_argv->argc)
	{
		argc_argv->argv++;
		if (ft_strlen(*argc_argv->argv) > 2
			&& (*argc_argv->argv)[0] == '-' && (*argc_argv->argv)[1] == '-')
			cmd_param_type = E_OPTIONAL_LONG;
		else if (ft_strlen(*argc_argv->argv) > 1
			&& (*argc_argv->argv)[0] == '-')
			cmd_param_type = E_OPTIONAL_SHORT;
		else
			cmd_param_type = E_MANDATORY;
		split_cmd_argument(arg_parser, argc_argv, cmd_param_type);
		argc_argv->argc--;
	}
	return ;
}
