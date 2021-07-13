/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:19:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/13 17:00:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINEAR_REGRESSION_H
# define FT_LINEAR_REGRESSION_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

typedef struct s_file_params
{
	int		fd;
	int		ret;
	char	*line;
}				t_file_params;

typedef struct s_input_params
{
	int				argc;
	char			**argv;
	char			*dataset_file;
	t_loging_level	event_logging_level;
}				t_input_params;

typedef struct s_data_record
{
	int		km;
	int		price;
}				t_data_record;

typedef struct s_lin_reg_data
{
	t_list		**data_record_lst;
	int			num_of_records;
	int			sum_km;
	int			sum_price;
	int			*vec_observed_values_price;
	double		*error_variable;
	int			*input_variables;
}				t_lin_reg_data;

void			*initialize_cmd_args(int argc, char **argv);
void			save_cmd_argument(void *input_params, char opt,
					char *next_arg);
void			print_usage(void);
t_lin_reg_data	*read_dataset_file(char *dataset_file);
void			release_input_params(t_input_params **input_params);
void			release_data_record_lst(t_list **data_record_lst);
void			linear_regression_data_release(
					t_lin_reg_data **linear_regression_data);
void			linear_regression_add_data_record(
					t_lin_reg_data *linear_regression_data,
					t_data_record *data_record);
void			perform_linear_regression_data(
					t_lin_reg_data *linear_regression_data);

#endif
