/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:49 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/24 20:03:38 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	slide(char *str, int *i, int *j)
{
	int	k;

	k = *i + 1;
	while (str[k] && str[k] != str[*i])
	{
		if (str[k] == '\\' && str[k + 1])
			k++;
		k++;
	}
	if (!str[k])
		return (-1);
	while (++(*i) < k)
		str[(*j)++] = str[*i];
	str[*i] = '\0';
	return (0);
}

int	rm_quote(char **str)
{
	int	i;
	int	j;

	while (*str)
	{
		i = -1;
		j = 0;
		while ((*str)[++i])
		{
			if ((*str)[i] == '\'' || (*str)[i] == '\"')
			{
				if (slide(*str, &i, &j) == -1)
					return (-1);
			}
			else
			{
				(*str)[j++] = (*str)[i];
				if ((*str)[i] == '\\' && (*str)[i + 1])
					(*str)[j++] = (*str)[++i];
			}
		}
		(*str++)[j] = '\0';
	}
	return (0);
}
