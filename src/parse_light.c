/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:59:58 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 19:09:46 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_light(t_data *d, t_list *list)
{
	t_light		*light;
	t_list		*ret;

	light = (t_light *)ft_memalloc(sizeof(t_light));
	parse_props(list, &light->props);
	ret = ft_lstnew(light, sizeof(t_light));
	ret->content_size = LIGHT;
	ft_lstadd(&d->scene->objects, ret);
}
