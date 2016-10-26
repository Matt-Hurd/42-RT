/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 01:12:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/21 00:13:19 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	key_hook_rotation(int keycode, t_data *d)
{
	if (keycode == KEY_ROT_X_U)
		d->scene->cam_rot.x += 0.2;
	else if (keycode == KEY_ROT_X_D)
		d->scene->cam_rot.x -= 0.2;
	else if (keycode == KEY_ROT_Y_U)
		d->scene->cam_rot.y += 0.2;
	else if (keycode == KEY_ROT_Y_D)
		d->scene->cam_rot.y -= 0.2;
	else if (keycode == KEY_ROT_Z_U)
		d->scene->cam_rot.z += 0.2;
	else if (keycode == KEY_ROT_Z_D)
		d->scene->cam_rot.z -= 0.2;
	else
		return (0);
	return (1);
}

static int	key_hook_translation(int keycode, t_data *d)
{
	if (keycode == KEY_UP)
		d->scene->cam_pos.y -= 50;
	else if (keycode == KEY_DOWN)
		d->scene->cam_pos.y += 50;
	else if (keycode == KEY_LEFT)
		d->scene->cam_pos.x -= 50;
	else if (keycode == KEY_RIGHT)
		d->scene->cam_pos.x += 50;
	else
		return (0);
	return (1);
}

static int	key_hook_scale(int keycode, t_data *d)
{
	if (keycode == KEY_ZOOM_IN)
		d->scene->cam_pos.z += 50;
	else if (keycode == KEY_ZOOM_OUT)
		d->scene->cam_pos.z -= 50;
	else
		return (0);
	return (1);
}

int			key_hook(int keycode, t_data *d)
{
	int redraw;

	redraw = 0;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	redraw += key_hook_rotation(keycode, d);
	redraw += key_hook_translation(keycode, d);
	redraw += key_hook_scale(keycode, d);
	if (redraw)
		draw_reload(d);
	return (0);
}
