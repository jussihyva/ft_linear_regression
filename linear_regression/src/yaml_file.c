/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaml_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:59:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/12 14:11:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

char	*file_path_create(char *file_name)
{
	char			*file_path;
	size_t			str_len;

	str_len = ft_strlen(get_home_dir()) + 1 + ft_strlen(file_name);
	file_path = ft_memalloc(sizeof(*file_path) * (str_len + 1));
	ft_strcat(file_path, get_home_dir());
	ft_strcat(file_path, "/");
	ft_strcat(file_path, file_name);
	return (file_path);
}

void	save_unknown_variables(double **theta_values)
{
	char			write_buf[WRITE_BUF_SIZE];
	char			*theta_file_yaml;
	int				fd;
	ssize_t			ret;
	size_t			i;

	theta_file_yaml = file_path_create(THETA_FILE_NAME);
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

static double	parse_theta_value(char *line)
{
	char		**param_value;
	char		*endptr;
	double		theta_value;

	theta_value = 0;
	param_value = ft_strsplit(line, ':');
	if (param_value[0] && param_value[1])
	{
		errno = 0;
		theta_value = strtod(param_value[1], &endptr);
		if (errno != 0 || *endptr != '\0')
			FT_LOG_ERROR("Content of the theta input file (%s) is not valid!",
				THETA_FILE_NAME);
	}
	else
		FT_LOG_ERROR("Content of the theta input file (%s) is not valid!",
			THETA_FILE_NAME);
	ft_strarraydel(&param_value);
	return (theta_value);
}

static t_matrix	*read_theta_values(int fd)
{
	t_matrix	*theta;
	char		*line;
	size_t		i;

	theta = ft_vector_create(sizeof(double), 2);
	line = NULL;
	i = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (i > 1)
			FT_LOG_ERROR("Theta file includes unexpected number of lines!");
		((double **)theta->values)[i][0] = parse_theta_value(line);
		FT_LOG_DEBUG("%s", line);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	return (theta);
}

t_matrix	*unknown_variables_read(void)
{
	t_matrix	*theta;
	int			fd;
	char		*theta_file_yaml;

	theta = NULL;
	theta_file_yaml = file_path_create(THETA_FILE_NAME);
	fd = open(theta_file_yaml, O_RDONLY);
	if (fd > 0)
		theta = read_theta_values(fd);
	else
		FT_LOG_ERROR("Theta file (%s) is not created!", theta_file_yaml);
	ft_strdel(&theta_file_yaml);
	return (theta);
}
