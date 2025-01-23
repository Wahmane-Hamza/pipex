/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:29:50 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/23 15:25:52 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// commands_help
void	failed_dup2(int *fd, int pipe, int file);
void	failed_fork(int *fd);
void	failed_pipe(void);
void	input_error(char *arg_ex);
void	open_faild(int *fd, char *command);

// commands_help2
char	*get_path(char **paths, char *command);
char	*take_path(char **commands, char *command, char **env);
void	ft_free(char **get_free);
void	check_arg(char *av, char **commands, char **env);
void	ft_write(char **commands, char *path, char *signal, int ft_exit);

#endif