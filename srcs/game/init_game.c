#include "../include/cub3d.h"

int	set_sprite_update(t_cub *cub)
{
	t_list		*sp_lst;
	t_sprite	*sp;

	sp_lst = cub->sp;
	while (sp_lst)
	{
		sp = (t_sprite *)sp_lst->content;
		sp->last_update = cub->time;
		sp_lst = sp_lst->next;
	}
	return (0);
}

int	set_surface_tex(t_cub *cub)
{
	int			i;
	t_surface	*sf;

	i = 0;
	while (i < cub->tex_sf->texnbr && i < WALL_NBR)
	{
		sf = &cub->sf[i];
		sf->tex = &cub->tex_sf->tex[i];
		sf->last_update = cub->time;
		i++;
	}
	while (i < WALL_NBR)
	{
		sf = &cub->sf[i];
		sf->tex = &cub->tex_sf->tex[0];
		sf->last_update = cub->time;
		i++;
	}
	return (SUCCESS);
}

void	init_game_values(t_cub *cub)
{
	int	ret;

	cub->timeref = clock() + CLOCKS_PER_SEC;
	cub->time = clock();
	set_sprite_update(cub);
	set_surface_tex(cub);
	cub->play->maxhealth = 10;
	cub->play->health = 10;
	if (init_minimap(cub, cub->mini) == ERR_MINI_SMALL)
	{
		cub->mini->off = 1;
		printf("Minimap dimensions are too small, cannot be displayed\n");
	}
	ret = check_teleport_pos(cub);
	if (ret < 0)
		exit_error(cub, ret, "TP");
	ret = check_mob_pos(cub);
	if (ret < 0)
		exit_error(cub, ret, "MOB");
}

static void	init_game_hooks(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, gameloop, cub);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 1L << 17, click_cross, cub);
}

void	init_game(t_cub *cub)
{
	init_game_values(cub);
	cub->z = malloc(sizeof(*cub->z) * cub->res.x);
	if (init_hud(cub) < 0)
		exit_done(cub);
	if (cub->z == NULL)
		exit_error(cub, ERR_MALLOC, NULL);
	if (cub->save == 1)
		save_screenshot(cub);
	else
	{
		cub->win = mlx_new_window(cub->mlx, cub->res.x, cub->res.y, "cub3D");
		init_game_hooks(cub);
		mlx_loop(cub->mlx);
	}
}
