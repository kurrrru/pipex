/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:02:34 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 22:20:04 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_path_from_pathset(char *cmd, char *path_set);
static char	*get_path(char *cmd, char **envp);

int	execute(char *sentence, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_pipex(sentence, CMD_DELIMITER);
	if (!cmd)
		return (perror("malloc"), FAILURE);
	if (rm_quote(cmd) == FAILURE)
		return (quote_error(cmd[0]), free_2d(cmd), FAILURE);
	path = get_path(cmd[0], envp);
	if (!path)
		return (free_2d(cmd), FAILURE);
	if (access(path, X_OK) == 0)
		path = shebang(path, &cmd, envp);
	if (!path || !cmd)
		return (free(path), free_2d(cmd), FAILURE);
	execve(path, cmd, envp);
	return (perror(path), free_2d(cmd), free(path), FAILURE);
}

static char	*get_path_from_pathset(char *cmd, char *path_set)
{
	int		i;
	char	*path_part;
	char	*path;
	char	**path_list;

	path_list = ft_split_pipex(path_set + ENVP_PATH_SIZE, ENVP_PATH_DELIMITER);
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
		if (access(path, F_OK) == SUCCESS)
			return (free_2d(path_list), path);
		free(path);
	}
	return (cmd_not_found(cmd), free_2d(path_list), NULL);
}

static char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;

	if (access(cmd, F_OK) == SUCCESS)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (perror("malloc"), NULL);
		return (path);
	}
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], ENVP_PATH, ENVP_PATH_SIZE) == 0)
			return (get_path_from_pathset(cmd, envp[i]));
	return (cmd_not_found(cmd), NULL);
}
