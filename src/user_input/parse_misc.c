/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:48:11 by mhurd             #+#    #+#             */
/*   Updated: 2017/03/05 13:26:04 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	display_help(void)
{
	ft_putstr("Valid commands: \n\
	aa on/off\n\
		Enables/Disables AntiAliasing\n\
	ambient [0 - 100]\n\
		Set the intensity of ambient light\n\
	depth [num]\n\
		Set the max recursion depth\n\
	set [objnum] [prop] [value]\n\
		Properties: posx/y/z, rotx/y/z, r/g/b, radiance, reflect\n\
		Properties: gloss, trans, material, bump\n\
		Materials:  marble\n\
	add [objtype]\n\
		Add an object of [sphere/cone/cylinder/plane/light]\n\
	delete/rm [objnum]\n\
		Removes and object from the scene\n\
	info\n\
		Displays a list of objects\n\
	help\n\
		Displays this page\n");
}

int		parse_misc(char **split, int c, t_data *d)
{
	if (ft_strequ(split[0], "info"))
		print_scene_info(d);
	if (c >= 2)
	{
		if (ft_strequ(split[0], "aa"))
			d->s->aa = ft_atoi(split[1]);
		if (ft_strequ(split[0], "sepia"))
			d->s->sepia = ft_atoi(split[1]);
		if (ft_strequ(split[0], "ambient"))
			d->s->ambient = CLAMP((float)ft_atoi(split[1]) / 100, -0.20, 1.20);
		else if (ft_strequ(split[0], "depth"))
			d->s->maxdepth = ft_atoi(split[1]);
		else
			return (0);
		return (1);
	}
	else if (ft_strequ(split[0], "help"))
		display_help();
	return (0);
}
