/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_addons_against_norm.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:52:44 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/11 14:38:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ADDONS_AGAINST_NORM_H
# define LIBFT_ADDONS_AGAINST_NORM_H

void	ft_loging_event(int level, const char *file, int line,
			const char *fmt, ...);

# define FT_LOG_FATAL(...)	ft_log_fatal(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_ERROR(...)	ft_log_error(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_WARN(...)	ft_log_warn(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_INFO(...)	ft_log_info(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_DEBUG(...)	ft_log_debug(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_TRACE(...)	ft_log_trace(__FILE__, __LINE__, __VA_ARGS__)

#endif
