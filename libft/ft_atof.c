/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 08:26:12 by mhurd             #+#    #+#             */
/*   Updated: 2017/01/18 11:14:28 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Handles floats up to max int or down to min int
*/

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	if (ft_strlen(c) > 9)
		c[9] = 0;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	return (res + ((res > 0) ? res2 : -res2));
}
