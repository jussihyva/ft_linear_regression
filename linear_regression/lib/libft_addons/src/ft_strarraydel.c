/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:47:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/12 13:47:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_strarraydel(char ***array)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while ((*array)[i])
	{
		ptr = (*array)[i];
		ft_strdel(&ptr);
		i++;
	}
	ft_memdel((void **)array);
	return ;
}
