/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpput_read_mileage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:24:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 18:25:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

int	read_mileage_of_a_car(t_input_params *input_params)
{
	char	*endptr;
	char	*line;
	int		km;

	input_params->order = E_CALCULATE_PRICE;
	line = NULL;
	ft_printf("Type mileage (int) of the car: ");
	ft_get_next_line(0, &line);
	errno = 0;
	km = ft_strtoi(line, &endptr, 10);
	if (*endptr != '\0' || errno != 0)
	{
		ft_printf("km param (%s) is not valid\n", line);
		exit(42);
	}
	ft_strdel(&line);
	return (km);
}
