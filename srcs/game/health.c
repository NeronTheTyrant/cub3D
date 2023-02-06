/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:15:19 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_health(t_cub *cub, int health)
{
	cub->play->health = ft_islower(cub->play->health + health,
			cub->play->maxhealth);
}

void	remove_health(t_cub *cub, int damage)
{
	cub->play->health = ft_ishigher(0, cub->play->health - damage);
}
