/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_release.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:32:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/13 10:33:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_event_logging_release(t_event_logging_data **event_logging_data)
{
	int		i;

	i = -1;
	while (++i < 6)
		ft_memdel((void **)&(*event_logging_data)->level_colors[i]);
	ft_memdel((void **)&(*event_logging_data)->level_colors);
	i = -1;
	while (++i < 6)
		ft_memdel((void **)&(*event_logging_data)->level_strings[i]);
	ft_memdel((void **)&(*event_logging_data)->level_strings);
	ft_memdel((void **)event_logging_data);
	ft_release_loging_params();
	return ;
}
