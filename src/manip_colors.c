/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 06:57:09 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/29 07:00:22 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
