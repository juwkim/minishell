/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pattern_match.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:54:27 by juwkim            #+#    #+#             */
/*   Updated: 2023/02/12 16:03:52 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"

static char	**dp_init(int n, int m, char *pattern);

bool	is_pattern_match(char *str, char *pattern, int pattern_len)
{
	const int	n = ft_strlen(str);
	int			i;
	int			j;
	char		**dp;
	bool		match;

	dp = dp_init(n, pattern_len, pattern);
	if (dp == NULL)
		return (false);
	i = 0;
	while (++i <= n)
	{
		j = 0;
		while (++j <= pattern_len)
		{
			if (pattern[j - 1] == '*')
				dp[i][j] = (dp[i][j - 1] || dp[i - 1][j]);
			else if (pattern[j - 1] == str[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
		}
	}
	match = dp[n][pattern_len];
	ft_free_array(dp, n + 1);
	return (match);
}

static char	**dp_init(int n, int m, char *pattern)
{
	char	**dp;
	int		i;
	int		j;

	dp = malloc(sizeof(char *) * (n + 1));
	if (dp == NULL)
		return (NULL);
	i = 0;
	while (i <= n)
	{
		dp[i] = (char *) ft_calloc(m + 1, sizeof(char));
		if (dp[i] == NULL)
		{
			ft_free_array(dp, i);
			return (NULL);
		}
		++i;
	}
	j = 1;
	dp[0][0] = true;
	while (j <= m && pattern[j - 1] == '*')
		dp[0][j++] = true;
	return (dp);
}
