/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:25:37 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:32:54 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_set_id	get_id_len1(char *arg)
{
	if (*arg == 'S')
		return (SPRITE);
	if (*arg == 'R')
		return (RES);
	if (*arg == 'F')
		return (FLOOR);
	if (*arg == 'C')
		return (CEILING);
	return (WRONG_ID);
}

static t_set_id	get_id_len2(char *arg)
{
	if (ft_strcmp(arg, "NO") == 0)
		return (NORTH);
	if (ft_strcmp(arg, "SO") == 0)
		return (SOUTH);
	if (ft_strcmp(arg, "EA") == 0)
		return (EAST);
	if (ft_strcmp(arg, "WE") == 0)
		return (WEST);
	return (WRONG_ID);
}

t_set_id	get_id(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len == 2)
	{
		return (get_id_len2(arg));
	}
	else if (len == 1)
	{
		return (get_id_len1(arg));
	}
	else
		return (WRONG_ID);
}
