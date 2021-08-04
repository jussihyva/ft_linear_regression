/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:42:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/04 18:22:34 by jkauppi          ###   ########.fr       */
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

static int	pre_analyse_argument(char *options, char arg,
														t_argc_argv *argc_argv)
{
	char					*opt_ptr;
	int						result;

	opt_ptr = ft_strchr(options, arg);
	if (opt_ptr && arg != ':')
	{
		if (*(opt_ptr + 1) == ':')
		{
			if (argc_argv->argc < 2)
				param_error("Missing argument for parameter: -%c", arg);
			argc_argv->argc--;
			argc_argv->argv++;
		}
		result = 1;
	}
	else
		result = 0;
	return (result);
}

static void	split_cmd_argument(t_arg_parser *arg_parser,
							t_argc_argv *argc_argv,
							t_cmd_param_type cmd_param_type)
{
	t_save_cmd_argument		fn_save_cmd_argument;
	char					*arg;

	fn_save_cmd_argument = arg_parser->fn_save_cmd_argument;
	arg = *argc_argv->argv;
	if (cmd_param_type == E_OPTIONAL_SHORT)
	{
		while (*(++arg))
		{
			if (pre_analyse_argument(arg_parser->options, *arg, argc_argv))
				fn_save_cmd_argument(arg_parser->input_params, *arg, argc_argv,
					cmd_param_type);
			else
			{
				cmd_param_type = E_MANDATORY;
				fn_save_cmd_argument(arg_parser->input_params, *arg, argc_argv,
					cmd_param_type);
				break ;
			}
		}
	}
	else if (cmd_param_type == E_MANDATORY)
		fn_save_cmd_argument(arg_parser->input_params, *arg, argc_argv,
			cmd_param_type);
	return ;
}

void	ft_arg_parser(t_arg_parser *arg_parser)
{
	int						arg_index;
	t_cmd_param_type		cmd_param_type;
	t_argc_argv				*argc_argv;

	argc_argv = &arg_parser->argc_argv;
	arg_parser->input_params
		= (void *)arg_parser->fn_initialize_cmd_args(&arg_parser->argc_argv);
	arg_index = 0;
	while (--argc_argv->argc)
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
	}
	return ;
}
