/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/25 19:47:26 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		display_help();
		draw_everything(data);
	}
	else
		display_usage(av[0]);
	return (0);
}
