/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:31:22 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/23 19:05:05 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// FIRST_CHILD
void	first_child(int *fd, char **av, char **env)
{
	char	**commands;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		open_faild(fd, av[1]);
	close(fd[0]);
	if (dup2(infile, STDIN_FILENO) == -1)
		failed_dup2(fd, 1, infile);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		failed_dup2(fd, 1, infile);
	close(infile);
	close(fd[1]);
	commands = ft_split(av[2], ' ');
	if (!commands)
		ft_write(NULL, NULL, "Memory allocation failed", 1);
	check_arg(av[2], commands, env);
	path = take_path(commands, commands[0], env);
	if (!path)
		ft_write(commands, NULL, ": Command not found", 1);
	if (execve(path, commands, env) == -1)
		ft_write(commands, path, ": No such file or directory", 1);
}

// SECOND_CHILD
void	second_child(int *fd, char **av, char **env)
{
	char	**commands;
	char	*path;
	int		outfile;

	outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile == -1)
		open_faild(fd, NULL);
	close(fd[1]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		failed_dup2(fd, 0, outfile);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		failed_dup2(fd, 0, outfile);
	close(outfile);
	close(fd[0]);
	commands = ft_split(av[3], ' ');
	if (!commands)
		ft_write(NULL, NULL, "Memory allocation failed", 1);
	check_arg(av[3], commands, env);
	path = take_path(commands, commands[0], env);
	if (!path)
		ft_write(commands, NULL, ": Command not found", 1);
	if (execve(path, commands, env) == -1)
		ft_write(commands, path, ": No such file or directory", 1);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	id;
	int	id2;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			failed_pipe();
		id = fork();
		if (id == -1)
			failed_fork(fd);
		if (id == 0)
			first_child(fd, av, env);
		id2 = fork();
		if (id2 == -1)
			failed_fork(fd);
		if (id2 == 0)
			second_child(fd, av, env);
		close(fd[0]);
		close(fd[1]);
		waitpid(id, NULL, 0);
		waitpid(id2, NULL, 0);
	}
	else
		input_error("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
}
