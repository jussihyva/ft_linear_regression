# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/08/07 10:46:18 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	read_dataset_file.c cmd_arguments.c linear_regression.c \
					gradient_rescent_1.c gradient_rescent_2.c variable.c \
					variable_remove.c ft_matrix_subtract_vector_double.c \
					ft_vector_create.c ft_matrix_sum.c ft_matrix_print.c \
					ft_matrix_dot_vector_double.c ft_matrix_transpose.c \
					ft_matrix_multiply_vector_double.c \
					variable_normalize.c influxdb.c \
					statistics_1.c statistics_2.c statistics_3.c \
					statistics_4.c statistics_remove.c statistics_record.c \
					yaml_file.c system.c coefficient_of_determination.c \
					residual.c error.c
SRC_H_FILES		=	ft_linear_regression.h
LOCAL_LIBS		=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS		=	libm.a libssl.a libcrypto.a libm.a
ifneq ($(OS), Darwin)
	GLOBAL_LIBS	+=	
endif
