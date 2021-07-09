/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:19:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/09 19:59:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINEAR_REGRESSION_H
# define FT_LINEAR_REGRESSION_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

typedef struct s_input_params
{
	int		argc;
	char	**argv;
}				t_input_params;

void		*initialize_cmd_args(int argc, char **argv);
void		save_cmd_argument(void *input_params, char opt, char *next_arg);
void		print_usage(void);

#endif
