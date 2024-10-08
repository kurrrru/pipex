/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:16:45 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 12:35:49 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_wrap(int fd)
{
	if (fd != FAILURE && close(fd) == FAILURE)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

void	dup2_wrap(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == FAILURE)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(MSG_CMD_NOT_FOUND, STDERR_FILENO);
	exit(EXIT_CMD_NOT_FOUND);
}

void	quote_error(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(MSG_QUOTE_ERROR, STDERR_FILENO);
}

void	usage_error(void)
{
	ft_putstr_fd(MSG_USAGE_ERROR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
