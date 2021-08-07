/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 10:46:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/07 10:50:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

void	error_remove(t_reg_error **reg_error)
{
	if (reg_error && *reg_error)
	{
		ft_vector_remove(&(*reg_error)->error);
		ft_vector_remove(&(*reg_error)->error_squares);
		ft_memdel((void **)reg_error);
	}
	return ;
}
