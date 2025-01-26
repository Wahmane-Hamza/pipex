/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:40:18 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/26 17:01:00 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
	exit(127);
}

void	redir_here_doc(int *pipe_fd, char **av, int ac, char **env)
{
	int	fdout;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN);
	close(pipe_fd[0]);
	redir(av[3], env);
	fdout = openfile(av[ac - 1], OUTFILE);
	redir2(av[4], env, fdout);
	close(fdout);
	exit(127);
}

void	here_doc(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	char	*line;

	if (ac == 6)
	{
		if (pipe(pipe_fd) == -1)
			failed_pipe();
		while (1)
		{
			write(1, ">", 1);
			line = get_next_line(0);
			if (!line)
				close_pipes(pipe_fd);
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0
				&& line[ft_strlen(av[2])] == '\n')
				break ;
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		free(line);
		redir_here_doc(pipe_fd, av, ac, env);
	}
	else
		input_error("Ex: ./pipex here_doc LIMITER cmd cmd1 file\n");
}

int	openfile(char *filename, int mode)
{
	int	fd;

	if (mode == INFILE)
	{
		if (filename[0] == '/' && filename[1] == '\0')
			return (open(filename, O_RDONLY));
		if (access(filename, F_OK | W_OK))
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, ": ", 2);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
		}
		return (open(filename, O_RDONLY));
	}
	else
	{
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(filename, W_OK) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, ": ", 2);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
		}
		return (fd);
	}
}

int	wait_child(t_data data)
{
	int	status;

	(void)data;
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			data.exit_num = WEXITSTATUS(status);
	}
	return (data.exit_num);
}
