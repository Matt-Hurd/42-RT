/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:34:31 by mhurd             #+#    #+#             */
/*   Updated: 2017/03/05 14:56:18 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void print_progress(t_args *a)
{
	char	*s;
	float	percent;
	int		x;
	int		y;

	a->d->drawn += 1;
	if (a->d->drawn % a->d->s->size.x != 0)
		return ;
	s = (char *)ft_memalloc(40);
	s[0] = '[';
	percent = a->d->drawn / ((float)a->d->s->size.x * a->d->s->size.y);
	x = percent * 100 / 5;
	y = x;
	while (x-- > 0)
		s[x + 1] = '+';
	while (++y < 20)
		s[y] = '-';
	s[20] = ']';
	s[21] = '\r';
	ft_putstr(s);
}

void clear_loading()
{
	ft_putstr("                                        \r");
}
