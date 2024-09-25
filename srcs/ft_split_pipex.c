/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:43:47 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/09/25 18:23:14 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static void	free_rec(char **to_free, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		free(to_free[i]);
	free(to_free);
}

static void	scanning(char *ret, const char *s, char c, int *pos)
{
	int	esc;
	int	quo[2];

	*pos = 0;
	quo[0] = 0;
	quo[1] = 0;
	esc = 0;
	while (s[*pos] != '\0' && (s[*pos] != c || quo[0] || quo[1] || esc))
	{
		quo[0] ^= ((s[*pos] == '\'') && !esc && !quo[1]);
		quo[1] ^= ((s[*pos] == '\"') && !esc && !quo[0]);
		esc = (s[*pos] == '\\' && !esc);
		if (ret)
			ret[*pos] = s[*pos];
		(*pos)++;
	}
}

static int	split_fill(char **ret, int cnt, const char *s, char c)
{
	int	block;
	int	pos;

	block = -1;
	pos = 0;
	while (++block < cnt)
	{
		while (s[pos] == c && s[pos] != '\0')
			pos++;
		s = s + pos;
		scanning(NULL, s, c, &pos);
		ret[block] = (char *)malloc((pos + 1) * sizeof(char));
		if (!ret[block])
			return (free_rec(ret, block), 1);
		scanning(ret[block], s, c, &pos);
		ret[block][pos] = '\0';
	}
	return (0);
}

static int	count_words(const char *s, char c)
{
	int	cnt;
	int	i;
	int	esc;
	int	quo[2];

	i = 0;
	cnt = (s[0] != c && s[0] != '\0');
	quo[0] = (s[0] == '\'');
	quo[1] = (s[0] == '\"');
	esc = (s[0] == '\\');
	while (s[0] != '\0' && s[++i] != '\0')
	{
		cnt += (s[i - 1] == c && s[i] != c && !quo[0] && !quo[1] && !esc);
		quo[0] ^= (s[i] == '\'' && !esc && !quo[1]);
		quo[1] ^= (s[i] == '\"' && !esc && !quo[0]);
		esc = (s[i] == '\\' && !esc);
	}
	return (cnt);
}

char	**ft_split_pipex(const char *s, char c)
{
	int		cnt;
	char	**ret;

	if (!s)
		return (NULL);
	cnt = count_words(s, c);
	ret = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[cnt] = NULL;
	if (split_fill(ret, cnt, s, c) == 1)
		return (NULL);
	return (ret);
}

// int main(int argc, char **argv)
// {
// 	char *sentence = argv[1];
// 	printf("[%s]\n", sentence);
// 	char **splited = ft_split_pipex(sentence, ' ');
// 	int i = 0;
// 	while (splited[i])
// 	{
// 		printf("[%s]\n", splited[i]);
// 		i++;
// 	}
// 	return 0;
// }
