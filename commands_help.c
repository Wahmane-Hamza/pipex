/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/25 10:42:27 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
