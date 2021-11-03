/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:41 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:11:21 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	handle_setting(char **args, int fd, t_set_id set_id, t_cub *cub)
{
	int	err;

	err = 0;
	if (set_id == RES)
		err = handle_resolution(args, cub);
	else if (set_id == SPRITE_POS)
		err = handle_sprites(fd, cub);
	else if (set_id == TELEPORTERS)
		err = handle_teleporters(fd, cub);
	else if (set_id == MINIMAP)
		err = handle_minimap(args, cub);
	else if (set_id == MOBS)
		err = handle_mobs(fd, cub);
	else if (set_id == NEXT_LEVEL)
		err = handle_next_level(args, cub);
	if (err == -1 && (set_id == SPRITE_POS || set_id == TELEPORTERS
			|| set_id == MOBS))
		ft_freeargs(args, ft_argcount(args));
	return (err);
}

int	get_settings(char **args, int fd, int *check, t_cub *cub)
{
	t_set_id	set_id;
	int			err;

	err = 0;
	ft_strlcpy(cub->set_id, args[0], 3);
	set_id = get_id(args[0]);
	if (set_id != WRONG_ID && check[set_id] == 1)
		set_id = DUP_ID;
	if (set_id >= 0)
		err = handle_setting(args, fd, set_id, cub);
	if (set_id == WRONG_ID)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	else if (set_id == DUP_ID)
		return (setting_error(cub, args, ERR_DUP_ID, args[0]));
	else if (err != -1)
	{
		check[set_id] = 1;
		ft_freeargs(args, ft_argcount(args));
	}
	return (err);
}
