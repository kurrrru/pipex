/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:16:45 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/23 19:41:13 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	close_wrap(int fd)
{
	if (fd != -1 && close(fd) == -1)
		perror("close");
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
