/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 01:22:59 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 08:21:42 by mhurd            ###   ########.fr       */
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
	free(s);
}

void	*parse_input(void *data)
{
	char *str;

	while (1)
	{
		ft_get_next_line(0, &str);
		handle_input(str, data);
	}
}

void	create_input_thread(t_data *d)
{
	d->input_thread = (pthread_t *)ft_memalloc(sizeof(pthread_t));
	if (pthread_create(d->input_thread, NULL, parse_input, d))
		ft_error("ERROR! Unable to create interpreter thread.");
}
