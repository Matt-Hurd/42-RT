/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 15:40:25 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include <stdio.h>

void	display_usage(char *av)
{
	ft_putstr("usage: ");
	ft_putstr(av);
	ft_putendl(" input_file");
}

int		main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = (t_data *)ft_memalloc(sizeof(t_data));
		if (!data)
			ft_error("Malloc Error");
		parse_file(data, av[1]);
		draw_everything(data);
	}
	else
		display_usage(av[0]);
	return (0);
}
