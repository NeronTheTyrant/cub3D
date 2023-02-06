/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings_id.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:51 by mlebard           #+#    #+#             */
/*   Updated: 2021/05/01 18:31:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_set_id	get_id_len1(char *arg)
{
	if (*arg == 'R')
		return (RES);
	return (WRONG_ID);
}

static t_set_id	get_id_len2(char *arg)
{
	if (ft_strcmp(arg, "SP") == 0)
		return (SPRITE_POS);
	if (ft_strcmp(arg, "TP") == 0)
		return (TELEPORTERS);
	return (WRONG_ID);
}

static t_set_id	get_id_len4(char *arg)
{
	if (ft_strcmp(arg, "MINI") == 0)
		return (MINIMAP);
	else if (ft_strcmp(arg, "NEXT") == 0)
		return (NEXT_LEVEL);
	else
		return (WRONG_ID);
}

static t_set_id	get_id_len3(char *arg)
{
	if (ft_strcmp(arg, "MOB") == 0)
		return (MOBS);
	else
		return (WRONG_ID);
}

t_set_id	get_id(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len == 4)
		return (get_id_len4(arg));
	if (len == 3)
		return (get_id_len3(arg));
	if (len == 2)
		return (get_id_len2(arg));
	else if (len == 1)
		return (get_id_len1(arg));
	else
		return (WRONG_ID);
}
