/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:29:50 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/24 13:52:48 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define INFILE 0
# define OUTFILE 1

// pipex_bonus
int		openfile(char *filename, int mode);
void	exec(char *cmd, char **env);
void	redir(char *cmd, char **env);
void	redir2(char *cmd, char **env);

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

// commands_bonus
void	here_doc(int ac, char **av, char **env);
void	redir_here_doc(int *pipe_fd, char **av, int ac, char **env);

//check
void	check(char *cmd);

#endif