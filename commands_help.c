/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/13 20:45:21 by hwahmane         ###   ########.fr       */
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

void	input_error(void)
{
	ft_putstr_fd("Bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
}

void	open_faild(int *fd)
{
	close(fd[1]);
	close(fd[0]);
	perror("failed to open fd");
	exit(1);
}
