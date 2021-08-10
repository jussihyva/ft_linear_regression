/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:52:29 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/10 19:05:47 by jkauppi          ###   ########.fr       */
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
	FT_LOG_INFO("LINE %d: %s", line_counter, line);
	data_record = (t_data_record *)ft_memalloc(sizeof(*data_record));
	errno = 0;
	data_record->km = ft_strtoi(line, &endptr, 10);
	if (errno == EINVAL && *endptr == ',')
	{
		line = endptr + 1;
		errno = 0;
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

t_lin_reg	*linear_regression_initialize(void)
{
	t_lin_reg	*linear_regression;

	linear_regression = (t_lin_reg *)ft_memalloc(sizeof(*linear_regression));
	return (linear_regression);
}

void	dataset_add_record(t_dataset *dataset, t_data_record *data_record)
{
	t_list						*elem;

	dataset->num_of_records++;
	elem = ft_lstnew(&data_record, sizeof(data_record));
	ft_lstadd(&dataset->data_record_lst, elem);
	return ;
}

t_dataset	*read_dataset_file(char *dataset_file)
{
	t_file_params	file_params;
	t_data_record	*data_record;
	t_dataset		*dataset;

	dataset = (t_dataset *)ft_memalloc(sizeof(*dataset));
	file_params.fd = ft_open_fd(dataset_file);
	file_params.line = NULL;
	ft_get_next_line(file_params.fd, &file_params.line);
	ft_strdel((char **)&file_params.line);
	while (ft_get_next_line(file_params.fd, &file_params.line) > 0)
	{
		data_record = read_data_line(file_params.line);
		dataset_add_record(dataset, data_record);
		ft_strdel((char **)&file_params.line);
	}
	ft_strdel((char **)&file_params.line);
	close(file_params.fd);
	return (dataset);
}
