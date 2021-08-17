/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:58:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/17 16:21:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	influxdb_remove(t_influxdb *influxdb)
{
	if (influxdb->connection)
	{
		SSL_shutdown(((t_tls_connection *)influxdb->connection)->ssl_bio);
		SSL_free(((t_tls_connection *)influxdb->connection)->ssl_bio);
		SSL_CTX_free(((t_tls_connection *)influxdb->connection)->ctx);
		ft_memdel((void **)&influxdb->connection);
	}
	ft_memdel((void **)&influxdb);
	return ;
}
