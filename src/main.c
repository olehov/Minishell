/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:07 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/14 15:53:39 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	signal_handler(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_received_signal = SIGINT;
// 	}
// 	else if (signo == SIGQUIT)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_received_signal = SIGQUIT;
// 	}
// }

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
	if (msh->exit_code == 0)
		prompt = ft_strjoin(user, RESET "> ");
	else
	{
		tmp = ft_strjoin(user, " " RED "[");
		if (tmp == NULL)
			return (free(user), NULL);
		err_code = ft_itoa(msh->exit_code);
		prompt = ft_strjoin3(tmp, err_code, "]" RESET "> ");
		free(tmp);
		if (err_code != NULL)
			free(err_code);
	}
	free(user);
	return (prompt);
}

// char	*get_line(t_minish *msh)
// {
// 	char	*line;
// 	char	*prompt;

// 	prompt = get_prompt(msh);
// 	if (isatty(STDIN_FILENO))
// 	{
// 		if (prompt == NULL)
// 			line = readline(GRN "minishell> " RESET);
// 		else
// 			line = readline(prompt);
// 	}
// 	else
// 		line = readline("minishell> ");
// 	if (line == NULL)
// 	{
// 		if (prompt != NULL)
// 			free(prompt);
// 		return (NULL);
// 	}
// 	if (prompt != NULL)
// 		free(prompt);
// 	return (line);
// }


int	minishell_loop()
{

}

int	main(int argc, char **argv, char **envp)
{
	t_minish	msh;
	int			exit_code;
	char		*line;

	(void)argc;
	(void)argv;
	init_shell(&msh, envp);
	set_signals();
	while (1)
	{
		line = get_line(&msh);
		if (!line)
		{
			msh.exit_code = 0;
			break ;
		}
		if (g_received_signal == SIGINT)
		{
			msh.exit_code = 128 + SIGINT;
			g_received_signal = 0;
		}
		if (*line)
			add_history(line);
		msh.cmd = parse_input(line, msh.env, &msh);
		free(line);
		if (msh.cmd == NULL)
			continue ;
		execute_commands(&msh);
		free_cmd_list(msh.cmd);
		unlink_heredocs(&msh.heredocs);
	}
	rl_clear_history();
	exit_code = msh.exit_code;
	free_shell(&msh);
	exit(exit_code);
}
