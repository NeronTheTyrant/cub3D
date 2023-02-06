/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:47:00 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 13:48:50 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_borders(t_cub *cub)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < cub->map_w)
	{
		if (ft_isin(cub->map[0][j], cub->wallc) == -1)
			return (map_error(cub, 0, j, ERR_MAP_BORDERS));
		if (ft_isin(cub->map[cub->map_h - 1][j], cub->wallc) == -1)
			return (map_error(cub, cub->map_h - 1, j, ERR_MAP_BORDERS));
		j++;
	}
	while (i < cub->map_h)
	{
		if (ft_isin(cub->map[i][0], cub->wallc) == -1)
			return (map_error(cub, 0, i, ERR_MAP_BORDERS));
		if (ft_isin(cub->map[i][cub->map_w - 1], cub->wallc) == -1)
			return (map_error(cub, cub->map_w - 1, i, ERR_MAP_BORDERS));
		i++;
	}
	return (0);
}

static int	check_space(t_cub *cub, t_pos pos)
{
	if (pos.y > 0)
	{
		if (ft_isin(cub->map[pos.y - 1][pos.x], cub->wallc) == -1)
			return (-1);
	}
	if (pos.x > 0)
	{
		if (ft_isin(cub->map[pos.y][pos.x - 1], cub->wallc) == -1)
			return (-1);
	}
	if (pos.y < cub->map_h - 1)
	{
		if (ft_isin(cub->map[pos.y + 1][pos.x], cub->wallc) == -1)
			return (-1);
	}
	if (pos.x < cub->map_w - 1)
	{
		if (ft_isin(cub->map[pos.y][pos.x + 1], cub->wallc) == -1)
			return (-1);
	}
	return (0);
}

static void	assign_player(t_cub *cub, t_pos pos, char playdir)
{
	cub->play->pos.x = (double)pos.x + 0.5;
	cub->play->pos.y = (double)pos.y + 0.5;
	if (playdir == 'N')
	{
		cub->play->dir.y = -1;
		cub->play->plane.x = 0.66;
	}
	else if (playdir == 'S')
	{
		cub->play->dir.y = 1;
		cub->play->plane.x = -0.66;
	}
	else if (playdir == 'E')
	{
		cub->play->dir.x = 1;
		cub->play->plane.y = 0.66;
	}
	else if (playdir == 'W')
	{
		cub->play->dir.x = -1;
		cub->play->plane.y = -0.66;
	}
	cub->map[pos.y][pos.x] = '0';
}

static int	check_char(t_cub *cub, t_pos pos)
{
	int			ret;

	ret = ft_isin(cub->map[pos.y][pos.x], cub->wallplayc);
	if (ret == -1)
		return (map_error(cub, pos.y, pos.x, ERR_MAP_INVALID));
	if (ret == 0)
		if (check_space(cub, pos) == -1)
			return (map_error(cub, pos.y, pos.x, ERR_MAP_OPEN));
	if (ret >= 1 && ret <= 4)
	{
		cub->play->flag++;
		if (cub->play->flag > 1)
			return (map_error(cub, pos.y, pos.x, ERR_MAP_PLAYERS));
		assign_player(cub, pos, cub->map[pos.y][pos.x]);
	}
	if (pos.x == cub->map_w - 1 && pos.y == cub->map_h - 1
		&& cub->play->flag == 0)
		return (map_error(cub, 0, 0, ERR_MAP_NOPLAYER));
	return (0);
}

int	check_map(t_cub *cub)
{
	t_pos	pos;
	int		ret;

	pos.y = 0;
	ret = check_borders(cub);
	if (ret == -1)
		return (-1);
	while (pos.y < cub->map_h)
	{
		pos.x = 0;
		while (pos.x < cub->map_w)
		{
			if (check_char(cub, pos) == -1)
				return (-1);
			pos.x++;
		}
		pos.y++;
	}
	return (0);
}
