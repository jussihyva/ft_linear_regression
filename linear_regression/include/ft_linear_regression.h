/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:19:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/22 13:05:06 by jkauppi          ###   ########.fr       */
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

typedef struct s_min_max_value
{
	void	*min_value;
	void	*max_value;
}				t_min_max_value;

typedef struct s_variable
{
	char				*name;
	size_t				size;
	void				*values;
	t_min_max_value		min_max_value;
	double				**normalized_values;
	double				**standardized_values_not_implemented_yet;
	double				**matrix;
	t_matrix_size		matrix_size;
}				t_variable;

typedef struct s_measured_variables
{
	t_variable		price;
}				t_measured_variables;

typedef struct s_input_variables
{
	t_variable		km;
}				t_input_variables;

typedef struct s_lin_reg_data
{
	t_list					**data_record_lst;
	size_t					num_of_records;
	t_input_variables		input_variables;
	t_measured_variables	measured_variables;
}				t_lin_reg_data;

typedef struct s_error_data
{
	double		**error;
	double		error_sum;
}				t_error_data;

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
void			pre_process_input_variables(
					t_lin_reg_data *linear_regression_data);
void			pre_process_observed_values(
					t_lin_reg_data *linear_regression_data);
double			**theta_initialize(void);
double			**matrix_initialize(t_variable *km, t_matrix_size *matrix_size);
void			calculate_error(double alpha, double **theta,
					t_variable *input_variable, t_variable *measured_variable);
void			ft_matrix_subtrack_vector_double(t_matrix_size *matrix_size,
					double **matrix, double **vector, double **new_vector);
void			**ft_create_vector(size_t size, size_t vector_size);
double			ft_matrix_sum(t_matrix_size *matrix_size, double **matrix);
void			ft_matrix_dot_vector_double(t_matrix_size *matrix_size,
					double **matrix, double **vector, double **new_vector);

#endif
