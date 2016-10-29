/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 04:21:33 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/28 01:13:18 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
