/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 01:22:59 by mhurd             #+#    #+#             */
/*   Updated: 2017/03/05 14:29:42 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	handle_input(char *s, t_data *d)
{
	char	**split;
	int		count;

	split = ft_strsplit(s, ' ');
	count = ft_count_words(s, ' ');
	if (parse_misc(split, count, d))
		d->expired = 1;
	else if (modify_object(split, count, d))
		d->expired = 1;
	else if (count >= 2 && add_object(split, d))
		d->expired = 1;
	else if (count >= 2 && del_object(split, d))
		d->expired = 1;
	ft_free_strsplit(s, split, ' ');
}

void	*parse_input(void *data)
{
	char	*str;
	char	**strs;
	int		x;

	while (1)
	{
		ft_get_next_line(0, &str);
		strs = ft_strsplit(str, ';');
		x = -1;
		while (++x < ft_count_words(str, ';'))
			handle_input(strs[x], data);
		ft_free_strsplit(str, strs, ';');
	}
}

void	create_input_thread(t_data *d)
{
	d->input_thread = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	if (pthread_create(d->input_thread, NULL, parse_input, d))
		ft_error("ERROR! Unable to create interpreter thread.");
}
