/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelcont.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 04:55:43 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/25 19:37:50 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelcont(t_list **alst, void *cont)
{
	t_list	*prev;
	t_list	*current;

	if (!alst || !*alst)
		return ;
	prev = *alst;
	if (prev->content == cont)
	{
		*alst = prev->next;
		return ;
	}
	current = prev->next;
	while (current)
	{
		if (current->content == cont)
		{
			prev->next = current->next;
			free(current);
			free(cont);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
