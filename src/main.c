/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/09 20:59:10 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// global variable for parce status (like $?)
int	g_last_exit_code;

// initialization shell: enviroment variables
void	init_shell(t_minish *msh, char **envp)
{
	msh->env = NULL;
	msh->heredocs = NULL;
	g_last_exit_code = 0;
	if (init_env(&msh->env, envp) == -1)
	{
		g_last_exit_code = EXIT_FAILURE;
		ft_putstr_fd("Failed to initialize environment\n", STDERR_FILENO);
		exit(g_last_exit_code);
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
	char	*err_code;

	user_value = get_env_value("USER", msh->env);
	if (ft_strcmp(user_value, "\0") != 0)
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
		err_code = ft_itoa(g_last_exit_code);
		prompt = ft_strjoin3(tmp, err_code, "]" RESET "> ");
		free(tmp);
		free(err_code);
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
	// line = readline("MINISHELL>");
	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
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

// Основний цикл shell
int	main(int argc, char **argv, char **envp)
{
	t_minish	msh;
	t_cmd		*cmd_list;

	(void)argc;
	(void)argv;
	init_shell(&msh, envp);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		cmd_list = get_cmd_lst(&msh);
		if (cmd_list == NULL)
			break ;
		msh.cmd = cmd_list;
		execute_commands(&msh);
		free_cmd_list(cmd_list);
		unlink_heredocs(&msh.heredocs);
	}
	rl_clear_history();
	ft_lstclear(&msh.env, free_env);
	exit(g_last_exit_code);
}
