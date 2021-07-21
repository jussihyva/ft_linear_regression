/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_addons.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:53:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/21 11:11:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ADDONS_H
# define LIBFT_ADDONS_H
# include "libft_addons_against_norm.h"
# include "libft.h"
# include "ft_printf.h"
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <openssl/ssl.h>
# include <openssl/err.h>

# define MAX_LOGING_EXTENSIONS		32
# define PI							3.141592654
# define LOGING_LEVELS				6
# define MAX_NUM_OF_B_TREE_ELEMS	10

typedef enum e_loging_level
{
	LOG_TRACE = 0,
	LOG_DEBUG = 1,
	LOG_INFO = 2,
	LOG_WARN = 3,
	LOG_ERROR = 4,
	LOG_FATAL = 5
}				t_loging_level;

typedef struct s_event_logging_data
{
	const char	**level_strings;
	const char	**level_colors;
}				t_event_logging_data;

# if DARWIN
typedef struct s_timeval
{
	__darwin_time_t			tv_sec;
	__darwin_suseconds_t	tv_usec;
}									t_timeval;
# else
typedef struct s_timeval
{
	__kernel_time_t			tv_sec;
	__kernel_suseconds_t	tv_usec;
}									t_timeval;
# endif

typedef struct s_tls_connection
{
	int			socket_fd;
	SSL_CTX		*ctx;
	SSL			*ssl_bio;
}				t_tls_connection;

typedef struct s_matrix_size
{
	size_t		rows;
	size_t		columns;
}				t_matrix_size;

typedef struct s_log_event
{
	va_list			ap;
	const char		*fmt;
	const char		*file;
	struct timeval	tv;
	void			*additional_event_data;
	int				line;
	int				level;
}				t_log_event;

typedef void	(*t_loging_function)(t_log_event *event);
typedef void	(*t_loging_lock_function)(int lock, void *udata);

typedef struct s_loging_extension
{
	t_loging_function	fn;
	void				*additional_event_data;
	int					level;
}				t_loging_extension;

typedef struct s_loging_params
{
	void					*udata;
	t_loging_lock_function	lock;
	int						level;
	int						quiet;
	const char				**level_strings;
	const char				**level_colors;
	t_loging_extension		*loging_extensions[MAX_LOGING_EXTENSIONS];
}				t_loging_params;

typedef struct s_queue
{
	t_list		**in_stack;
	t_list		**out_stack;
}				t_queue;

typedef struct s_bt_key
{
	void				*key;
	size_t				key_size;
}				t_bt_key;

typedef struct s_bt_data
{
	void				*data;
	size_t				data_size;
}				t_bt_data;

typedef struct s_bt_elem
{
	int					is_queue;
	t_bt_data			bt_data;
	t_bt_key			bt_key;
	struct s_bt_node	*left_child;
	struct s_bt_node	*right_child;
}				t_bt_elem;

typedef struct s_bt_node
{
	int					num_of_elems;
	t_bt_elem			bt_elem[MAX_NUM_OF_B_TREE_ELEMS];
}				t_bt_node;

typedef void	(*t_save_cmd_argument)(void*, char, char*);

typedef void*	(*t_initialize_cmd_args)(int argc, char **argv);

typedef void	(*t_usage)(void);

typedef struct s_arg_parser_data
{
	t_initialize_cmd_args	fn_initialize_cmd_args;
	t_save_cmd_argument		fn_save_cmd_argument;
	t_usage					fn_usage;
	void					*input_params;
}				t_arg_parser_data;

void					ft_log_trace(const char *file, const int line,
							const char *fmt, ...);
void					ft_log_debug(const char *file, const int line,
							const char *fmt, ...);
void					ft_log_info(const char *file, const int line,
							const char *fmt, ...);
void					ft_log_warn(const char *file, const int line,
							const char *fmt, ...);
void					ft_log_error(const char *file, const int line,
							const char *fmt, ...);
void					ft_log_fatal(const char *file, const int line,
							const char *fmt, ...);
void					ft_log_set_lock(t_loging_lock_function fn, void *udata);
void					ft_log_set_level(int level);
/*
** void			log_set_quiet(int enable);
*/
int						ft_log_add_fd(int *fd, int level);
void					ft_log_set_params(const char **level_strings,
							const char **level_colors);
void					set_g_loging_params_2(t_loging_params *loging_params);
void					set_g_loging_params_3(t_loging_params *loging_params);
void					set_g_loging_params_4(t_loging_params *loging_params);
void					set_g_loging_params_5(t_loging_params *loging_params);
t_event_logging_data	*ft_event_logging_init(t_loging_level event_type);
void					ft_event_logging_release(
							t_event_logging_data **event_logging_data);
double					ft_radian(double angle_degree);
int						ft_max_int(int nbr1, int nbr2);
int						ft_min_int(int nbr1, int nbr2);
double					ft_max_double(double nbr1, double nbr2);
double					ft_min_double(double nbr1, double nbr2);
double					ft_mod_double(double dividend, double divisor);
int						ft_mod_int(int dividend, int divisor);
void					ft_matrix_x_vector_double(t_matrix_size *matrix_size,
							double **matrix, double *vector,
							double **new_vector);
int						ft_isdigit_base(int c, int base);
int						ft_strtoi(const char *str, char **endptr, int base);
void					stdout_callback(t_log_event *event);
void					unlock(void);
void					lock(void);
void					file_callback(t_log_event *event);
void					execute_login_extensions(t_log_event *event,
							const char *fmt, ...);
int						ft_log_add_callback(t_loging_function fn,
							void *additional_event_data, int level);
void					ft_release_loging_params(void);
void					ft_openssl_init(void);
SSL_CTX					*ft_openssl_init_ctx(const SSL_METHOD	*tls_method,
							char *pem_cert_file, char *pem_private_key_file);
SSL_CTX					*ft_openssl_init_client(char *pem_cert_file,
							char *pem_private_key_file, int *socket_fd);
t_tls_connection		*ft_openssl_connect(char *hostname, char *port,
							int socket_fd, SSL_CTX *ctx);
void					ft_openssl_rel_conn(t_tls_connection **connection);
void					ft_stack_push(t_list **stack, void *data);
void					*ft_stack_pop(t_list **stack);
void					ft_enqueue(t_queue *queue, void *data);
void					*ft_dequeue(t_queue *queue);
int						ft_is_queue_empty(t_queue *queue);
t_queue					*ft_queue_init(void);
void					ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data,
							t_bt_node **bt_root);
void					ft_bt_print(t_bt_node *bt_node, int *count);
int						find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node,
							t_bt_data *bt_data);
void					ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root,
							t_bt_data *return_bt_data);
void					ft_bt_remove(t_bt_node **bt_node, t_bt_key *bt_key,
							void ((*fn)(void *data, size_t size)));
int						search_key_position(t_bt_node *bt_node,
							t_bt_key *bt_key, t_bt_data *bt_data);
void					split_node(t_bt_node **bt_node, t_bt_node **parent,
							t_bt_key *bt_key);
void					ft_prio_enqueue(t_bt_node **states_prio_queue,
							int *prio, void *puzzle_status);
void					*ft_prio_dequeue(t_bt_node **states_prio_queue);
void					ft_print_memory(const void *addr, size_t size);
int						ft_open_fd(char *file_path);
void					ft_arg_parser(t_arg_parser_data *arg_parser_data,
							int argc, char **argv, char *options);

#endif
