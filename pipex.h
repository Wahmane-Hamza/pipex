/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:29:50 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/26 18:13:48 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct l_data
{
	int	exit_num;
}		t_data;

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define INFILE 0
# define OUTFILE 1

// pipex_bonus
void	exec(char *cmd, char **env);
void	redir(char *cmd, char **env);
void	redir2(char *cmd, char **env, int fdout);
void	redir3(char *cmd, char **env, int fdin);

// commands_help
void	failed_fork(int *fd);
void	failed_pipe(void);
void	input_error(char *arg_ex);
void	close_open(int open, int fd);
void	open_write(char *filename);

// commands_help2
char	*get_path(char **paths, char *command);
char	*take_path(char **commands, char *command, char **env);
void	ft_free(char **get_free);
void	check_arg(char *av, char **commands, char **env);
void	ft_write(char **commands, char *path, char *signal, int ft_exit);

// commands_help3
void	here_doc(int ac, char **av, char **env);
void	redir_here_doc(int *pipe_fd, char **av, int ac, char **env);
int		openfile(char *filename, int mode);
int		wait_child(t_data data, int fdout);
void	close_pipes(int *pipes);

//check
void	check(char *cmd, int *fd);

#endif