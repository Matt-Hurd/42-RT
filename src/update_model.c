/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 03:35:38 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/19 04:28:15 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	update_model(t_model *m)
{
	float		global_matrix[4][4];
	int			x;

	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix,
		m->props.rot.x,
		m->props.rot.y,
		m->props.rot.z);
	x = -1;
	while (++x < m->vnc)
	{
		ft_vec_mult_mat(&m->normals_origin[x], global_matrix, &m->normals[x]);
		normalize_vector(&m->normals[x]);
	}
	ft_tr_scale(global_matrix,
		m->scale,
		m->scale,
		m->scale);
	ft_tr_translate(global_matrix,
		m->props.pos.x,
		m->props.pos.y,
		m->props.pos.z);
	x = -1;
	while (++x < m->vc)
		ft_vec_mult_mat(&m->vertices_origin[x], global_matrix, &m->vertices[x]);
}
