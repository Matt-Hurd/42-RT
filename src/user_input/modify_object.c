/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:59:52 by mhurd             #+#    #+#             */
/*   Updated: 2017/01/18 11:13:53 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list		*get_object(t_data *d, int num)
{
	int		x;
	t_list	*ret;

	x = 0;
	ret = d->s->objects;
	while (ret)
	{
		++x;
		if (x == num)
			return (ret);
		ret = ret->next;
	}
	return (ret);
}

static int	set_values(char **s, int c, t_list *obj, t_data *d)
{
	(void)c;
	(void)d;
	if (ft_strequ(s[2], "radius") && (obj->content_size != PLANE &&
		obj->content_size != LIGHT))
	{
		if (obj->content_size == CONE)
			return (((t_sphere *)obj->content)->radius =
				(float)ft_atoi(s[3]) * M_PI / 180);
		else
			return (((t_sphere *)obj->content)->radius = ft_atoi(s[3]));
	}
	else
	{
		if (set_props(s, obj->content))
		{
			if (obj->content_size == MODEL)
				update_model(obj->content);
			return (1);
		}
		return (0);
	}
}

int			modify_object(char **s, int c, t_data *d)
{
	int		num;
	t_list	*obj;

	if (c >= 4)
		if (ft_strequ(s[0], "set") && (num = ft_atoi(s[1])))
			if ((obj = get_object(d, num)))
				return (set_values(s, c, obj, d));
	return (0);
}
