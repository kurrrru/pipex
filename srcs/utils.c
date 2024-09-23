/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:02:34 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/23 12:48:23 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	free_2d(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

char	*get_path_from_pathset(char *cmd, char *path_set)
{
	int		i;
	char	*path_part;
	char	*path;
	char	**path_list;

	path_list = ft_split(path_set + 5, ':');
	if (!path_list)
		return (perror("malloc"), NULL);
	i = -1;
	while (path_list[++i])
	{
		path_part = ft_strjoin(path_list[i], "/");
		if (!path_part)
			return (perror("malloc"), free_2d(path_list), NULL);
		path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (!path)
			return (perror("malloc"), free_2d(path_list), NULL);
		if (access(path, F_OK) == 0)
			return (free_2d(path_list), path);
		free(path);
	}
	return (cmd_not_found(cmd), free_2d(path_list), NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;

	if (access(cmd, F_OK) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (perror("malloc"), NULL);
		return (path);
	}
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (get_path_from_pathset(cmd, envp[i]));
	return (cmd_not_found(cmd), NULL);
}

int	execute(char *sentence, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(sentence, ' ');
	if (!cmd)
	{
		perror("malloc");
		return (-1);
	}
	path = get_path(cmd[0], envp);
	if (!path)
	{
		return (free_2d(cmd), -1);
	}
	execve(path, cmd, envp);
	perror(path);
	return (free_2d(cmd), free(path), -1);
}
