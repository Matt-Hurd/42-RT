/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/25 19:18:23 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_screen(t_data *d)
{
	int		z;
	t_ray	r;
	float	global_matrix[4][4];
	t_vec3	point;

	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix, d->scene->cam_rot.x, d->scene->cam_rot.y,
		d->scene->cam_rot.z);
	ft_tr_translate(global_matrix, d->scene->cam_pos.x, d->scene->cam_pos.y,
		d->scene->cam_pos.z);
	z = -1;
	while (++z < d->scene->size.y * d->scene->size.x)
	{
		clear_color(&d->scene->color);
		scale_vector(1, &d->scene->cam_pos, &r.start);
		point.x = (z % d->scene->size.x) - d->scene->size.x / 2;
		point.y = (z / d->scene->size.x) - d->scene->size.y / 2;
		point.z = d->scene->fov * 10;
		ft_vec_mult_mat(&point, global_matrix, &point);
		sub_vect(&point, &r.start, &r.dir);
		normalize_vector(&r.dir);
		d->scene->coef = 1.0;
		ray_trace(d, r, 0);
		d->image[(z / d->scene->size.x)][(z % d->scene->size.x)] = d->scene->color;
	}
}

void	draw_reload(t_data *d)
{
	d->expired = 0;
	draw_screen(d);
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img =
		mlx_new_image(d->mlx, d->scene->size.x + 100, d->scene->size.y + 100);
	d->pixel_img =
		mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	post_process(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

int		expose_hook(t_data *d)
{
	if (d->img && !d->expired)
		mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	else
		draw_reload(d);
	return (0);
}

void	draw_everything(t_data *d)
{
	int y;

	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->scene->size.x,
		d->scene->size.y, d->scene->name);
	d->image = ft_memalloc(sizeof(t_rgb) * d->scene->size.y);
	y = -1;
	while (++y < d->scene->size.y)
		d->image[y] = ft_memalloc(sizeof(t_rgb) * d->scene->size.x);
	d->scene->maxdepth = (d->scene->maxdepth) ? d->scene->maxdepth : 16;
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_loop(d->mlx);
}
