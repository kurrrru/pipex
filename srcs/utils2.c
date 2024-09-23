/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:49 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/23 19:51:25 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	rm_quote(char **str)
{
	int i;
	int	j;
	int	k;
	int	type;

	type = 0;
	while (*str)
	{
		i = -1;
		j = 0;
		while ((*str)[++i])
		{
			if ((*str)[i] == '\'' || (*str)[i] == '\"')
				type = 1;
			else
				(*str)[j++] = (*str)[i];
			if (type == 1)
			{
				k = i + 1;
				while ((*str)[k] && (*str)[k] != (*str)[i])
					k++;
				if (!(*str)[k])
					return (-1);
				while (++i < k)
					(*str)[j++] = (*str)[i];
				(*str)[i] = '\0';
				type = 0;
			}
		}
		(*str)[j] = '\0';
		str++;
	}
	return (0);
}