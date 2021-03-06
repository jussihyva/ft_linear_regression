# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2021/08/12 11:57:57 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_FOLDERS			=	Docker linear_regression
CUR_DIR					=	$(abspath .)
DOCKER_NAME				=	$(shell which docker)
DOCKER-COMPOSE_NAME		=	$(shell which docker-compose)

define DOCKER_NOT_INSTALLED_ERROR

	Docker is not installed:

		1. For Hive MAC's:	Download alexandregv/42toolbox (github) and run init_docker.sh
		2. For std linux env:	sudo apt-get install docker"

		
endef

define OPENSSL_ERROR

	OPENSSL is not installed:

		1. For Hive MAC's:	brew install openssl

		
endef

.PHONY: all
all:
	@echo "1. Installation"	
	@echo "  make build"
	@echo ""
	@echo "2. Run N-Puzzle solver"
	@echo "  make run"
	@echo ""
	@echo "3. Help"	
	@echo "  $(CUR_DIR)/linear_regression/ft_linear_regression -h"
	@echo ""

.PHONY: help
help: all
	@echo "DONE"

.PHONY: build
build: check_openssl check_docker folders check_jupyter
	@echo "DONE"

.PHONY: run
run:
	make -C linear_regression run

.PHONY: folders
folders:
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder ; \
	done

.PHONY: clean
clean:
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder clean ; \
	done

.PHONY: fclean
fclean:
	for folder in $(PROJECT_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done

.PHONY: re
re: all
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder norm ; \
	done

.PHONY: check_docker
check_docker:
ifeq (, $(DOCKER_NAME))
	$(error $(DOCKER_NOT_INSTALLED_ERROR))
else ifeq (, $(DOCKER-COMPOSE_NAME))
	$(error $(DOCKER_NOT_INSTALLED_ERROR))
endif

.PHONY: check_openssl
check_openssl:

.PHONY: check_jupyter
check_jupyter:
ifeq (, $(shell which jupyter | egrep jupyter))
	pip3 install notebook
endif
ifeq (, $(shell pip3 list | egrep "^numpy "))
	pip3 install numpy
endif
ifeq (, $(shell pip3 list | egrep "^matplotlib "))
	pip3 install matplotlib
endif
	jupyter notebook
