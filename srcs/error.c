/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:16:45 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/25 18:36:36 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	close_wrap(int fd)
{
	if (fd != -1 && close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

void	dup2_wrap(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	quote_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": quote error\n", 14);
}

void	usage_error(void)
{
	write(2, "usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	exit(EXIT_FAILURE);
}
