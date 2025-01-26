/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:40:22 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/26 17:15:57 by hwahmane         ###   ########.fr       */
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
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	free(path);
	return (NULL);
}

char	*take_path(char **commands, char *command, char **env)
{
	int		i;
	char	**paths;
	char	*path;

	i = -1;
	while (env[++i] && ft_strnstr(env[i], "PATH", 4) == 0)
		;
	if (!env[i])
		ft_write(commands, NULL, ": not found", 127);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = get_path(paths, command);
	if (!path)
	{
		ft_free(paths);
		return (NULL);
	}
	ft_free(paths);
	return (path);
}

void	ft_free(char **get_free)
{
	int	i;

	if (!get_free)
		return ;
	i = 0;
	while (get_free[i])
	{
		free(get_free[i]);
		i++;
	}
	free(get_free);
	return ;
}

void	check_arg(char *av, char **commands, char **env)
{
	int	i;

	if (ft_strncmp(av, "./", 2) == 0 || ft_strncmp(av, "../", 3) == 0
		|| ft_strncmp(av, "/", 1) == 0)
	{
		if (execve(commands[0], commands, env) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, ": ", 2);
			ft_write(commands, NULL, NULL, 127);
		}
	}
	i = 1;
	while (av[i])
	{
		if (av[i] == '/')
			ft_write(commands, NULL, ": not found", 127);
		i++;
	}
}

void	ft_write(char **commands, char *path, char *signal, int ft_exit)
{
	if (*commands)
		write(2, commands[0], ft_strlen(commands[0]));
	if (signal)
		write(2, signal, ft_strlen(signal));
	write(2, "\n", 1);
	if (ft_exit)
	{
		if (commands)
			ft_free(commands);
		if (path)
			free(path);
		exit(127);
	}
}
