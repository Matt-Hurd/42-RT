/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:23:39 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 17:08:17 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_find_word(const char *str, int i, char **ret, char c)
{
	int		len;
	int		space;

	space = 0;
	len = 0;
	while (*str == c)
	{
		str++;
		space++;
	}
	while (str[len] && str[len] != c)
		len++;
	if (len > 0)
	{
		ret[i] = ft_strnew(len);
		ft_strncpy(ret[i], str, len);
	}
	return (space + len);
}

char			**ft_strsplit(char const *s, char c)
{
	int		len;
	char	**ret;
	int		i;
	int		wc;

	if (!s)
		return (NULL);
	wc = ft_count_words(s, c);
	len = 0;
	ret = (char **)ft_memalloc((wc + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	len = 0;
	while (*s)
	{
		len = ft_find_word(s, i++, ret, c);
		s += len;
	}
	ret[wc] = 0;
	return (ret);
}
