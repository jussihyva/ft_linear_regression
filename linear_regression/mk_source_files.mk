# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/07/22 10:54:19 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	read_dataset_file.c cmd_arguments.c linear_regression.c \
					gradient_rescent.c variables.c \
					ft_matrix_subtrack_vector_double.c ft_create_vector.c \
					ft_matrix_sum.c ft_matrix_dot_vector_double.c
SRC_H_FILES		=	ft_linear_regression.h
LOCAL_LIBS		=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS		=	libm.a
ifneq ($(OS), Darwin)
	GLOBAL_LIBS	+=	
endif
