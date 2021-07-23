/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linear_regression.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:19:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/23 19:17:59 by jkauppi          ###   ########.fr       */
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

# define	NUM_OF_STAT_COUNTERS	18

typedef enum e_stat_counter_name
{
	E_PUZZLE_INITIAL_STATE,
	E_PUZZLE_FINAL_STATE,
	E_IS_PUZZLE_SOLVABLE,
	E_IS_PUZZLE_SOLVED,
	E_IS_TIME_LIMIT_REACHED,
	E_IS_MEM_LIMIT_REACHED,
	E_NUM_OF_SOLUTION_MOVES,
	E_EXECUTION_TIME,
	E_TOTAL_CPU_USAGE_TIME,
	E_SOLVER_CPU_USAGE_TIME,
	E_PRINTING_CPU_USAGE_TIME,
	E_TOTAL_NUM_OF_PUZZLE_STATES,
	E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS,
	E_MAX_NUM_OF_SAVED_PUZZLE_STATES,
	E_MAX_QUEUE_LEN,
	E_TOTAL_NUM_OF_ELEM_IN_QUEUE,
	E_MAX_MEM_USAGE,
	E_MIN_FREE_MEM
}				t_stat_counter_name;

typedef struct s_stat_counters
{
	char				*counter_names[NUM_OF_STAT_COUNTERS];
	int					value[NUM_OF_STAT_COUNTERS];
	long				is_active[NUM_OF_STAT_COUNTERS];
}				t_stat_counters;

typedef struct s_statistics
{
	char				*algorithm;
	char				*algorithm_substring;
	struct timespec		start_time;
	struct timespec		end_time;
	time_t				start_time_ms;
	time_t				end_time_ms;
	clock_t				cpu_usage_ms;
	t_tls_connection	*connection;
	int					solution_move_cnt;
	int					puzzle_size;
	int					puzzle_states_cnt;
	int					puzzle_state_collision_cnt;
	t_stat_counters		stat_counters;
	int					solver_start_time_ms;
	int					solver_end_time_ms;
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
double			**theta_initialize(void);
double			**matrix_initialize(t_variable *km);
void			calculate_error(double alpha, double **theta,
					t_variable *input_variable, t_variable *measured_variable);
void			ft_matrix_subtrack_vector_double(t_matrix_size *matrix_size,
					double **matrix, double **vector, double **new_vector);
void			**ft_vector_create(size_t size, size_t vector_size);
void			ft_vector_remove(void ***vector, size_t vector_size);
double			ft_matrix_sum(t_matrix_size *matrix_size, double **matrix);
void			ft_matrix_dot_vector_double(t_matrix_size *matrix_size,
					double **matrix, double **vector, double **new_vector);
double			**variable_normalize(void *values,
					t_min_max_value *min_max_value, size_t num_of_records);
void			variable_remove(t_variable *variable);
time_t			get_execution_time(t_statistics *statistics);
void			write_influxdb(t_tls_connection *connection, char *body,
					char *database);

#endif
