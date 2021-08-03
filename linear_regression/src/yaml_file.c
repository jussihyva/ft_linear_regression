/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaml_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:59:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/03 20:25:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	save_unknown_variables(double **theta_values)
{
	char			write_buf[WRITE_BUF_SIZE];
	char			*theta_file_yaml;
	int				fd;
	ssize_t			ret;
	size_t			i;

	theta_file_yaml = ft_strjoin(get_home_dir(), THETA_FILE_NAME);
	remove(theta_file_yaml);
	fd = open(theta_file_yaml, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	i = -1;
	while (++i < 2)
	{
		ft_bzero(write_buf, sizeof(char) * WRITE_BUF_SIZE);
		ft_sprintf(write_buf, "theta%d: %f\n", i, theta_values[i][0]);
		ret = write(fd, write_buf, ft_strlen(write_buf));
	}
	ret = close(fd);
	ft_strdel(&theta_file_yaml);
	return ;
}

t_matrix	*unknown_variables_read(void)
{
	t_matrix	*theta;
	int			fd;
	char		*theta_file_yaml;
	char		*line;
	int			ret;

	theta = NULL;
	theta_file_yaml = ft_strjoin(get_home_dir(), THETA_FILE_NAME);
	fd = open(theta_file_yaml, O_RDONLY);
	if (fd > 0)
	{
		ret = ft_get_next_line(fd, &line);
		FT_LOG_INFO("Theta0: %s", line);
		ft_strdel(&line);
		ret = ft_get_next_line(fd, &line);
		FT_LOG_INFO("Theta1: %s", line);
		ft_strdel(&line);
		theta = ft_vector_create(sizeof(double), 2);
	}
	return (theta);
}
