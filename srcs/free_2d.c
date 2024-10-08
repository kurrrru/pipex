/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:48 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 12:58:53 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_2d(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}
