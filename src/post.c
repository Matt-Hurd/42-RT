/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 23:18:37 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/25 20:01:43 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_rgb		*anti_alias(t_data *d, int y, int x, t_rgb *new)
{
	int		yi;
	int		xi;
	float	count;
	float	weight;

	yi = MAX(-1, y - 2);
	count = 0;
	while (++yi < MIN(d->scene->size.y, y + 2))
	{
		xi = MAX(-1, x - 2);
		while (++xi < MIN(d->scene->size.x, x + 2))
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

void	post_process(t_data *d)
{
	int		x;
	int		y;
	t_rgb	new;

	y = -1;
	while (++y < d->scene->size.y)
	{
		x = -1;
		while (++x < d->scene->size.x)
		{
			if (d->scene->aa)
				anti_alias(d, y, x, &new);
			else
				new = d->image[y][x];
			put_pixel(d, x, y, new);
		}
	}
}