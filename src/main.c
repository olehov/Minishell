/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/04 16:39:05 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// global variable for parce status (like $?)
int	g_last_exit_code;

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL || *str == NULL)
	{
		return ;
	}
	while (str[i] != NULL)
	{
		free(str[i++]);
	}
	free(str);
}

// initialization shell: enviroment variables
void	init_shell(t_minish *msh, char **envp)
{
	msh->env = NULL;
	g_last_exit_code = 0;
	if (init_env(&msh->env, envp) == -1)
	{
		ft_putstr_fd("Failed to initialize environment\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_last_exit_code = 130;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*get_prompt(t_minish *msh)
{
	char	*prompt;
	char	*tmp;
	char	*user;
	char	*user_value;

	user_value = get_env_value("USER", msh->env);
	if (ft_strcmp(user_value, "\0"))
		user = ft_strjoin3(CYAN, user_value, "'s" RESET "-" GRN "minishell");
	else
		user = ft_strjoin(GRN, "minishell");
	if (user == NULL)
		return (NULL);
	if (g_last_exit_code == 0)
		prompt = ft_strjoin(user, RESET "> ");
	else
	{
		tmp = ft_strjoin(user, " " RED "[");
		if (tmp == NULL)
			return (NULL);
		prompt = ft_strjoin3(tmp, ft_itoa(g_last_exit_code),
				"]" RESET "> ");
		free(tmp);
	}
	free(user);
	return (prompt);
}

t_cmd	*get_cmd_lst(t_minish *msh)
{
	char	*line;
	char	*prompt;
	t_cmd	*cmd_list;

	prompt = get_prompt(msh);
	// line = readline(prompt);
	line = readline("minishell> ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	cmd_list = parse_input(line, msh->env, msh);
	free(line);
	free(prompt);
	return (cmd_list);
}

void	print_arr_of_str(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL || *str == NULL)
	{
		return ;
	}
	while (str[i] != NULL)
	{
		printf("str[%lu]: %s\n", i, str[i]);
		i++;
	}
}

void	print_error(char *cmd)
{
	if (g_last_exit_code == 0)
		return ;
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (g_last_exit_code == 127)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		perror(cmd);
}

// Основний цикл shell
int	main(int argc, char **argv, char **envp)
{
	t_minish	msh;
	t_cmd		*cmd_list;
	int			std_fd[2];

	(void)argc;
	(void)argv;
	init_shell(&msh, envp);
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	while (1)
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		cmd_list = get_cmd_lst(&msh);
		if (cmd_list == NULL)
			break ;
		// print_arr_of_str(cmd_list->args);
		msh.cmd = cmd_list;
		execute_commands(&msh);
		print_error(cmd_list->args[0]);
		free_cmd_list(cmd_list);
		if (unlink(HEREDOC_FILENAME_PATH) == -1 && errno != ENOENT)
			perror(HEREDOC_FILENAME_PATH);
	}
	rl_clear_history();
	ft_lstclear(&msh.env, free_env);
	exit(g_last_exit_code);
}
