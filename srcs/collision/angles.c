/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:17:17 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 15:17:19 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_angle_from_pos(t_dpos origin, t_dpos target)
{
	double	angle;

	angle = atan2(origin.y - target.y, target.x - origin.x) * (180 / M_PI);
	if (angle < 0)
		angle += 360.0;
	angle = angle_atan_to_angle_cardinal(angle);
	return (angle);
}

double	angle_atan_to_angle_cardinal(double angle)
{
	if (angle <= 90.0)
	{
		return (90.0 - angle);
	}
	else if (angle <= 180.0)
	{
		return (270.0 + 180.0 - angle);
	}
	else if (angle <= 270.0)
	{
		return (180.0 + 270.0 - angle);
	}
	else
		return (90.0 + 360.0 - angle);
}

int	angle_diff(t_vect reference, t_vect target, double threshold)
{
	if (fabs(reference.x - target.x) > threshold)
		return (0);
	if (fabs(reference.y - target.y) > threshold)
		return (0);
	return (1);
}
