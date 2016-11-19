/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 06:57:09 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/19 04:06:36 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		color_to_int(t_rgb color)
{
	int red;
	int green;
	int blue;

	red = color.r * 255;
	green = color.g * 255;
	blue = color.b * 255;
	return (((int)red) << 16 | ((int)green) << 8 | blue);
}

void	clear_color(t_rgb *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	add_colors(t_rgb *c1, t_rgb *c2, t_rgb *c3)
{
	c3->r = c1->r + c2->r;
	c3->g = c1->g + c2->g;
	c3->b = c1->b + c2->b;
}

void	sub_colors(t_rgb *c1, t_rgb *c2, t_rgb *c3)
{
	c3->r = c1->r - c2->r;
	c3->g = c1->g - c2->g;
	c3->b = c1->b - c2->b;
}

void	scale_color(float scale, t_rgb *c1, t_rgb *c2)
{
	c2->r = c1->r * scale;
	c2->g = c1->g * scale;
	c2->b = c1->b * scale;
}
