/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 04:07:27 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/28 01:13:16 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_radius(t_list *list, void *obj, int type)
{
	char **buff;

	if (ft_strchr(list->content, '='))
	{
		buff = ft_strsplit(list->content, '=');
		buff[0] = ft_strtrim(buff[0]);
		if (ft_strequ(buff[0], "radius"))
		{
			if (type == CONE)
				((t_cone *)obj)->radius = (float)ft_atoi(buff[1]) * M_PI / 180;
			if (type == CYLINDER)
				((t_cylinder *)obj)->radius = (float)ft_atoi(buff[1]);
			if (type == SPHERE)
				((t_sphere *)obj)->radius = (float)ft_atoi(buff[1]);
		}
		free(buff);
	}
}
