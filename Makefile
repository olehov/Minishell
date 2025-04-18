# -------------------------
#       VARIABLES
# -------------------------
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = ./ft_libft
LIBFT = $(LIBFT_DIR)/libft_ft.a

SRC_DIR = src
OBJ_DIR = build

ENV_DIR = env
BUILTIN_DIR = builtin
CMD_DIR = cmd
PARSER_DIR = parser
UTILS_DIR = utils
SIGNALS_DIR = signals
HEREDOC_DIR = $(BUILTIN_DIR)/ft_heredoc

# -------------------------
#     SOURCE FILES
# -------------------------

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/execute_commands.c \
	$(SRC_DIR)/execute_builtin.c \
	$(SRC_DIR)/launch_child.c \
	$(SRC_DIR)/ft_shell.c \
	$(SRC_DIR)/$(UTILS_DIR)/utils.c \
	$(SRC_DIR)/$(UTILS_DIR)/pipe_utils.c \
	$(SRC_DIR)/$(UTILS_DIR)/ft_decode_wstatus.c \
	$(SRC_DIR)/$(UTILS_DIR)/get_prompt.c \
	$(SRC_DIR)/$(UTILS_DIR)/ft_syntax_error.c \
	$(SRC_DIR)/$(UTILS_DIR)/print_syntax_err.c \
	$(SRC_DIR)/$(PARSER_DIR)/parse_input.c \
	$(SRC_DIR)/$(PARSER_DIR)/parse_input_delimi.c \
	$(SRC_DIR)/$(PARSER_DIR)/parse_input_tok.c \
	$(SRC_DIR)/$(PARSER_DIR)/split_outside_quotes.c \
	$(SRC_DIR)/$(PARSER_DIR)/parser_utils.c \
	$(SRC_DIR)/$(PARSER_DIR)/tokenize_utils.c \
	$(SRC_DIR)/$(PARSER_DIR)/tokenize_with_quote_info.c \
	$(SRC_DIR)/$(PARSER_DIR)/handle_single_redirect.c \
	$(SRC_DIR)/$(PARSER_DIR)/handle_word.c \
	$(SRC_DIR)/$(PARSER_DIR)/parce_heredoc.c \
	$(SRC_DIR)/$(PARSER_DIR)/free_tokens.c \
	$(SRC_DIR)/$(PARSER_DIR)/append_part.c \
	$(SRC_DIR)/$(ENV_DIR)/print_env_list.c \
	$(SRC_DIR)/$(ENV_DIR)/ft_env_unset.c \
	$(SRC_DIR)/$(ENV_DIR)/ft_set_env.c \
	$(SRC_DIR)/$(ENV_DIR)/init_env.c \
	$(SRC_DIR)/$(ENV_DIR)/ft_get_env.c \
	$(SRC_DIR)/$(ENV_DIR)/get_env_value.c \
	$(SRC_DIR)/$(ENV_DIR)/process_env.c \
	$(SRC_DIR)/$(ENV_DIR)/extract_variable_utils.c \
	$(SRC_DIR)/$(ENV_DIR)/handle_escaping_variable.c \
	$(SRC_DIR)/$(ENV_DIR)/append_variable_value.c \
	$(SRC_DIR)/$(ENV_DIR)/try_ensure_buffer_capacity.c \
	$(SRC_DIR)/$(ENV_DIR)/proccess_quoted_text.c \
	$(SRC_DIR)/$(ENV_DIR)/env_list_to_arr.c \
	$(SRC_DIR)/$(ENV_DIR)/split_path.c \
	$(SRC_DIR)/$(ENV_DIR)/free_env.c \
	$(SRC_DIR)/$(ENV_DIR)/extract_variable_value.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/printpwd.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/builtin_echo.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/ft_cd.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/free_redirect.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/init_redirect.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/ft_is_directory.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/is_builtin.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/handle_redirect.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/ft_exit_utils.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/ft_exit.c \
	$(SRC_DIR)/$(HEREDOC_DIR)/ft_heredoc.c \
	$(SRC_DIR)/$(HEREDOC_DIR)/init_heredoc.c \
	$(SRC_DIR)/$(HEREDOC_DIR)/unlink_heredocs.c \
	$(SRC_DIR)/$(HEREDOC_DIR)/free_heredoc.c \
	$(SRC_DIR)/$(HEREDOC_DIR)/check_delimiter.c \
	$(SRC_DIR)/$(HEREDOC_DIR)/get_delimiter.c \
	$(SRC_DIR)/$(CMD_DIR)/init_cmd_node.c \
	$(SRC_DIR)/$(CMD_DIR)/add_redirection.c \
	$(SRC_DIR)/$(CMD_DIR)/free_cmd_list.c \
	$(SRC_DIR)/$(CMD_DIR)/get_cmd_lst.c \
	$(SRC_DIR)/$(SIGNALS_DIR)/ft_signals.c \
	$(SRC_DIR)/$(SIGNALS_DIR)/set_signals.c

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# -------------------------
#      RULES
# -------------------------
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

v: all
	valgrind --suppressions=rl.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
