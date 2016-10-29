/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/29 06:50:39 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ssaa2(t_args *a, t_vec3 point, t_recurse *rec, int depth, t_rgb colors[4])
{
	int		x;
	int		y;
	float	diff;
	t_rgb	avg;
	t_vec3	new;

	y = -1;
	diff = 0;
	clear_color(&avg);
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			diff += fabs(colors[x].r - colors[y].r);
			diff += fabs(colors[x].g - colors[y].g);
			diff += fabs(colors[x].b - colors[y].r);
		}
		avg.r += colors[y].r;
		avg.g += colors[y].g;
		avg.b += colors[y].b;
	}
	if (depth < 2 && diff >= 1)
	{
		clear_color(&avg);
		x = -1;
		while (++x < 4)
		{
			new = point;
			new.x += 1.0 / pow(2, depth + 1) * ((x % 2) ? -1 : 1);
			new.y += 1.0 / pow(2, depth + 1) * ((x / 2) ? 1 : -1);
			ssaa(a, new, rec, depth + 1);
			avg.r += rec->color.r;
			avg.g += rec->color.g;
			avg.b += rec->color.b;
		}
	}
	avg.r /= 4;
	avg.g /= 4;
	avg.b /= 4;
	rec->color = avg;
}

void	ssaa(t_args *a, t_vec3 point, t_recurse *rec, int depth)
{
	t_ray	r;
	t_rgb	colors[4];
	t_vec3	new;
	int		x;

	x = -1;
	while (++x < 4)
	{
		clear_color(&rec->color);
		new = point;
		new.x += 1.0 / pow(2, depth) * ((x % 2) ? -1 : 1);
		new.y += 1.0 / pow(2, depth) * ((x / 2) ? 1 : -1);
		scale_vector(1, &a->d->s->cam_pos, &r.start);
		ft_vec_mult_mat(&new, a->global, &new);
		sub_vect(&new, &r.start, &r.dir);
		normalize_vector(&r.dir);
		rec->coef = 1.0;
		rec->r = r;
		rec->depth = 0;
		ray_trace(a->d, rec);
		colors[x] = rec->color;
	}
	ssaa2(a, point, rec, depth, colors);
}

void	regular_pixel(t_args *a, t_vec3 point, t_recurse *rec)
{
	t_ray		r;

	scale_vector(1, &a->d->s->cam_pos, &r.start);
	ft_vec_mult_mat(&point, a->global, &point);
	sub_vect(&point, &r.start, &r.dir);
	normalize_vector(&r.dir);
	rec->coef = 1.0;
	rec->r = r;
	rec->depth = 0;
	ray_trace(a->d, rec);
}

void	*do_recurse(void *args)
{
	int			z;
	t_recurse	*rec;
	t_vec3		point;
	t_args		*a;

	a = (t_args *)args;
	rec = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	z = a->d->s->size.x * a->start.y + a->start.x;
	while (++z < a->d->s->size.x * a->end.y + a->end.x)
	{
		clear_color(&rec->color);
		point.x = (z % a->d->s->size.x) - a->d->s->size.x / 2;
		point.y = (z / a->d->s->size.x) - a->d->s->size.y / 2;
		point.z = a->d->s->fov * 10;
		if (a->d->s->aa == 2)
			ssaa(a, point, rec, 1);
		else
			regular_pixel(a, point, rec);
		a->d->image[(z / a->d->s->size.x)][(z % a->d->s->size.x)] = rec->color;
	}
	free(args);
	return (NULL);
}

void	draw_screen(t_data *d)
{
	int		x;
	int		z;
	t_args	*a;

	x = -1;
	while (++x < 16)
	{
		a = (t_args *)ft_memalloc(sizeof(t_args));
		ft_make_identity_matrix(a->global);
		ft_tr_rotate(a->global, d->s->cam_rot.x, d->s->cam_rot.y,
			d->s->cam_rot.z);
		ft_tr_translate(a->global, d->s->cam_pos.x, d->s->cam_pos.y,
			d->s->cam_pos.z);
		z = d->s->size.x * d->s->size.y / 16;
		a->d = d;
		a->start.x = (x * z) % d->s->size.x - 1;
		a->start.y = (x * z) / d->s->size.x;
		a->end.x = ((x + 1) * z) % d->s->size.x;
		a->end.y = ((x + 1) * z) / d->s->size.x;
		if (pthread_create(&d->render_threads[x], NULL, do_recurse, a))
			ft_error("ERROR! Unable to create render thread.");
	}
}

void	draw_reload(t_data *d)
{
	int x;

	if (d->drawing)
		return ;
	d->drawing = 1;
	d->expired = 0;
	draw_screen(d);
	x = -1;
	while (++x < 16)
		pthread_join(d->render_threads[x], NULL);
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img =
		mlx_new_image(d->mlx, d->s->size.x + 100, d->s->size.y + 100);
	d->pixel_img =
		mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	post_process(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->drawing = 0;
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
	d->win = mlx_new_window(d->mlx, d->s->size.x,
		d->s->size.y, d->s->name);
	d->image = ft_memalloc(sizeof(t_rgb) * d->s->size.y);
	y = -1;
	while (++y < d->s->size.y)
		d->image[y] = ft_memalloc(sizeof(t_rgb) * d->s->size.x);
	d->s->maxdepth = (d->s->maxdepth) ? d->s->maxdepth : 16;
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_loop(d->mlx);
}
