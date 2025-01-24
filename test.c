/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:54:56 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/24 17:45:51 by hwahmane         ###   ########.fr       */
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
	if (execve(path, commands, env) == -1)
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
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT) == -1)
		{
			perror("error failed dup2");
			exit(1);
		}
		close(pipefd[1]);
		exec(cmd, env);
		exit(1);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN) == -1)
	{
		perror("error failed dup2");
		exit(1);
	}
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}

void	redir2(char **cmd, char **env, int *fd)
{
	int	infile;

	infile = openfile(cmd[1], INFILE);
	if (infile == -1)
		exit(1);
	close(fd[0]);
	dup2(infile, STDIN);
	dup2(fd[1], STDOUT);
	close(infile);
	close(fd[1]);
	exec(cmd[2], env);
	exit(1);
}

void	redir3(char **cmd, char **env, int open)
{
	int	outfile;

	outfile = openfile(cmd[open + 1], OUTFILE);
	if (outfile == -1)
		exit(1);
	if (dup2(outfile, STDOUT) == -1)
	{
		perror("error failed dup2");
		exit(1);
	}
	close(outfile);
	exec(cmd[open], env);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];

	i = 3;
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			here_doc(ac, av, env);
		if (pipe(fd) == -1)
			failed_pipe();
		pid = fork();
		if (pid == 0)
			redir2(av, env, fd);
		close(fd[1]);
		close(fd[0]);
		while (i < ac - 2)
			redir(av[i++], env);
		pid2 = fork();
		if (pid2 == 0)
			redir3(av, env, i);
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		input_error("Ex: ./pipex <file1> <cmd1> <cmd2> ... <cmdn> <file2>\n");
	return (1);
}
