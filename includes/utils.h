/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:57:14 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/23 14:35:57 by nkawaguc         ###   ########.fr       */
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

void	free_2d(char **ptr);
char	*get_path_from_pathset(char *cmd, char *path_set);
char	*get_path(char *cmd, char **envp);
int		execute(char *sentence, char **envp);

void	close_wrap(int fd);

#endif
