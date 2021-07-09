/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:14:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/09 20:01:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

int	main(int argc, char **argv)
{
	t_arg_parser_data		arg_parser_data;
	char					*options;

	options = "f:h";
	arg_parser_data.fn_initialize_cmd_args = initialize_cmd_args;
	arg_parser_data.fn_save_cmd_argument = save_cmd_argument;
	arg_parser_data.fn_usage = print_usage;
	arg_parser_data.input_params = NULL;
	ft_arg_parser(&arg_parser_data, argc, argv, options);
	return (0);
}
