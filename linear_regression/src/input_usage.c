/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:38:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 18:39:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

static void	print_examples(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./ft_linear_regression\n");
	ft_printf("    Type mileage (int) of the car: 10000\n");
	ft_printf("    Estimated price: $8280\n");
	ft_printf("\n   2:\n");
	ft_printf("    ./ft_linear_regression 220000\n");
	ft_printf("    Estimated price: $3788\n");
	ft_printf("\n   3:\n");
	ft_printf("    ./ft_linear_regression -f data/data.csv\n");
	ft_printf("    THETA0:    8493.5558\n");
	ft_printf("    THETA1:      -0.0214\n");
	ft_printf("    Precision of theta values (R2): 0.732969\n");
	return ;
}

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./ft_linear_regression\n");
	print_examples();
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  None\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h                            Help printout\n");
	ft_printf("  -f    <data set file>         %s\n",
		"Calculates unknown variables (Theta values)");
	ft_printf("  -F                            %s\n",
		"Allow calculation of negative inpput values and results");
	ft_printf("  -A    <learning rate>         %s\n",
		"Learning rate (alpha) for gradient descent. Default value is 0.1");
	ft_printf("  -C    <cost limit>            %s%s\n",
		"Cost limit is a maximum allowed cost change per iteration loop (R2) ",
		"for gradient descent calculation. Default value is 0.0000001");
	ft_printf("  -L    <logging level>         %s\n",
		"Logging details for trouble shoooting. Valid values 0-4");
	ft_printf("  -l                            %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}
