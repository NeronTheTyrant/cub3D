/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_handle_teleporters_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:49:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:49:41 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	get_teleporter_info(t_cub *cub, char **args, t_sprite *temp_sprite,
		t_dpos *tp)
{
	if (ft_isfloat(args[1]) == 1 && ft_isfloat(args[2]) == 1)
		set_sprite_posxy(ft_atof(args[1]), ft_atof(args[2]), temp_sprite);
	else
		return (ERR_BAD_ARG);
	(*temp_sprite).id = ++cub->sp_nb;
	(*temp_sprite).ev_id = ++cub->event_count;
	if (ft_isfloat(args[3]) == 1 && ft_isfloat(args[4]) == 1)
	{
		(*tp).x = ft_atof(args[3]);
		(*tp).y = ft_atof(args[4]);
	}
	else
		return (ERR_BAD_ARG);
	return (0);
}

int	add_teleporter(char **args, t_cub *cub)
{
	t_sprite	temp;
	t_dpos		tp;
	int			ret;
	int			typenbr;

	if (ft_argcount(args) != 6)
		return (ERR_ARG_NB);
	ft_bzero(&temp, sizeof(t_sprite));
	typenbr = get_tex_nbr(args[0], cub->sp_type_nb);
	if (typenbr < 0)
		return (typenbr);
	ft_memcpy(&temp, &cub->sp_type[typenbr], sizeof(t_sprite));
	if (get_teleporter_info(cub, args, &temp, &tp) != SUCCESS)
		return (ERR_BAD_ARG);
	ret = add_sprite(temp, cub);
	if (ret < 0)
		return (ret);
	ret = add_event_teleport(cub, temp, tp);
	if (ret < 0)
		return (ret);
	return (SUCCESS);
}

int	handle_teleporters(int fd, t_cub *cub)
{
	int		ret;
	char	**args;

	args = NULL;
	if (open_set(fd) < 0)
		return (setting_error(cub, args, ERR_SET_OPEN, cub->set_id));
	while (1)
	{
		ret = get_next_setting(&args, fd);
		if (ret < 0)
			return (setting_error(cub, args, ret, cub->set_id));
		if (ft_strcmp(args[0], "}") == 0)
			break ;
		ret = add_teleporter(args, cub);
		if (ret < 0)
			return (setting_error(cub, args, ret, cub->set_id));
		ft_freeargs(args, ft_argcount(args));
	}
	if (ft_argcount(args) != 2)
		return (setting_error(cub, args, ERR_SET_CLOSE, cub->set_id));
	ft_freeargs(args, ft_argcount(args));
	return (SUCCESS);
}
