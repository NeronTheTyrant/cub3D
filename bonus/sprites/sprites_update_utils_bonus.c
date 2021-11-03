#include "../include/cub3d_bonus.h"

void	check_sprite_update(t_cub *cub, t_sprite *sp)
{
	sp->update = (cub->time - sp->last_update >= sp->tex->delay);
}

void	update_sprite_tex(t_cub *cub, t_sprite *sprite, t_img *nextframe)
{
	sprite->last_update += sprite->tex->delay;
	sprite->tex = nextframe;
	check_sprite_update(cub, sprite);
}
