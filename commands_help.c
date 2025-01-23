/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/23 15:18:40 by hwahmane         ###   ########.fr       */
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

void	failed_fork(int *fd)
{
	perror("error");
	close(fd[1]);
	close(fd[0]);
	exit(1);
}

void	failed_pipe(void)
{
	perror("error");
	exit(1);
}

void	input_error(char *arg_ex)
{
	ft_putstr_fd("Bad arguments\n", 2);
	ft_putstr_fd(arg_ex, 2);
	exit(1);
}

void	open_faild(int *fd, char *command)
{
	close(fd[1]);
	close(fd[0]);
	if (command)
	{
		write(2, command, ft_strlen(command));
		write(2, ": No such file or directory", 27);
		write(2, "\n", 1);
	}
	exit(1);
}
