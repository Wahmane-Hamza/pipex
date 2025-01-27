/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:40:18 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/27 15:59:51 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int fd, char *tmpfile, int ex)
{
	free(tmpfile);
	close(fd);
	if (ex == 1)
		exit(127);
}

void	redir_here_doc(char **av, char **env, char *tmpfile)
{
	int		fdout;
	t_data	data;
	int		fd;

	fd = openfile(tmpfile, INFILE);
	redir3(av[3], env, fd);
	unlink(tmpfile);
	free(tmpfile);
	close_open(fd);
	fdout = openfile(av[5], 2);
	redir2(av[4], env, fdout);
	close_open(fdout);
	data.exit_num = wait_child(data, fdout);
	exit(data.exit_num);
}

void	here_doc(int ac, char **av, char **env)
{
	int		fd;
	char	*line;
	char	*tmpfile;

	if (ac == 6)
	{
		tmpfile = ft_getrandtmp_file();
		fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		while (1)
		{
			write(1, ">", 1);
			line = get_next_line(0);
			if (!line)
				close_fd(fd, tmpfile, 1);
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0
				&& line[ft_strlen(av[2])] == '\n')
				break ;
			write(fd, line, ft_strlen(line));
			free(line);
		}
		close_fd(fd, line, 0);
		redir_here_doc(av, env, tmpfile);
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
			open_write(filename, strerror(errno));
		return (open(filename, O_RDONLY));
	}
	else
	{
		if (mode == 2)
			fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(filename, W_OK) == -1)
			open_write(filename, strerror(errno));
		return (fd);
	}
}

int	wait_child(t_data data, int fdout)
{
	int	status;

	(void)data;
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			data.exit_num = WEXITSTATUS(status);
	}
	if (fdout == -1)
		data.exit_num = 1;
	return (data.exit_num);
}
