/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 04:07:27 by mhurd             #+#    #+#             */
/*   Updated: 2017/01/18 00:32:27 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_float_trip(t_vec3 *dest, char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	if (ft_count_words(line, ' ') != 4)
		ft_error("Invalid float triple");
	dest->x = atof(split[1]);
	dest->y = atof(split[2]);
	dest->z = atof(split[3]);
	ft_free_strsplit(line, split, ' ');
}

void	set_radius(t_list *list, void *obj, int type)
{
	char **buff;
	char *tmp;

	if (ft_strchr(list->content, '='))
	{
		buff = ft_strsplit(list->content, '=');
		tmp = ft_strtrim(buff[0]);
		if (ft_strequ(tmp, "radius"))
		{
			if (type == CONE)
				((t_cone *)obj)->radius = (float)ft_atoi(buff[1]) * M_PI / 180;
			if (type == CYLINDER)
				((t_cylinder *)obj)->radius = (float)ft_atoi(buff[1]);
			if (type == SPHERE)
				((t_sphere *)obj)->radius = (float)ft_atoi(buff[1]);
		}
		free(tmp);
		ft_free_strsplit(list->content, buff, '=');
	}
}
