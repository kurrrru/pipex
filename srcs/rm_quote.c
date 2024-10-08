/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:49 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/10/08 12:57:35 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	slide(char *str, int *i, int *j);

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
				if (slide(*str, &i, &j) == FAILURE)
					return (FAILURE);
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
	return (SUCCESS);
}

static int	slide(char *str, int *i, int *j)
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
		return (FAILURE);
	while (++(*i) < k)
		str[(*j)++] = str[*i];
	str[*i] = '\0';
	return (SUCCESS);
}
