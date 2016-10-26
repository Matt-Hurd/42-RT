/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:59:52 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/25 19:28:17 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_list	*get_object(t_data *d, int num)
{
	int		x;
	t_list	*ret;

	x = 0;
	ret = d->scene->objects;
	while (ret)
	{
		++x;
		if (x == num)
			return (ret);
		ret = ret->next;
	}
	return (ret);
}

static int	change_rotation(t_sphere *obj, float new, char which)
{
	float		global_matrix[4][4];
	t_vec3		n;

	if (which == 'x')
		obj->props.rot.x = new;
	else if (which == 'y')
		obj->props.rot.y = new;
	else if (which == 'z')
		obj->props.rot.z = new;
	else
		return (0);
	n.x = 0;
	n.y = -1;
	n.z = 0;
	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix,
		obj->props.rot.x,
		obj->props.rot.y,
		obj->props.rot.z);
	ft_vec_mult_mat(&n, global_matrix, &obj->props.rot);
	return (1);
}

static int	set_props(char **s, t_sphere *obj)
{
	if (ft_strequ(s[2], "posx"))
		obj->props.pos.x = ft_atoi(s[3]);
	else if (ft_strequ(s[2], "posy"))
		obj->props.pos.y = ft_atoi(s[3]);
	else if (ft_strequ(s[2], "posz"))
		obj->props.pos.z = ft_atoi(s[3]);
	else if (ft_strequ(s[2], "r"))
		obj->props.color.r = (float)ft_atoi(s[3]) / 255;
	else if (ft_strequ(s[2], "g"))
		obj->props.color.g = (float)ft_atoi(s[3]) / 255;
	else if (ft_strequ(s[2], "b"))
		obj->props.color.b = (float)ft_atoi(s[3]) / 255;
	else if (ft_strequ(s[2], "reflect"))
		obj->props.reflect = (float)ft_atoi(s[3]) / 100;
	else if (ft_strstr(s[2], "rot"))
		return (change_rotation(obj, ft_atoi(s[3]) * M_PI / 180, s[2][3]));
	else if (ft_strstr(s[2], "radiance"))
		obj->props.radiance = (float)ft_atoi(s[3]) / 100;
	else
		return(0);
	return (1);
}

static int	set_values(char **s, int c, t_list *obj, t_data *d)
{
	(void)c;
	(void)d;
	if (ft_strequ(s[2], "radius") && (obj->content_size != PLANE &&
		obj->content_size != LIGHT))
		return (((t_sphere *)obj->content)->radius = ft_atoi(s[3]));
	else
		return (set_props(s, obj->content));
}

int		modify_object(char **s, int c, t_data *d)
{
	int		num;
	t_list	*obj;

	if (c >= 4)
		if (ft_strequ(s[0], "set") && (num = ft_atoi(s[1])))
			if ((obj = get_object(d, num)))
				return (set_values(s, c, obj, d));
	return (0);
}