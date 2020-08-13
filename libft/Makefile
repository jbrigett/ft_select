# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrigett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 14:47:30 by jbrigett          #+#    #+#              #
#    Updated: 2019/09/19 14:25:35 by jbrigett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror $(INC) -c -o

INC = -I includes/

SRCS_DIR = srcs/

OBJ_DIR = obj/

SRCS = ft_strnstr.c ft_putnbr_fd.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_isspace.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_printf.c help.c help_float.c itoa_base.c not_found.c parser.c parser_spec.c print_ae.c print_aefg.c print_all.c print_bxou.c print_c.c print_di.c print_f.c print_g.c print_n.c print_p.c print_percent.c print_s.c print_ws.c ws_help.c help_spec_val.c

CFIND = $(SRCS:%=$(SRCS_DIR)%)

OFILE = $(SRCS:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OFILE))

all: $(NAME)

$(NAME): $(OBJ_DIR)  $(OBJ)
	@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OFILE))
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ): $(CFIND)
	@$(MAKE) $(OFILE)

$(OFILE):
	@$(CC) $(FLAGS) $(OBJ_DIR)$@ $(SRCS_DIR)$(@:%.o=%.c)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all