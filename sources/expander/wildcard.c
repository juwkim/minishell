/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:17:39 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/10 10:57:49 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdlib.h>
​
static int	count_word(char const *str, char charset)
{
	int	i;
	int	cnt;
​
	cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == charset)
			i++;
		if (str[i])
			cnt++;
		while (str[i] != charset && str[i])
			i++;
	}
	return (cnt);
}
​
static int	word_len(char const *str, char charset)
{
	int	i;
​
	i = 0;
	while (str[i] && str[i] != charset)
		i++;
	return (i);
}
​
static char	*word_cpy(char const *src, char charset)
{
	int		i;
	int		size;
	char	*res;
​
	size = word_len(src, charset);
	res = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
​
static char	**free_word(char **word)
{
	int	i;
​
	i = 0;
	while (word[i])
		free(word[i++]);
	free(word);
	return (0);
}
​
char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
​
	if (!s)
		return (0);
	res = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		res[j] = word_cpy(&s[i], c);
		if (!res[j++])
			return (free_word(res));
		while (s[i] != c && s[i])
			i++;
	}
	res[j] = 0;
	return (res);
}
​
#include <stdio.h>
​
int main(int argc, char **argv)
{
	char **wildcard;
	int	check[argc];
	int	i;
	int	j;
	int k;
​
	bzero(check, sizeof(check));
	if (strcmp(argv[1], "*") == 0)
	{
		i = 2;
		while (argv[i])
		{
			printf("%s : true\n", argv[i]);
			++i;
		}
		return (0);
	}
	wildcard = ft_split(argv[1], '*');
	i = 2;
	while (i < argc)
	{
		j = 0;
		k = 0;
		while (argv[i][j])
		{
			if (wildcard[k + 1] != NULL)
			{
				if (strncmp(&argv[i][j], wildcard[k], strlen(wildcard[k]) - 1) == 0)
				{
					j += strlen(wildcard[k]) - 1;
					++k;
				}
				else
					++j;
			}
			else
			{
				if (strncmp(&argv[i][j], wildcard[k], strlen(wildcard[k])) == 0)
				{
					check[i] = 1;
					break ;
				}
				++j;
			}
		}
		++i;
	}
	i = 2;
	while (i < argc)
	{
		if (check[i])
			printf("%s : true\n", argv[i]);
		else
			printf("%s : false\n", argv[i]);
		++i;
	}
}