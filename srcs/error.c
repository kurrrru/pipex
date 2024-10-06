/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:16:45 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/06 13:03:25 by nkawaguc         ###   ########.fr       */
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
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(EXIT_CMD_NOT_FOUND);
}

void	quote_error(char *cmd)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": quote error\n", 14);
}

void	usage_error(void)
{
	write(STDERR_FILENO, "usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	exit(EXIT_FAILURE);
}
