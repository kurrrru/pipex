/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:57:14 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 13:12:26 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

# define PROPER_ARGC 5

# define PID_WHEN_CHILD 0

# define EXIT_CMD_NOT_FOUND 127

# define ENVP_PATH "PATH="
# define ENVP_PATH_SIZE 5
# define ENVP_PATH_DELIMITER ':'
# define ENVP_SHELL "SHELL="
# define ENVP_SHELL_SIZE 6

# define SHEBANG_PREFIX "#!"
# define SHEBANG_PREFIX_SIZE 2
# define CHECK_BYTES 1024
# define BINARY_THRESHOLD_RATIO 10
# define DEFAULT_SHELL "/bin/bash"

# define MSG_CMD_NOT_FOUND ": command not found\n"
# define MSG_QUOTE_ERROR ": quote error\n"
# define MSG_USAGE_ERROR "usage: ./pipex file1 cmd1 cmd2 file2\n"

// exec.c
void	free_2d(char **ptr);
int		execute(char *sentence, char **envp);

// error.c
void	close_wrap(int fd);
void	cmd_not_found(char *cmd);
void	quote_error(char *cmd);
void	dup2_wrap(int oldfd, int newfd);
void	usage_error(void);

// rm_quote.c
int		rm_quote(char **str);

// ft_split_pipex.c
char	**ft_split_pipex(const char *s, char c);

// shebang.c
char	*shebang(char *path, char ***cmd, char **envp);

// add_shebang.c
char	**add_shebang(char **cmd, char *path);

// pipex.c
int		pipex(char **argv, char **envp);

#endif
