/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:31:22 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/13 19:02:56 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	failed_dup2(int *fd, int pipe, int file)
{
	close(fd[pipe]);
	close(file);
	perror("error failed dup2");
	exit(1);
}

void	ft_free(char **get_free)
{
	int	i;

	if (!get_free)
		return;
	i = 0;
	while (get_free[i])
	{
		free(get_free[i]);
		i++;
	}
	free(get_free);
	return ;
}

void	exec_path_failed(char **commands)
{
	perror(commands[0]);
	ft_free(commands);
	exit(1);
}

void	failed_fork(int *fd)
{
	perror("error");
	close(fd[1]);
	close(fd[0]);
	exit(1);
}

void	failed_pipe()
{
	perror("error");
	exit(1);
}

void	input_error(void)
{
	ft_putstr_fd("Bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
}

char	*get_path(char **paths, char *command)
{
	int		i;
	char	*path;
	char	*part_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, command);
		free(part_path);
		if (path && access(path, F_OK | X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

char	*take_path(char *command, char **env)
{
	int	i;
	char	**paths;
	char	*path;

	i = -1;
	while (env[++i] && ft_strnstr(env[i], "PATH", 4) == 0);
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = get_path(paths, command);
	if (!path)
		return (NULL);
	ft_free(paths);
	return (path);
}

void	first_child(int *fd, char **av, char **env)
{
	char	**commands;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		close(fd[1]);
		close(fd[0]);
		perror("failed to open fd");
		exit(1);
	}
	close(fd[0]);
	if (dup2(infile, STDIN_FILENO) == -1)
		failed_dup2(fd, 1, infile);
	if (dup2(fd[1],STDOUT_FILENO) == -1)
		failed_dup2(fd, 1, infile);
	close(fd[1]);

	commands = ft_split(av[2], ' ');
	if (!commands)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}

	if (ft_strncmp(av[2], "./", 2) == 0 || ft_strncmp(av[2], "../", 3) == 0
		|| ft_strncmp(av[2], "/", 1) == 0)
		if (execve(commands[0], commands, env) == -1)
			exec_path_failed(commands);

	path = take_path(commands[0], env);
	if (!path)
	{
		write(2,"Command not found :",19);
		write(2,commands[0],ft_strlen(commands[0]));
		write(2,"\n",1);
		exit(1);
	}

	if (execve(path, commands, env) == -1)
	{
		ft_printf("execve failed for :%s\n", commands[0]);
		ft_free(commands);
		exit(1);
	}

	ft_free(commands);
}

void	second_child(int *fd, char **av, char **env)
{
	char	**commands;
	char	*path;
	int		outfile;

	outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile == -1)
	{
		close(fd[1]);
		close(fd[0]);
		perror("failed to open fd");
		exit(1);
	}

	close(fd[1]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		failed_dup2(fd, 0, outfile);
	if (dup2(fd[0],STDIN_FILENO) == -1)
		failed_dup2(fd, 0, outfile);
	close(fd[0]);

	commands = ft_split(av[3], ' ');
	if (!commands)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}

	if (ft_strncmp(av[3], "./", 2) == 0 || ft_strncmp(av[3], "../", 3) == 0
		|| ft_strncmp(av[3], "/", 1) == 0)
		if (execve(commands[0], commands, env) == -1)
			exec_path_failed(commands);

	path = take_path(commands[0], env);
	if (!path)
	{
		write(2,"Command not found :",19);
		write(2,commands[0],ft_strlen(commands[0]));
		write(2,"\n",1);
		exit(1);
	}

	if (execve(path,commands,env) == -1)
	{
		ft_printf("execve failed for :%s\n", commands[0]);
		ft_free(commands);
		exit(1);
	}

	ft_free(commands);
}

int main(int ac, char **av, char **env)
{
	int 	fd[2];
	int		id;
	int		id2;

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
		waitpid(id,NULL,0);
		waitpid(id2,NULL,0);
	}
	else
		input_error();
}
