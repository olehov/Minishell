/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:47:37 by ogrativ           #+#    #+#             */
/*   Updated: 2025/03/23 13:07:47 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// // --- Обробка редіректів ---
// void handle_redirects(t_cmd *cmd)
// {
//     int fd;

//     if (cmd->infile && ft_strcmp(cmd->infile, "<<") != 0) // звичайний редірект
//     {
//         fd = open(cmd->infile, O_RDONLY);
//         if (fd < 0)
//         {
//             perror("Input file open failed");
//             exit(EXIT_FAILURE);
//         }
//         dup2(fd, STDIN_FILENO);
//         close(fd);
//     }
//     if (cmd->outfile)
//     {
//         if (cmd->append_out)
//             fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         else
//             fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fd < 0)
//         {
//             perror("Output file open failed");
//             exit(EXIT_FAILURE);
//         }
//         dup2(fd, STDOUT_FILENO);
//         close(fd);
//     }
// }

void printerrcode(t_minish *msh)
{
	if (msh != NULL)
	{
		perror(ft_itoa(msh->last_exit_code));
	}
}

// --- Вбудовані команди ---
void execute_builtin(t_cmd *cmd, t_minish *msh)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(cmd->args[1], &msh->env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		printpwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env_list(msh->env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_set_env(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_env_unset(&msh->env, cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "$?") == 0)
		printerrcode(msh);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "$?") == 0)
		return (1);
	return (0);
}

// --- Heredoc перед виконанням ---
void handle_heredoc(t_cmd *cmd, t_list *env)
{
	if (cmd->infile && ft_strcmp(cmd->infile, "<<") == 0)
	{
		ft_heredoc(cmd->delimiter, env);
		free(cmd->infile);
		cmd->infile = ft_strdup(HEREDOC_FILENAME_PATH);
	}
}

char *find_executable_path(char *cmd, t_list *env)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}

	char **paths = split_path(env, "PATH", ':');
	if (!paths)
		return NULL;

	char *full_path = NULL;
	for (int i = 0; paths[i]; i++)
	{
		char *tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);

		if (access(full_path, X_OK) == 0)
		{
			ft_free_2d_array(paths, -1);
			return full_path;
		}
		free(full_path);
	}

	ft_free_2d_array(paths, -1);
	return NULL;
}

// --- Основна функція виконання з пайпами ---
void execute_commands(t_cmd *cmd_list, t_minish *msh)
{
	t_cmd *cmd = cmd_list;
	int prev_fd = -1;
	int pipe_fd[2];
	pid_t pid;

	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		handle_heredoc(cmd, msh->env);
		if (is_builtin(cmd->args[0]) && !cmd->next && prev_fd == -1)
		{
			execute_builtin(cmd, msh);
			g_minish.last_exit_code = errno;
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1) dup2(prev_fd, 0);
			if (cmd->next) dup2(pipe_fd[1], 1);
			handle_redirects(cmd);

			if (is_builtin(cmd->args[0]))
			{
				execute_builtin(cmd, msh);
				rl_clear_history();
				exit(0);
			}
			char *path = find_executable_path(cmd->args[0], msh->env);
			if (!path)
			{
				perror("command not found");
				msh->last_exit_code = 127;
				exit(msh->last_exit_code);
			}
			char **envp = env_list_to_str_arr(msh->env);
			execve(path, cmd->args, envp); // виклик зовнішньої команди
			msh->last_exit_code = 127;
			rl_clear_history();
			perror("execve failed");
			exit(msh->last_exit_code);
		}
		else
		{
			waitpid(pid, &msh->last_exit_code, 0);
			if (WIFEXITED(msh->last_exit_code))
				g_minish.last_exit_code = WEXITSTATUS(msh->last_exit_code);
			else if (WIFSIGNALED(msh->last_exit_code))
				g_minish.last_exit_code = 128 + WTERMSIG(msh->last_exit_code);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		cmd = cmd->next;
	}
}
