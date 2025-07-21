/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/27 15:44:21 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	failed_fork(int *fd)
{
	perror("error");
	close(fd[1]);
	close(fd[0]);
	exit(127);
}

void	failed_pipe(void)
{
	perror("error");
	exit(127);
}

void	input_error(char *arg_ex)
{
	ft_putstr_fd("Bad arguments\n", 2);
	ft_putstr_fd(arg_ex, 2);
	exit(127);
}

void	open_write(char *filename, char *stre)
{
	write(2, stre, ft_strlen(stre));
	write(2, ": ", 2);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
}

void	close_open(int fd)
{
	if (fd != -1)
		close(fd);
}
