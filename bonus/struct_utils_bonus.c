/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:12:01 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:12:02 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_pos	get_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_dpos	get_dpos(double x, double y)
{
	t_dpos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_triangle	get_triangle(t_pos v1, t_pos v2, t_pos v3)
{
	t_triangle	new;

	new.v1 = v1;
	new.v2 = v2;
	new.v3 = v3;
	return (new);
}
