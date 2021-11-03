/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:51:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:26:46 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	raycasting(t_cub *cub, t_img *frame)
{
	init_skybox(cub, cub->sky, cub->play);
	wallcasting(cub, cub->ray, frame);
	spritecasting(cub, cub->sprite, frame);
	return (0);
}
