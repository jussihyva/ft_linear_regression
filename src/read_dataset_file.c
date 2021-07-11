/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:52:29 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/11 18:35:37 by jkauppi          ###   ########.fr       */
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
	static int		line_counter = 0;
	char			*endptr;
	t_data_record	*data_record;

	line_counter++;
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

static void	save_data_record_to_lst(t_list **data_record_lst,
													t_data_record *data_record)
{
	t_list			*elem;

	elem = ft_lstnew(&data_record, sizeof(data_record));
	ft_lstadd(data_record_lst, elem);
	return ;
}

t_list	**read_dataset_file(char *dataset_file)
{
	int				fd;
	t_data_record	*data_record;
	char			*line;
	int				ret;
	t_list			**data_record_lst;

	fd = ft_open_fd(dataset_file);
	data_record_lst = (t_list **)ft_memalloc(sizeof(*data_record_lst));
	line = NULL;
	ret = ft_get_next_line(fd, &line);
	ft_strdel((char **)&line);
	ret = ft_get_next_line(fd, &line);
	while (ret)
	{
		data_record = read_data_line(line);
		save_data_record_to_lst(data_record_lst, data_record);
		ft_printf("LINE: %s\n", line);
		ft_strdel((char **)&line);
		ret = ft_get_next_line(fd, &line);
	}
	ft_strdel((char **)&line);
	close(fd);
	return (data_record_lst);
}
