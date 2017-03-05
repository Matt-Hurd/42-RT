/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 23:18:37 by mhurd             #+#    #+#             */
/*   Updated: 2017/03/05 13:26:58 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb	*anti_alias(t_data *d, int y, int x, t_rgb *new)
{
	int		yi;
	int		xi;
	float	count;
	float	weight;

	yi = MAX(-1, y - 2);
	count = 0;
	while (++yi < MIN(d->s->size.y, y + 2))
	{
		xi = MAX(-1, x - 2);
		while (++xi < MIN(d->s->size.x, x + 2))
		{
			weight = (xi == x && yi == y) ? 5 : 1;
			new->r += d->image[yi][xi].r * weight;
			new->g += d->image[yi][xi].g * weight;
			new->b += d->image[yi][xi].b * weight;
			count += weight;
		}
	}
	new->r /= count;
	new->g /= count;
	new->b /= count;
	return (new);
}

t_rgb	*sepia(t_data *d, int y, int x, t_rgb *new)
{
	new->r = d->image[y][x].r;
	new->g = d->image[y][x].g;
	new->b = d->image[y][x].b;
	new->r += 112.0 / 255;
	new->g += 66.0 / 255;
	new->b += 20.0 / 255;
	new->r /= 2;
	new->g /= 2;
	new->b /= 2;
	return (new);
}

void	post_process(t_data *d)
{
	int		x;
	int		y;
	t_rgb	new;

	y = -1;
	while (++y < d->s->size.y)
	{
		x = -1;
		while (++x < d->s->size.x)
		{
			if (d->s->aa == 1)
				anti_alias(d, y, x, &new);
			else if (d->s->sepia == 1)
				sepia(d, y, x, &new);
			else
				new = d->image[y][x];
			put_pixel(d, x, y, new);
		}
	}
}
