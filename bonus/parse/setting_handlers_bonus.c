/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_handlers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:21:40 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:47:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	handle_resolution(char **args, t_cub *cub)
{
	t_pos	screen;

	if (cub->res.x != 0 && cub->res.y != 0)
		return (SUCCESS);
	if (ft_argcount(args) != 4)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (ft_argcheck_each(&args[1], &ft_isdigit) == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	cub->res.x = ft_atoi(args[1]);
	cub->res.y = ft_atoi(args[2]);
	if (cub->res.x <= 0 || cub->res.y <= 0)
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	if (cub->save != 1)
	{
		mlx_get_screen_size(cub->mlx, &screen.x, &screen.y);
		cub->res.x = ft_islower(screen.x, cub->res.x);
		cub->res.y = ft_islower(screen.y, cub->res.y);
	}
	return (SUCCESS);
}

int	handle_skybox(char **args, t_cub *cub)
{
	int	ret;

	if (ft_strcmp(args[0], "SB") != 0)
		return (ERR_WRONG_ID);
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	ret = assign_texture(args, cub, &cub->tex_sky);
	if (ret != 0)
		return (setting_error(cub, args, ret, args[0]));
	return (SUCCESS);
}

int	assign_rgb(char *rgb_str, int *dest)
{
	int		rgb;
	char	*temp;

	rgb = 0;
	temp = rgb_str;
	while (temp)
	{
		temp = ft_strchr(temp, ',');
		if (temp && *(++temp) == ',')
			return (ERR_BAD_ARG);
	}
	rgb = str_to_rgb(rgb_str);
	if (rgb == -1)
		return (ERR_BAD_ARG);
	*dest = rgb;
	return (SUCCESS);
}

int	handle_minimap(char **args, t_cub *cub)
{
	if (ft_argcount(args) != 8)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (ft_strcheck_each(args[1], &ft_isdigit) && ft_strcheck_each(args[2],
			&ft_isdigit) && ft_strcheck_each(args[3], &ft_isdigit))
	{
		cub->mini->ratio.x = ft_atoi(args[1]);
		cub->mini->ratio.y = ft_atoi(args[2]);
		cub->mini->tilesize = ft_atoi(args[3]);
	}
	else
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	if (cub->mini->ratio.x <= 0 || cub->mini->ratio.y <= 0
		|| cub->mini->tilesize <= 0)
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	if (assign_rgb(args[4], &cub->mini->wall_color) != SUCCESS)
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	if (assign_rgb(args[5], &cub->mini->floor_color) != SUCCESS)
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	if (assign_rgb(args[6], &cub->mini->player_color) != SUCCESS)
		return (setting_error(cub, args, ERR_BAD_ARG, args[0]));
	return (SUCCESS);
}

int	handle_next_level(char **args, t_cub *cub)
{
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (ft_strcmp(args[1], "NONE") == 0)
	{
		cub->nextmap = NULL;
		return (SUCCESS);
	}
	if (check_file_extension(args[1], ".cub") == 0)
		return (setting_error(cub, args, ERR_FILE_EXTENSION, args[1]));
	if (filecheck(args[1]) == -1)
		return (setting_error(cub, args, ERR_NOT_FILE, args[1]));
	cub->nextmap = ft_strdup(args[1]);
	return (SUCCESS);
}
