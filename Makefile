NAME = ft_select
CC = gcc
FLAGS = -Wall -Werror -Wextra -O
LIBFT = libft.a

CUR_DIR = $(shell pwd)
O_DIR = $(CUR_DIR)/objs
C_DIR = $(CUR_DIR)/srcs
LIBFT_DIR = $(CUR_DIR)/libft

HEADERS = $(LIBFT_DIR)/includes $(CUR_DIR)/includes

FILES = err_dir \
		format \
		ft_dlst_count \
		get_rights \
		help \
		help_dir \
		main \
		parser \
		parser_1 \
		parser_bigc \
		parser_d \
		parser_l \
		parser_r \
		parser_time \
		sort

O_FILES = $(patsubst %, $(O_DIR)/%.o, $(FILES))
C_FILES = $(patsubst %, $(C_DIR)/%.c, $(FILES))

all: $(NAME)

o_dir:
	@if ! [ -d $(O_DIR) ]; then mkdir $(O_DIR); fi;

$(NAME): $(LIBFT) $(O_FILES)
	@$(CC) $(FLAGS) $(patsubst %, -I %, $(HEADERS)) $(patsubst lib%.a, -l%, $(LIBFT)) \
	-L$(LIBFT_DIR) $(O_FILES) -o $(NAME)

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
