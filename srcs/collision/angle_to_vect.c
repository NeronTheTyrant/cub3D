/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_to_vect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:16:12 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static double	get_y_vector(double angle)
{
	double	temp;

	if (angle < 180.0)
		temp = angle + 90.0;
	else
		temp = angle - 90.0;
	temp = (180.0 - temp) / 90.0;
	if (angle < 180.0)
		temp *= -1;
	return (temp);
}

static double	get_x_vector(double angle)
{
	double	temp;

	temp = 180.0 - angle;
	temp /= 90;
	if (angle < 90)
		temp = 2.0 - temp;
	else if (angle > 270)
		temp = -2.0 - temp;
	return (temp);
}

t_vect	angle_to_vect(double angle)
{
	t_vect	vect;

	vect.x = get_x_vector(angle);
	vect.y = get_y_vector(angle);
	return (vect);
}
