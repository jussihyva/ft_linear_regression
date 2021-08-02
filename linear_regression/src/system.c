/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:06:44 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/02 12:15:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linear_regression.h"

// #include <unistd.h>
// #include <sys/types.h>
#include <pwd.h>


const char	*get_home_dir(void)
{
	struct passwd 	*pw;
	const char		*homedir;

	pw = getpwuid(getuid());
	homedir = pw->pw_dir;
	return (homedir);
}
