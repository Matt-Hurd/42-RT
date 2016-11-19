/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 18:52:56 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/28 01:13:22 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		del_object(char **s, t_data *d)
{
	int		num;
	t_list	*obj;

	if ((ft_strequ(s[0], "delete") || ft_strequ(s[0], "rm"))
		&& (num = ft_atoi(s[1])))
		if ((obj = get_object(d, num)))
		{
			ft_lstdelcont(&d->s->objects, obj->content);
			return (1);
		}
	return (0);
}

int		add_object(char **s, t_data *d)
{
	t_list	*new;
	void	*obj;
	int		type;

	obj = ft_memalloc(sizeof(t_sphere));
	if (!ft_strequ(s[0], "add"))
		return (0);
	if (ft_strequ(s[1], "sphere"))
		type = SPHERE;
	else if (ft_strequ(s[1], "cylinder"))
		type = CYLINDER;
	else if (ft_strequ(s[1], "plane"))
		type = PLANE;
	else if (ft_strequ(s[1], "cone"))
		type = CONE;
	else if (ft_strequ(s[1], "light"))
		type = LIGHT;
	else
		return (0);
	new = ft_lstnew(obj, sizeof(t_sphere));
	new->content_size = type;
	ft_lst_add_back(&d->s->objects, new);
	return (1);
}
