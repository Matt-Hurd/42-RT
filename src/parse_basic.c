/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 17:14:06 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 08:11:34 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_material(char **buff, t_props *props)
{
	if (ft_strequ(buff[1], "marble"))
		props->material = MAT_MARBLE;
}

void	parser_set_props(char **buff, t_props *props)
{
	if (ft_strequ(buff[0], "pos"))
		parse_triple(buff[1], &props->pos);
	else if (ft_strequ(buff[0], "rot"))
		parse_triple(buff[1], &props->rot);
	else if (ft_strequ(buff[0], "color"))
		parse_color(buff[1], &props->color);
	else if (ft_strequ(buff[0], "reflect"))
		props->reflect = (float)ft_atoi(buff[1]) / 100;
	else if (ft_strequ(buff[0], "gloss"))
		props->gloss = (float)ft_atoi(buff[1]) / 100;
	else if (ft_strequ(buff[0], "transparency"))
		props->trans = (float)ft_atoi(buff[1]) / 100;
	else if (ft_strequ(buff[0], "density"))
		props->density = (float)ft_atoi(buff[1]) / 100;
	else if (ft_strequ(buff[0], "radiance"))
		props->radiance = (float)ft_atoi(buff[1]) / 100;
	else if (ft_strequ(buff[0], "bump"))
		props->bump = (float)ft_atoi(buff[1]) / 100;
	else if (ft_strequ(buff[0], "material"))
		set_material(buff, props);
}

void	parse_props(t_list *list, t_props *props)
{
	char	**buff;
	char	*tmp;

	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			tmp = buff[0];
			buff[0] = ft_strtrim(buff[0]);
			free(tmp);
			tmp = buff[1];
			buff[1] = ft_strtrim(buff[1]);
			free(tmp);
			parser_set_props(buff, props);
			ft_free_strsplit(list->content, buff, '=');
		}
		list = list->next;
	}
	scale_vector(M_PI / 180, &props->rot, &props->rot);
}
