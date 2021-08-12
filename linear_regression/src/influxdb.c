/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:14:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/12 14:20:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static void	set_client_socket_params(int socket_fd)
{
	t_timeval		timeout;
	int				on;

	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	on = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
		sizeof(timeout));
	return ;
}

static t_influxdb	*init_influx_session(void)
{
	t_influxdb	*influxdb;

	influxdb = (t_influxdb *)ft_memalloc(sizeof(*influxdb));
	influxdb->connection_status = E_IDLE;
	return (influxdb);
}

t_influxdb	*ft_influxdb_connect(char *host_name, char *port_number)
{
	SSL_CTX				*ctx;
	int					socket_fd;
	t_influxdb			*influxdb;
	char				*cert_file;
	char				*private_key_file;

	ft_openssl_init();
	influxdb = init_influx_session();
	cert_file = file_path_create(PEM_CERT_FILE);
	private_key_file = file_path_create(PEM_PRIVTE_KEY_FILE);
	ctx = ft_openssl_init_client(cert_file, private_key_file, &socket_fd);
	influxdb->connection = ft_openssl_connect(host_name, port_number, socket_fd,
			ctx);
	if (influxdb->connection)
	{
		set_client_socket_params(socket_fd);
		influxdb->connection_status = E_CONNECTED;
	}
	else
	{
		SSL_CTX_free(ctx);
		FT_LOG_WARN("Connection setup to Influxdb failed!");
	}
	return (influxdb);
}

static void	read_response(SSL *ssl_bio)
{
	char		*read_buf;
	int			chars;
	clock_t		start;
	clock_t		end;

	read_buf = (char *)ft_memalloc(sizeof(*read_buf) * SEND_REC_BUF_MAX_SIZE);
	start = clock();
	end = start + (CLOCKS_PER_SEC * 2);
	chars = -1;
	while (chars == -1 && end > clock())
		chars = SSL_read(ssl_bio, read_buf, SEND_REC_BUF_MAX_SIZE);
	if (chars == -1)
		FT_LOG_ERROR("%s", "Reading of influxdb response failed!");
	else
	{
		while (chars > 0)
		{
			FT_LOG_TRACE("CHARS: %s", read_buf);
			chars = SSL_read(ssl_bio, read_buf,
					SEND_REC_BUF_MAX_SIZE);
		}
	}
	ft_strdel(&read_buf);
	return ;
}

void	ft_influxdb_write(t_tls_connection *connection, char *body,
																char *database)
{
	char		header[SEND_REC_BUF_MAX_SIZE];

	if (connection)
	{
		sprintf(header,
			"POST /write?db=%s&precision=s %sContent-Length: %ld\r\n\r\n",
			database, "HTTP/1.1\r\nHost: none\r\n", strlen(body));
		SSL_write(connection->ssl_bio, header, strlen(header));
		FT_LOG_TRACE("BODY: %s", body);
		SSL_write(connection->ssl_bio, body, strlen(body));
		read_response(connection->ssl_bio);
	}
	return ;
}
