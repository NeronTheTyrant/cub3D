/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_handle_sprites_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:48:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:49:13 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_sprite_type(char *args, t_cub *cub)
{
	int	sp_type_nbr;

	sp_type_nbr = get_tex_nbr(args, cub->sp_type_nb);
	if (sp_type_nbr == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	if (cub->sp_type[sp_type_nbr].tex != NULL)
		return (ERR_DUP_ID);
	return (sp_type_nbr);
}

int	assign_sprite_info(char **args, t_cub *cub, int typenbr)
{
	t_sprite	temp;
	int			ret;

	if (ft_argcount(args) != 8)
		return (ERR_ARG_NB);
	ft_bzero(&temp, sizeof(t_sprite));
	ret = set_sprite(args, &temp, cub);
	if (ret != SUCCESS)
		return (ret);
	cub->sp_type[typenbr] = temp;
	return (SUCCESS);
}

int	handle_sprite_info(int fd, t_cub *cub)
{
	int		count;
	int		ret;
	int		typenbr;
	char	**args;

	count = 0;
	if (open_set(fd) < 0)
		return (setting_error(cub, NULL, ERR_SET_OPEN, cub->set_id));
	while (count < cub->sp_type_nb)
	{
		printf("count = %d\n", count);
		ret = get_next_setting(&args, fd);
		if (ret < 0)
			return (setting_error(cub, args, ret, "SPRITE INFO"));
		typenbr = check_sprite_type(args[0], cub);
		if (typenbr < 0)
			return (setting_error(cub, args, typenbr, "SPRITE INFO"));
		ret = assign_sprite_info(args, cub, typenbr);
		if (ret != 0)
			return (setting_error(cub, args, ret, "SPRITE INFO"));
		count++;
		ft_freeargs(args, ft_argcount(args));
	}
	if (close_set(fd) < 0)
		return (setting_error(cub, args, ERR_SET_CLOSE, "SPRITE INFO"));
	return (SUCCESS);
}

int	add_sprite_from_type(char **args, t_cub *cub)
{
	t_sprite	temp;
	int			typenbr;

	if (ft_argcount(args) != 4)
		return (ERR_ARG_NB);
	ft_bzero(&temp, sizeof(t_sprite));
	typenbr = get_tex_nbr(args[0], cub->sp_type_nb);
	if (typenbr < 0)
		return (typenbr);
	ft_memcpy(&temp, &cub->sp_type[typenbr], sizeof(t_sprite));
	if (ft_isfloat(args[1]) == 1 && ft_isfloat(args[2]) == 1)
		set_sprite_posxy(ft_atof(args[1]), ft_atof(args[2]), &temp);
	else
		return (ERR_BAD_ARG);
	temp.id = ++cub->sp_nb;
	if (temp.event != 0)
		temp.ev_id = ++cub->event_count;
	if (add_sprite(temp, cub) < 0)
		return (ERR_MALLOC);
	if (temp.event != 0)
	{
		if (add_event_from_sprite(cub, temp) < 0)
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	handle_sprites(int fd, t_cub *cub)
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
		ret = add_sprite_from_type(args, cub);
		if (ret < 0)
			return (setting_error(cub, args, ret, cub->set_id));
		ft_freeargs(args, ft_argcount(args));
	}
	if (ft_argcount(args) != 2)
		return (setting_error(cub, args, ERR_SET_CLOSE, cub->set_id));
	ft_freeargs(args, ft_argcount(args));
	return (1);
}
