/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:19:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/02 23:32:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINEAR_REGRESSION_H
# define FT_LINEAR_REGRESSION_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <sys/resource.h>

# if DARWIN
#  include <sys/sysctl.h>
#  define OS					"DARWIN"
# else
#  include <sys/sysinfo.h>
#  define OS					"LINUX"
# endif

# define MILLI_SECONDS					1000
# define MINUTE							60
# define EXECUTION_TIME_LIMIT_MIN		5
# define SEND_REC_BUF_MAX_SIZE			4096
# define PEM_CERT_FILE					"/var/tmp/tls-selfsigned.crt"
# define PEM_PRIVTE_KEY_FILE			"/var/tmp/tls-selfsigned.key"
# define WRITE_BUF_SIZE					1000

typedef struct s_memory_info
{
	int				mem_limit;
	long			usage_prev;
	struct rusage	rusage;
	struct rlimit	rlim;
	long			av_phys_pages;
	long			tot_phys_pages;
	int				mem_usage;

}						t_memory_info;

typedef enum e_connection_status
{
	E_IDLE,
	E_CONNECTED
}						t_connection_status;

typedef struct s_influxdb
{
	void					*connection;
	t_connection_status		connection_status;
}						t_influxdb;

# define	NUM_OF_STAT_COUNTERS	3

typedef enum e_stat_counter_name
{
	E_INDEPENDENT,
	E_DEPENDENT,
	E_PREDICTED_PRICE
}				t_stat_counter_name;

typedef struct s_stat_counters
{
	char				*counter_names[NUM_OF_STAT_COUNTERS];
	double				value[NUM_OF_STAT_COUNTERS];
	long				is_active[NUM_OF_STAT_COUNTERS];
}				t_stat_counters;

typedef struct s_statistics
{
	t_influxdb			*influxdb;
	char				*data_type;
	int					id;
	struct timespec		end_time;
	time_t				end_time_ms;
	t_tls_connection	*connection;
	t_list				*stat_counters_lst;
}				t_statistics;

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
	int				km;
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
	void	*range;
}				t_min_max_value;

typedef struct s_matrix
{
	t_matrix_size	size;
	void			**values;
}				t_matrix;

typedef struct s_variable
{
	char				*name;
	size_t				size;
	void				*values;
	t_min_max_value		min_max_value;
	t_matrix			*normalized_values;
	t_matrix			*standardized_values_not_implemented_yet;
	t_matrix			*matrix;
}				t_variable;

typedef struct s_measured_variables
{
	t_variable		price;
}				t_measured_variables;

typedef struct s_input_variables
{
	t_variable		km;
}				t_input_variables;

typedef struct s_gradient_descent_data
{
	double		alpha;
	t_matrix	*theta;
	char		*theta_file;
}				t_gradient_descent_data;

typedef struct s_lin_reg_data
{
	t_list						*data_record_lst;
	size_t						num_of_records;
	t_input_variables			input_variables;
	t_measured_variables		measured_variables;
	t_variable					predicted_price;
	double						*theta_values;
}				t_lin_reg_data;

typedef struct s_error_data
{
	t_matrix	*error;
	double		error_sum;
}				t_error_data;

void					*initialize_cmd_args(t_argc_argv *argc_argv);
void					save_cmd_argument(void *input_params, char opt,
							t_argc_argv *argc_argv,
							t_cmd_param_type cmd_param_type);
void					print_usage(void);
t_lin_reg_data			*read_dataset_file(char *dataset_file);
void					release_input_params(t_input_params **input_params);
void					release_data_record_lst(t_list **data_record_lst);
void					linear_regression_data_release(
							t_lin_reg_data **linear_regression_data);
void					linear_regression_add_data_record(
							t_lin_reg_data *linear_regression_data,
							t_data_record *data_record);
void					create_linear_regression_model(
							t_lin_reg_data *linear_regression_data,
							t_statistics *statistics);
void					pre_process_input_variables(
							t_lin_reg_data *linear_regression_data);
t_matrix				*theta_initialize(void);
t_matrix				*matrix_initialize(t_variable *km);
void					calculate_new_theta(
							t_gradient_descent_data *gradient_descent_data,
							t_variable *input_variable,
							t_variable *measured_variable,
							double **new_theta_values);
void					ft_matrix_subtrack_vector_double(t_matrix *matrix,
							t_matrix *vector, t_matrix *new_vector);
t_matrix				*ft_vector_create(size_t size, size_t vector_size);
void					ft_vector_remove(t_matrix **vector);
void					ft_matrix_remove(t_matrix **matrix);
double					ft_matrix_sum(t_matrix *matrix);
void					ft_matrix_dot_vector_double(t_matrix *matrix,
							t_matrix *vector, t_matrix *new_vector);
t_matrix				*variable_normalize(int *values,
							t_min_max_value *min_max_value,
							size_t num_of_records);
void					variable_remove(t_variable *variable);
time_t					get_execution_time(t_statistics *statistics);
void					ft_influxdb_write(t_tls_connection *connection,
							char *body, char *database);
t_influxdb				*ft_influxdb_connect(char *host_name, char *port_number,
							t_statistics *statistics);
t_statistics			*ft_statistics_initialize(void);
void					ft_influxdb_write(t_tls_connection *connection,
							char *body, char *database);
char					*create_influxdb_query_string(
							t_stat_counters *stat_counters,
							struct timespec end_time, char *data_type, int id);
void					stat_set_end_time(t_statistics *statistics);
void					initalize_variable(t_variable *variable,
							size_t num_of_records, size_t size);
t_matrix				*ft_matrix_transpose(t_matrix *matrix);
void					statistics_remove(t_statistics **statistics);
t_gradient_descent_data	*unknown_variables_iterate_values(
							t_variable *input_variable,
							t_variable *measured_variable);
void					statistics_create_records(t_list **stat_counters_lst,
							t_lin_reg_data *linear_regression_data);
void					statistics_save_records(t_statistics *statistics);
void					statistics_release_record(void *content, size_t size);
void					save_unknown_variables(double **theta_values);
const char				*get_home_dir(void);
double					calculate_price(int km, double theta0, double theta1);
t_stat_counters			*stat_counters_initialize(void);

#endif
