/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:25:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:02:33 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_borders(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < cub->map_w)
	{
		if (ft_isin(cub->map[0][j], " 1") == -1)
			return (map_error(cub, 0, j, 0));
		if (ft_isin(cub->map[cub->map_h - 1][j], " 1") == -1)
			return (map_error(cub, cub->map_h - 1, j, 0));
		j++;
	}
	while (i < cub->map_h)
	{
		if (ft_isin(cub->map[i][0], " 1") == -1)
			return (map_error(cub, i, 0, 0));
		if (ft_isin(cub->map[i][cub->map_w - 1], " 1") == -1)
			return (map_error(cub, i, cub->map_w - 1, 0));
		i++;
	}
	return (0);
}

static int	check_space(t_cub *cub, t_pos pos)
{
	if (pos.y > 0)
	{
		if (ft_isin(cub->map[pos.y - 1][pos.x], " 1") == -1)
			return (-1);
	}
	if (pos.x > 0)
	{
		if (ft_isin(cub->map[pos.y][pos.x - 1], " 1") == -1)
			return (-1);
	}
	if (pos.y < cub->map_h - 1)
	{
		if (ft_isin(cub->map[pos.y + 1][pos.x], " 1") == -1)
			return (-1);
	}
	if (pos.x < cub->map_w - 1)
	{
		if (ft_isin(cub->map[pos.y][pos.x + 1], " 1") == -1)
			return (-1);
	}
	return (0);
}

static int	check_char(t_cub *cub, t_pos pos)
{
	static int	player = 0;
	int			ret;

	ret = ft_isin(cub->map[pos.y][pos.x], "012 NSWE");
	if (ret == -1)
		return (map_error(cub, pos.y, pos.x, 1));
	if (ret == 2)
		if (add_sprite(cub, pos) == -1)
			return (setting_error(NULL, 0, -1));
	if (ret == 3)
		if (check_space(cub, pos) == -1)
			return (map_error(cub, pos.y, pos.x, 2));
	if (ret >= 4)
	{
		player++;
		if (player > 1)
			return (map_error(cub, pos.y, pos.x, 3));
		cub->play.x = pos.x;
		cub->play.y = pos.y;
	}
	if (pos.x == cub->map_w - 1 && pos.y == cub->map_h - 1 && player == 0)
		return (map_error(cub, 0, 0, 4));
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
