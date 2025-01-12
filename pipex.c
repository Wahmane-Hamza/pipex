/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:31:22 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/12 18:57:44 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	paths = ft_split(env[i] + 5, ':');
	path = get_path(paths, command);
	return (path);
}

void	first_child(int id, int *fd, char *av, char **env)
{
	char	**commands;
	char	*path;

	commands = ft_split(av, ' ');
	path = take_path(commands[0], env);
	if (id == 0)
		{
			dup2(fd[1],STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (execve(path, commands, env) == -1)
			{
				perror("execve failed");
				exit(1);
			}
		}
}

void	second_child(int id, int *fd, char *av, char **env)
{
	char	**commands;
	char	*path;

	commands = ft_split(av, ' ');
	path = take_path(commands[0], env);
	if (id == 0)
		{
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (execve(path,commands,env) == -1)
			{
				perror("execve failed");
				exit(1);
			}
		}
}

int main(int ac, char **av, char **env)
{
	int 	fd[2];
	int		id;
	int		id2;
	
	if (ac == 3)
	{
		pipe(fd);
		id = fork();
		first_child(id, fd, av[1], env);
		id2 = fork();
		second_child(id2, fd, av[2], env);
		close(fd[0]);
		close(fd[1]);
		waitpid(id,NULL,0);
		waitpid(id2,NULL,0);
	}
	else
		printf("arg not 2");
	return 0;
}