/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:57:14 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 10:40:10 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "get_next_line.h"

# define EXIT_CMD_NOT_FOUND 127
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

# define SHEBANG_PREFIX "#!"
# define SHEBANG_PREFIX_SIZE 2

# define CHECK_BYTES 1024

# define BINARY_THRESHOLD_RATIO 10

void	free_2d(char **ptr);
char	*get_path_from_pathset(char *cmd, char *path_set);
char	*get_path(char *cmd, char **envp);
int		execute(char *sentence, char **envp);

void	close_wrap(int fd);
void	cmd_not_found(char *cmd);
void	quote_error(char *cmd);
void	dup2_wrap(int oldfd, int newfd);
void	usage_error(void);

int		rm_quote(char **str);

char	**ft_split_pipex(const char *s, char c);

int		is_control(char c);
int		is_binary(int fd, char *buf);
int		is_shebang_found(char *buf);
char	*shebang(char *path, char ***cmd, char **envp);
char	*get_shell(char **envp);

char	**add_shebang(char **cmd, char *path);

#endif
