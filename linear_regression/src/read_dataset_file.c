/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:52:29 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/13 13:48:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static void	read_error(char *error_string, int line_counter)
{
	perror(error_string);
	FT_LOG_ERROR(error_string, line_counter);
	return ;
}

static t_data_record	*read_data_line(char *line)
{
	static int		line_counter = 1;
	char			*endptr;
	t_data_record	*data_record;

	line_counter++;
	ft_printf("LINE %d: %s\n", line_counter, line);
	data_record = (t_data_record *)ft_memalloc(sizeof(*data_record));
	data_record->km = ft_strtoi(line, &endptr, 10);
	if (errno == EINVAL && *endptr == ',')
	{
		line = endptr + 1;
		data_record->price = ft_strtoi(line, &endptr, 10);
		if (!((errno == EINVAL && *endptr == ' ')
				|| (!errno && *endptr == '\0')))
		{
			read_error("The second param in the line (%d) is faulty",
				line_counter);
		}
	}
	else
		read_error("The first param in the line (%d) is faulty", line_counter);
	return (data_record);
}

t_lin_reg_data	*read_dataset_file(char *dataset_file)
{
	t_lin_reg_data		*linear_regression_data;
	t_file_params		file_params;
	t_data_record		*data_record;

	file_params.fd = ft_open_fd(dataset_file);
	linear_regression_data = (t_lin_reg_data *)ft_memalloc(
			sizeof(*linear_regression_data));
	linear_regression_data->data_record_lst = (t_list **)ft_memalloc(
			sizeof(*linear_regression_data->data_record_lst));
	file_params.line = NULL;
	file_params.ret = ft_get_next_line(file_params.fd, &file_params.line);
	ft_strdel((char **)&file_params.line);
	file_params.ret = ft_get_next_line(file_params.fd, &file_params.line);
	while (file_params.ret)
	{
		data_record = read_data_line(file_params.line);
		linear_regression_add_data_record(linear_regression_data, data_record);
		ft_strdel((char **)&file_params.line);
		file_params.ret = ft_get_next_line(file_params.fd, &file_params.line);
	}
	ft_strdel((char **)&file_params.line);
	close(file_params.fd);
	return (linear_regression_data);
}
