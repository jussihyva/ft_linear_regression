/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:07:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 18:09:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

#if DARWIN
void	ft_print_leaks(void)
{
	system("leaks ft_linear_regression");
	return ;
}
#else

void	ft_print_leaks(void)
{
	return ;
}
#endif
