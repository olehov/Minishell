# -------------------------
#       VARIABLES
# -------------------------
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

LIBFT_DIR = ./ft_libft
LIBFT = $(LIBFT_DIR)/libft_ft.a

SRC_DIR = src
OBJ_DIR = build

# -------------------------
#     SOURCE FILES
# -------------------------

SRC = main.c \
      parse_input.c \
      execute_commands.c \
      builtin_echo.c \
      builtin_utils.c \
      ft_heredoc.c \
      utils.c \
      \
      ft_cd.c \
      printpwd.c \
      print_env_list.c \
      ft_env_unset.c \
      ft_set_env.c \
      init_env.c \
      ft_get_env.c \
      get_env_value.c \
      process_env.c \
      extract_variable_utils.c \
      handle_escaping_variable.c \
      append_variable_value.c \
      try_ensure_buffer_capacity.c \
      append_to_file.c \
      print_file_error.c \
      proccess_quoted_text.c \
      env_list_to_arr.c \
      split_path.c \
      expand_line.c

SRC_WITH_PATH = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# -------------------------
#      RULES
# -------------------------

all: $(NAME)

# Правило для створення каталогу build/ якщо нема
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Головна ціль: збірка minishell
$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

# Компиляція .c в .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Збірка libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Очищення об'єктів
clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

# Повна очистка
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Перезбірка
re: fclean all

.PHONY: all clean fclean re
