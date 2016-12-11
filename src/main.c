/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 08:43:36 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	list_bonuses(void)
{
	ft_putendl("Bonus Features:\n\
	INI File Input\n\
	Keyboard Input\n\
	Live CLI\n\
		Adding/Removing Objects\n\
		Modifying Objects\n\
		Printing Debug Info\n\
	Reflections\n\
		Lambertion Shading\n\
		Blinn-Phong Shading\n\
	Refractions\n\
		Density\n\
	Transparency\n\
	Anti-Aliasing\n\
	Supersampling\n\
	Perlin Noise\n\
		Marble Material\n\
		Bump Mapping\n\
	Triangle Intersections\n\
	Model Input");
}

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
		create_input_thread(data);
		list_bonuses();
		display_help();
		draw_everything(data);
	}
	else
		display_usage(av[0]);
	return (0);
}
