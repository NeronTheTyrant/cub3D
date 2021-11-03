/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:41:28 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:41:30 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	add_alpha(int bg_color, int top_color)
{
	int	r;
	int	g;
	int	b;

	r = (bg_color & 0xFF0000) / 2 + (top_color & 0xFF0000) / 2;
	g = (bg_color & 0xFF00) / 2 + (top_color & 0xFF00) / 2;
	b = (bg_color & 0xFF) / 2 + (top_color & 0xFF) / 2;
	return ((r & 0xFF0000) | (g & 0xFF00) | (b & 0xFF));
}

int	add_shade(double dist, int color)
{
	int		r;
	int		g;
	int		b;
	double	ratio;

	ratio = SHADE_DIST / dist;
	if (ratio > 1.0)
		return (color);
	r = (color & 0xFF0000) * ratio;
	g = (color & 0xFF00) * ratio;
	b = (color & 0xFF) * ratio;
	return ((r & 0xFF0000) | (g & 0xFF00) | (b & 0xFF));
}
