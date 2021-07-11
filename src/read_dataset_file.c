/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:52:29 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/11 16:08:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

t_data_set	*read_dataset_file(char *dataset_file)
{
	int				fd;
	t_data_set		*data_set;

	fd = ft_open_fd(dataset_file);
	data_set = (t_data_set *)ft_memalloc(sizeof(*data_set));
	close(fd);
	return (data_set);
}
