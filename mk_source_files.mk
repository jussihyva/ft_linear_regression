# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/07/09 12:48:55 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	read_dataset_file.c
SRC_H_FILES		=	ft_linear_regression.h
LOCAL_LIBS		=	
GLOBAL_LIBS		=	
ifneq ($(OS), Darwin)
	GLOBAL_LIBS	+=	
endif
