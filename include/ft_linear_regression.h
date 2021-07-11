/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:19:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/11 18:16:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINEAR_REGRESSION_H
# define FT_LINEAR_REGRESSION_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

typedef struct s_loging_data
{
	const char	**level_strings;
	const char	**level_colors;
}				t_loging_data;

typedef struct s_input_params
{
	int		argc;
	char	**argv;
	char	*dataset_file;
}				t_input_params;

typedef struct s_data_record
{
	int		km;
	int		price;
}				t_data_record;

void		*initialize_cmd_args(int argc, char **argv);
void		save_cmd_argument(void *input_params, char opt, char *next_arg);
void		print_usage(void);
t_list		**read_dataset_file(char *dataset_file);
void		release_input_params(t_input_params **input_params);

#endif
