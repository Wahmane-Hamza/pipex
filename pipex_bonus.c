/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:54:56 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/24 20:52:01 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(2, "cannot open ", 12);
			write(2, filename, ft_strlen(filename));
			write(2, ": No such file", 14);
			write(2, "\n", 1);
			exit(1);
		}
		return (open(filename, O_RDONLY));
	}
	else
	{
		if (access(filename, W_OK) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
		}
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	}
}

void	exec(char *cmd, char **env)
{
	char	**commands;
	char	*path;

	check(cmd, NULL);
	commands = ft_split(cmd, ' ');
	if (!commands)
		ft_write(NULL, NULL, "Memory allocation failed", 1);
	check_arg(cmd, commands, env);
	path = take_path(commands, commands[0], env);
	if (!path)
		ft_write(commands, NULL, ": not found", 1);
	execve(path, commands, env);
	ft_write(commands, path, ": not found", 1);
}

void	redir(char *cmd, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		failed_pipe();
	pid = fork();
	if (pid == -1)
		failed_fork(pipefd);
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		close(pipefd[1]);
		exec(cmd, env);
	}
}

void	redir2(char *cmd, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		failed_pipe();
	pid = fork();
	if (pid == -1)
		failed_fork(pipefd);
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		exec(cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;

	i = 3;
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			here_doc(ac, av, env);
		open_file(av, ac);
		redir(av[2], env);
		while (i < ac - 2)
			redir(av[i++], env);
		redir2(av[i], env);
		while (wait(NULL) != -1)
			continue ;
	}
	else
		input_error("Ex: ./pipex <file1> <cmd1> <cmd2> ... <cmdn> <file2>\n");
	return (1);
}
