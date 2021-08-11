/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:14:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 18:18:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_arg_parser	*arg_parser_init(int argc, char **argv)
{
	t_arg_parser	*arg_parser;

	arg_parser = (t_arg_parser *)ft_memalloc(sizeof(*arg_parser));
	arg_parser->argc_argv.argc = argc;
	arg_parser->argc_argv.argv = argv;
	arg_parser->fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser->fn_save_cmd_argument = save_cmd_argument;
	arg_parser->fn_usage = print_usage;
	arg_parser->options = ft_strdup("C:A:L:f:hFl");
	return (arg_parser);
}
