/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mob_ai.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:07:02 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 15:14:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_mob_ai_turret(t_mob *mob)
{
	mob->ai = AI_TURRET;
	mob->hp = 3;
	mob->hpmax = mob->hp;
	mob->speed = 0;
	mob->proj_speed = 2;
	mob->attackrange = 20;
	mob->lastattack = clock();
	mob->attackdelay = CLOCKS_PER_SEC * 1;
}

void	set_mob_ai_fighter(t_mob *mob)
{
	mob->ai = AI_FIGHTER;
	mob->hp = 5;
	mob->hpmax = mob->hp;
	mob->speed = 2.5;
	mob->proj_speed = 0;
	mob->attackrange = 1;
	mob->lastattack = clock();
	mob->attackdelay = CLOCKS_PER_SEC * 1.5;
}
