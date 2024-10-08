/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:16:43 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 10:50:10 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	is_control(char c)
{
	if (c <= 8 || (14 <= c && c <= 31) || c == 127)
		return (TRUE);
	return (FALSE);
}

int	is_binary(int fd, char *buf)
{
	int		read_size;
	int		num_control;
	int		i;

	read_size = read(fd, buf, CHECK_BYTES);
	if (read_size == FAILURE)
		return (FAILURE);
	buf[read_size] = '\0';
	i = -1;
	num_control = 0;
	while (++i < read_size)
		num_control += is_control(buf[i]);
	if (num_control * BINARY_THRESHOLD_RATIO > read_size)
		return (TRUE);
	return (FALSE);
}

int	is_shebang_found(char *buf)
{
	if (ft_strlen(buf) < 2 || buf[0] != '#' || buf[1] != '!')
		return (FALSE);
	return (TRUE);
}

char	*shebang(char *path, char ***cmd, char **envp)
{
	int		fd;
	char	buf[CHECK_BYTES + 1];
	char	*line;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == FAILURE)
		return (path);
	if (is_binary(fd, buf) != FALSE || is_shebang_found(buf) == TRUE)
		return (close(fd), path);
	line = get_shell(envp);
	if (!line)
		return (close(fd), free(path), NULL);
	*cmd = add_shebang(*cmd, line);
	if (!*cmd)
		return (close(fd), free(path), free(line), NULL);
	return (close(fd), free(path), line);
}

char	*get_shell(char **envp)
{
	int		i;
	char	*shell;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHELL=", 6) == 0)
		{
			shell = ft_strdup(envp[i] + 6);
			if (!shell)
				return (perror("malloc"), NULL);
			return (shell);
		}
	}
	return (ft_strdup("/bin/bash"));
}
