/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hud_tex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:49:43 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:10:55 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	get_health_tex(t_cub *cub, t_hud *hud)
{
	if (assign_texture_from_path("./assets/hud/heart_full.xpm", cub,
			&hud->hp_full) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HFULL"));
	if (assign_texture_from_path("./assets/hud/heart_empty.xpm", cub,
			&hud->hp_empty) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HEMPTY"));
	if (assign_texture_from_path("./assets/hud/heart_half.xpm", cub,
			&hud->hp_half) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HHALF"));
	return (SUCCESS);
}

static int	get_hands_attack_tex(t_cub *cub, t_hud *hud)
{
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_0.xpm",
			cub, &hud->hands_attack[0]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_0"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_1.xpm",
			cub, &hud->hands_attack[1]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_1"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_2.xpm",
			cub, &hud->hands_attack[2]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_2"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_3.xpm",
			cub, &hud->hands_attack[3]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_3"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_4.xpm",
			cub, &hud->hands_attack[4]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_4"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_5.xpm",
			cub, &hud->hands_attack[5]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_5"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_attack_6.xpm",
			cub, &hud->hands_attack[6]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HATTACK_6"));
	return (SUCCESS);
}

static int	get_hands_tex(t_cub *cub, t_hud *hud)
{
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_idle_0.xpm",
			cub, &hud->hands_idle[0]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HIDLE_0"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_idle_1.xpm",
			cub, &hud->hands_idle[1]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HIDLE_1"));
	if (assign_texture_from_path("./assets/hud/hands/hands_fire_idle_2.xpm",
			cub, &hud->hands_idle[2]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_HIDLE_2"));
	if (get_hands_attack_tex(cub, hud) < 0)
		return (-1);
	return (SUCCESS);
}

static int	get_mace_tex(t_cub *cub, t_hud *hud)
{
	if (assign_texture_from_path("./assets/hud/mace/mace_idle.xpm", cub,
			&hud->mace_idle) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MIDLE"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_1.xpm", cub,
			&hud->mace_attack[0]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_1"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_2.xpm", cub,
			&hud->mace_attack[1]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_2"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_3.xpm", cub,
			&hud->mace_attack[2]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_3"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_4.xpm", cub,
			&hud->mace_attack[3]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_4"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_5.xpm", cub,
			&hud->mace_attack[4]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_5"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_6.xpm", cub,
			&hud->mace_attack[5]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_6"));
	if (assign_texture_from_path("./assets/hud/mace/mace_attack_7.xpm", cub,
			&hud->mace_attack[6]) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD_MATTACK_7"));
	return (SUCCESS);
}

int	get_hud_tex(t_cub *cub, t_hud *hud)
{
	if (get_health_tex(cub, hud) < 0)
		return (-1);
	if (get_hands_tex(cub, hud) < 0)
		return (-1);
	if (get_mace_tex(cub, hud) < 0)
		return (-1);
	if (assign_texture_from_path("./assets/hud/crosshair.xpm", cub,
			&hud->crosshair) < 0)
		return (cub_error(cub, ERR_BAD_ARG, "HUD CROSSHAIR"));
	return (SUCCESS);
}
