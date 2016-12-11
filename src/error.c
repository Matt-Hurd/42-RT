/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 04:21:33 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 08:14:33 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	validate_scene(t_data *d)
{
	if (!d || !d->s || !d->s->fov || d->s->size.x <= 0
			|| d->s->size.y <= 0 || !d->s->name)
		ft_error("Invalid config");
}

void	ft_exit(void)
{
	exit(1);
}

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	ft_exit();
}

void	ft_error_unknown(void)
{
	ft_putstr("Error: ");
	ft_error(strerror(errno));
}
