/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:16:06 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:17:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map_id(char **args, t_cub *cub, int map_id)
{
	if (map_id == ID_MAP)
	{
		if (ft_strcmp(args[0], "MAP") != 0)
			return (ERR_WRONG_ID);
		if (ft_argcount(args) != 3)
			return (ERR_ARG_NB);
		if (ft_strcheck_each(args[1], &ft_isdigit) == 0)
			return (ERR_BAD_ARG);
		cub->map_h = ft_atoi(args[1]);
		if (cub->map_h <= 0)
			return (ERR_BAD_ARG);
	}
	else
	{
		if (map_id == ID_MAPF && ft_strcmp(args[0], "MAPF") != 0)
			return (ERR_WRONG_ID);
		else if (map_id == ID_MAPC && ft_strcmp(args[0], "MAPC") != 0)
			return (ERR_WRONG_ID);
		if (ft_argcount(args) != 2)
			return (ERR_ARG_NB);
	}
	return (0);
}
