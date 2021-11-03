/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:54:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/02/27 11:48:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_cub *cub, double speed)
{
	double	nexty;
	double	nextx;

	nexty = cub->play.y + cub->dir.y * speed;
	nextx = cub->play.x + cub->dir.x * speed;
	if (ft_isin(cub->map[(int)(nexty)][(int)(cub->play.x)], "12 ") == -1)
		cub->play.y = nexty;
	if (ft_isin(cub->map[(int)(cub->play.y)][(int)(nextx)], "12 ") == -1)
		cub->play.x = nextx;
}

void	move_backwards(t_cub *cub, double speed)
{
	double	nexty;
	double	nextx;

	nexty = cub->play.y - cub->dir.y * speed;
	nextx = cub->play.x - cub->dir.x * speed;
	if (ft_isin(cub->map[(int)(nexty)][(int)(cub->play.x)], "12 ") == -1)
		cub->play.y = nexty;
	if (ft_isin(cub->map[(int)(cub->play.y)][(int)(nextx)], "12 ") == -1)
		cub->play.x = nextx;
}

void	strafe_left(t_cub *cub, double speed)
{
	double	nexty;
	double	nextx;

	nexty = cub->play.y - cub->plane.y * speed;
	nextx = cub->play.x - cub->plane.x * speed;
	if (ft_isin(cub->map[(int)(nexty)][(int)(cub->play.x)], "12 ") == -1)
		cub->play.y = nexty;
	if (ft_isin(cub->map[(int)(cub->play.y)][(int)(nextx)], "12 ") == -1)
		cub->play.x = nextx;
}

void	strafe_right(t_cub *cub, double speed)
{
	double	nexty;
	double	nextx;

	nexty = cub->play.y + cub->plane.y * speed;
	nextx = cub->play.x + cub->plane.x * speed;
	if (ft_isin(cub->map[(int)(nexty)][(int)(cub->play.x)], "12 ") == -1)
		cub->play.y = nexty;
	if (ft_isin(cub->map[(int)(cub->play.y)][(int)(nextx)], "12 ") == -1)
		cub->play.x = nextx;
}
