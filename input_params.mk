# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    input_params.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:50:47 by jkauppi           #+#    #+#              #
#    Updated: 2021/07/09 10:51:56 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef F
	DATA_FILE			=	-F $(F)
else
	DATA_FILE			=	
endif
