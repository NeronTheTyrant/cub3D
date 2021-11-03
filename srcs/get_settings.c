/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:01:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:32:32 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_texture(char **args, t_set_id set_id, t_cub *cub)
{
	int		fd;
	t_img	txt;

	fd = 0;
	if (ft_argcount(args) != 3)
		return (ARG_NB);
	txt.img = mlx_xpm_file_to_image(cub->mlx, args[1], &txt.width, &txt.height);
	if (txt.img == NULL)
		return (BAD_ARG);
	txt.addr = mlx_get_data_addr(txt.img, &txt.bpp, &txt.linelen, &txt.endi);
	if (set_id == NORTH)
		cub->set.txnorth = txt;
	else if (set_id == SOUTH)
		cub->set.txsouth = txt;
	else if (set_id == EAST)
		cub->set.txeast = txt;
	else if (set_id == WEST)
		cub->set.txwest = txt;
	else if (set_id == SPRITE)
		cub->set.txsprite = txt;
	close(fd);
	return (SUCCESS);
}

int	get_resolution(char **args, t_cub *cub)
{
	t_pos	screen;

	if (ft_argcount(args) != 4)
		return (ARG_NB);
	if (ft_argcheck_each(&args[1], &ft_isdigit) == 0)
		return (BAD_ARG);
	cub->set.resx = ft_atoi(args[1]);
	cub->set.resy = ft_atoi(args[2]);
	if (cub->set.resx <= 0 || cub->set.resy <= 0)
		return (BAD_ARG);
	mlx_get_screen_size(cub->mlx, &screen.x, &screen.y);
	cub->set.resx = ft_islower(screen.x, cub->set.resx);
	cub->set.resy = ft_islower(screen.y, cub->set.resy);
	return (SUCCESS);
}

int	get_rgb(char **args, t_set_id set_id, t_cub *cub)
{
	int		rgb;
	char	*temp;

	rgb = 0;
	if (ft_argcount(args) != 3)
		return (ARG_NB);
	temp = args[1];
	while (temp)
	{
		temp = ft_strchr(temp, ',');
		if (temp && *(++temp) == ',')
			return (BAD_ARG);
	}
	rgb = str_to_rgb(args[1]);
	if (rgb == -1)
		return (BAD_ARG);
	if (set_id == FLOOR)
		cub->set.f_rgb = rgb;
	else if (set_id == CEILING)
		cub->set.c_rgb = rgb;
	return (SUCCESS);
}

int	handle_setting(char **args, t_set_id set_id, t_cub *cub)
{
	int	err;

	if (set_id >= NORTH && set_id <= SPRITE)
		err = get_texture(args, set_id, cub);
	else if (set_id == RES)
		err = get_resolution(args, cub);
	else if (set_id == FLOOR || set_id == CEILING)
		err = get_rgb(args, set_id, cub);
	else
		err = -1;
	return (err);
}

int	get_settings(char *line, int *check, t_cub *cub)
{
	char		**args;
	t_set_id	set_id;
	int			err;

	err = 0;
	args = ft_split(line, ' ');
	if (args == NULL)
		return (setting_error(NULL, 0, -1));
	if (args[0] == NULL)
	{
		ft_freeargs(args, 0);
		return (SKIP);
	}
	set_id = get_id(args[0]);
	if (set_id != WRONG_ID && check[set_id] == 1)
		set_id = DUP_ID;
	err = handle_setting(args, set_id, cub);
	if (err != SUCCESS || set_id < 0)
		return (setting_error(args, set_id, err));
	ft_freeargs(args, ft_argcount(args));
	return (set_id);
}
