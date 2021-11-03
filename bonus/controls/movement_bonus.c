/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:51:02 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/24 17:54:55 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	check_next_move(t_cub *cub, double *nextx, double *nexty)
{
	if (*nextx < 0)
		*nextx = 0;
	else if (*nextx > (float)(cub->map_w - 1))
		*nextx = cub->map_w - 1;
	if (*nexty < 0)
		*nexty = 0;
	else if (*nexty > (float)(cub->map_h - 1))
		*nexty = cub->map_h - 1;
}

int	move_forward(t_cub *cub, t_dpos *pos, t_vect dir, double speed)
{
	int			stopflag;
	double		nexty;
	double		nextx;

	nexty = pos->y + dir.y * speed;
	nextx = pos->x + dir.x * speed;
	check_next_move(cub, &nextx, &nexty);
	stopflag = 0;
	if (ft_isin(cub->map[(int)(nexty)][(int)(pos->x)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(pos->x, nexty), -1) == 0)
		pos->y = nexty;
	else
		stopflag = 1;
	if (ft_isin(cub->map[(int)(pos->y)][(int)(nextx)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(nextx, pos->y), -1) == 0)
		pos->x = nextx;
	else
		stopflag = 1;
	if (stopflag == 1)
		return (-1);
	return (0);
}

int	move_backwards(t_cub *cub, t_dpos *pos, t_vect dir, double speed)
{
	int			stopflag;
	double		nexty;
	double		nextx;

	nexty = pos->y - dir.y * speed;
	nextx = pos->x - dir.x * speed;
	check_next_move(cub, &nextx, &nexty);
	if (ft_isin(cub->map[(int)(nexty)][(int)(pos->x)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(pos->x, nexty), -1) == 0)
		pos->y = nexty;
	else
		stopflag = 1;
	if (ft_isin(cub->map[(int)(pos->y)][(int)(nextx)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(nextx, pos->y), -1) == 0)
		pos->x = nextx;
	else
		stopflag = 1;
	if (stopflag == 1)
		return (-1);
	return (0);
}

int	strafe_left(t_cub *cub, t_dpos *pos, t_vect plane, double speed)
{
	int			stopflag;
	double		nexty;
	double		nextx;

	nexty = pos->y - plane.y * speed;
	nextx = pos->x - plane.x * speed;
	check_next_move(cub, &nextx, &nexty);
	if (ft_isin(cub->map[(int)(nexty)][(int)(pos->x)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(pos->x, nexty), -1) == 0)
		pos->y = nexty;
	else
		stopflag = 1;
	if (ft_isin(cub->map[(int)(pos->y)][(int)(nextx)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(nextx, pos->y), -1) == 0)
		pos->x = nextx;
	else
		stopflag = 1;
	if (stopflag == 1)
		return (-1);
	return (0);
}

int	strafe_right(t_cub *cub, t_dpos *pos, t_vect plane, double speed)
{
	int			stopflag;
	double		nexty;
	double		nextx;

	nexty = pos->y + plane.y * speed;
	nextx = pos->x + plane.x * speed;
	check_next_move(cub, &nextx, &nexty);
	if (ft_isin(cub->map[(int)(nexty)][(int)(pos->x)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(pos->x, nexty), -1) == 0)
		pos->y = nexty;
	else
		stopflag = 1;
	if (ft_isin(cub->map[(int)(pos->y)][(int)(nextx)], cub->wallc) == -1 &&
			check_sprite_collision(cub, get_dpos(nextx, pos->y), -1) == 0)
		pos->x = nextx;
	else
		stopflag = 1;
	if (stopflag == 1)
		return (-1);
	return (0);
}
