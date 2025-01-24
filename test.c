/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:54:56 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/24 18:32:12 by hwahmane         ###   ########.fr       */
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
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
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

void	redir(char *cmd, char **env, int pid, int *pipefd)
{
	
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		close(pipefd[1]);
		exec(cmd, env);
	}
}

void	redir2(char *cmd, char **env, int pid)
{
	if (pid == 0)
		exec(cmd, env);
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;
	pid_t	pid;
	int		pipefd[2];
	pid_t	pid2;

	i = 3;
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			here_doc(ac, av, env);

		if (pipe(pipefd) == -1)
			failed_pipe();
		pid = fork();
		if (pid == -1)
			failed_fork(pipefd);

		fdin = openfile(av[1], INFILE);
		dup2(fdin, STDIN);
		close(fdin);
		redir(av[2], env, pid , pipefd);
		while (i < ac - 2)
		{
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
				waitpid(pid, NULL, 0);
			}
			redir(av[i++], env, pid, pipefd);
		}

		pid2 = fork();
		fdout = openfile(av[ac - 1], OUTFILE);
		dup2(fdout, STDOUT);
		close(fdout);
		redir2(av[i], env, pid2);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		input_error("Ex: ./pipex <file1> <cmd1> <cmd2> ... <cmdn> <file2>\n");
	return (1);
}
