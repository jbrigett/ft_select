# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 16:15:03 by jbrigett          #+#    #+#              #
#    Updated: 2020/08/17 16:15:04 by jbrigett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
CC = gcc
FLAGS = -Wall -Werror -Wextra
TERMFLAG = -ltermcap
LIBFT = libft.a

CUR_DIR = $(shell pwd)
O_DIR = $(CUR_DIR)/objs
C_DIR = $(CUR_DIR)/src
LIBFT_DIR = $(CUR_DIR)/libft

HEADERS = $(LIBFT_DIR)/includes $(CUR_DIR)/includes

FILES = sl_errors \
        sl_args \
        sl_struct \
        sl_key_pressed \
		ft_select

O_FILES = $(patsubst %, $(O_DIR)/%.o, $(FILES))
C_FILES = $(patsubst %, $(C_DIR)/%.c, $(FILES))

all: $(NAME)

o_dir:
	@if ! [ -d $(O_DIR) ]; then mkdir $(O_DIR); fi;

$(NAME): $(LIBFT) $(O_FILES)
	@$(CC) $(FLAGS) $(patsubst %, -I %, $(HEADERS)) $(patsubst lib%.a, -l%, $(LIBFT)) \
	-L$(LIBFT_DIR) $(O_FILES) -o $(NAME) $(TERMFLAG)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) $(LIBFT)

$(O_DIR)/%.o: $(C_DIR)/%.c
	@make o_dir
	@$(CC) $(CCFLAGS) -c $< -o $@ $(patsubst %, -I%, $(HEADERS));

clean:
	@rm -rf $(O_DIR)
	@make -C $(LIBFT_DIR) $@

fclean: clean
	@rm -rf $(CUR_DIR)/$(NAME)
	@make -C $(LIBFT_DIR) $@

re: fclean all
