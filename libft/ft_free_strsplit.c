/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 11:43:59 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/10 11:48:21 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_strsplit(char *s, char **buff, char split)
{
	int x;
	int len;

	len = ft_count_words(s, split);
	x = -1;
	while (++x < len)
		free(buff[x]);
	free(buff);
}
