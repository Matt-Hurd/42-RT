/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_props.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 20:13:13 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/19 03:56:13 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	if (obj->props.object)
		return (1);
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

static int	set_props_mat(char **s, t_sphere *obj)
{
	if (ft_strequ(s[2], "material"))
	{
		if (ft_strequ(s[3], "marble"))
		{
			obj->props.material = MAT_MARBLE;
			return (1);
		}
		else
		{
			obj->props.material = MAT_NONE;
		}
	}
	return (0);
}

static int	set_props_2(char **s, t_sphere *obj)
{
	if (ft_strequ(s[2], "reflect"))
		obj->props.reflect = (float)ft_atoi(s[3]) / 100;
	else if (ft_strequ(s[2], "gloss"))
		obj->props.gloss = (float)ft_atoi(s[3]) / 100;
	else if (ft_strequ(s[2], "trans"))
		obj->props.trans = (float)ft_atoi(s[3]) / 100;
	else if (ft_strstr(s[2], "density"))
		obj->props.density = (float)ft_atoi(s[3]) / 100;
	else if (ft_strstr(s[2], "bump"))
		obj->props.bump = (float)ft_atoi(s[3]) / 100;
	else
		return (set_props_mat(s, obj));
	return (1);
}

int			set_props(char **s, t_sphere *obj)
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
	else if (ft_strstr(s[2], "rot"))
		return (change_rotation(obj, ft_atoi(s[3]) * M_PI / 180, s[2][3]));
	else if (ft_strstr(s[2], "radiance"))
		obj->props.radiance = (float)ft_atoi(s[3]) / 100;
	else
		return (set_props_2(s, obj));
	return (1);
}
