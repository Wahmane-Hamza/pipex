/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:51:59 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/24 14:40:37 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check(char *cmd, int *fd)
{
	if (cmd[0] == ' ' || (cmd[0] >= 9 && cmd[0] <= 13))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": not found", 11);
		write(2, "\n", 1);
		if (fd)
		{
			close(fd[0]);
			close(fd[1]);
		}
		exit(1);
	}
	else if (cmd[0] == '\0')
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied", 19);
		write(2, "\n", 1);
		if (fd)
		{
			close(fd[0]);
			close(fd[1]);
		}
		exit(1);
	}
}
