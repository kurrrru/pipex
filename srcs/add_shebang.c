/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shebang.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:24:34 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 11:59:12 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**add_shebang(char **cmd, char *path)
{
	int		i;
	int		cmd_size;
	char	**new_cmd;

	cmd_size = 0;
	while (cmd[cmd_size])
		cmd_size++;
	new_cmd = (char **)malloc((cmd_size + 2) * sizeof(char *));
	if (!new_cmd)
		return (free(cmd), NULL);
	new_cmd[0] = ft_strdup(path);
	if (!new_cmd[0])
		return (free(new_cmd), free(cmd), NULL);
	i = 0;
	while (cmd[i])
	{
		new_cmd[i + 1] = ft_strdup(cmd[i]);
		if (!new_cmd[i + 1])
			return (free_2d(new_cmd), free(cmd), NULL);
		i++;
	}
	new_cmd[i + 1] = NULL;
	return (free(cmd), new_cmd);
}
