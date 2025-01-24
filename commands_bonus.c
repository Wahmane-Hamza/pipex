/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:40:18 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/24 21:02:03 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
	exit(1);
}

void	redir_here_doc(int *pipe_fd, char **av, int ac, char **env)
{
	int	fdout;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN);
	close(pipe_fd[0]);
	fdout = openfile(av[ac - 1], OUTFILE);
	if (fdout == -1)
		exit(1);
	if (dup2(fdout, STDOUT) == -1)
		exit(1);
	close(fdout);
	redir(av[3], env);
	redir2(av[4], env);
	exit(1);
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

void	open_file(char **av, int ac)
{
	int	fdin;
	int	fdout;

	fdin = openfile(av[1], INFILE);
	if (fdin == -1)
		exit(1);
	if (dup2(fdin, STDIN) == -1)
		exit(1);
	close(fdin);
	fdout = openfile(av[ac - 1], OUTFILE);
	if (fdout == -1)
		exit(1);
	if (dup2(fdout, STDOUT) == -1)
		exit(1);
	close(fdout);
}
