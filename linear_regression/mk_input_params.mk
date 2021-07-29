# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_input_params.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:50:47 by jkauppi           #+#    #+#              #
#    Updated: 2021/07/29 19:54:59 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef F
	DATA_FILE			=	-f $(F)
else
	DATA_FILE			=	-f data/data.csv
endif

ifdef L
	LOGGING_LEVEL		=	-L $(L)
else
	LOGGING_LEVEL		=	-L 3
endif
