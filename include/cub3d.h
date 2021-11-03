/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:07:04 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:15:06 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <stdio.h>
# include "../mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

/*
** Setting Return Defines
*/

# define SUCCESS		0
# define ARG_NB			1
# define BAD_ARG		2
# define MALLOC_ERR		-1
# define SKIP			-2

/*
** Key Flag Defines
*/

# define KEY_W			0x1
# define KEY_A			0x2
# define KEY_S			0x4
# define KEY_D			0x8
# define KEY_RG_ARR		0x10
# define KEY_LF_ARR		0x20
# define KEY_SHIFT		0x40

typedef struct s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct s_posmax
{
	intmax_t	x;
	intmax_t	y;
}				t_posmax;

typedef struct s_dpos
{
	double	x;
	double	y;
}				t_dpos;

typedef struct a_vect
{
	double	x;
	double	y;
}				t_vect;

typedef struct s_triangle
{
	t_pos	v1;
	t_pos	v2;
	t_pos	v3;
}				t_triangle;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		order;
	double	dist;
}				t_sprite;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			height;
	int			width;
	int			endi;
}				t_img;

typedef struct s_raycasting
{
	t_vect	ray;
	t_pos	pos;
	t_dpos	delt;
	t_dpos	dist;
	t_pos	step;
	int		side;
	double	perp_dist;
	double	hit;
}				t_raycasting;

typedef struct s_spritecasting
{
	t_dpos		transform;
	int			screenx;
	int			height;
	int			width;
	int			top;
	int			bot;
	int			left;
	int			right;
	int			stripe;
	t_posmax	texel;
}				t_spritecasting;

typedef struct s_wall
{
	int			height;
	int			top;
	int			bot;
	double		hit;
	t_posmax	texel;
	double		step;
	double		texpos;
}				t_wall;

typedef struct s_settings
{
	int			resx;
	int			resy;
	t_img		txnorth;
	t_img		txsouth;
	t_img		txeast;
	t_img		txwest;
	t_img		txsprite;
	int			f_rgb;
	int			c_rgb;
}				t_settings;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_settings	set;
	t_dpos		play;
	char		**map;
	int			map_w;
	int			map_h;
	t_img		mini;
	t_vect		dir;
	t_vect		plane;
	int			sp_nb;
	t_sprite	*sp;
	double		*z;
	uint32_t	keys;
	int			minimap;
	int			save;
}				t_cub;

typedef enum e_set_id
{
	DUP_ID = -2,
	WRONG_ID,
	RES,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	SPRITE,
	FLOOR,
	CEILING
}				t_set_id;

/*
** Struct Utils
*/

t_pos			get_pos(int x, int y);
t_triangle		get_triangle(t_pos v1, t_pos v2, t_pos v3);

/*
** Parse Manager
*/

int				parse_cub(t_file map, t_cub *cub);

/*
** Parser: Settings
*/

t_set_id		get_id(char *arg);
int				get_settings(char *line, int *check, t_cub *cub);

/*
** Parser: Map
*/

int				parse_map(t_file mapfile, int linecount, t_cub *cub);
int				check_map(t_cub *cub);
int				add_sprite(t_cub *cub, t_pos pos);

/*
** Minilibx Utils
*/

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_img			make_img(void*mlx, int x, int y);
void			fill_img(int limitx, int limity, t_img *img, int color);
void			draw_circle(t_pos pos, int r, int color, t_img *img);
void			horline(int hor, t_pos coord, int color, t_img *img);
void			vertline(int vert, t_pos coord, int color, t_img *img);
void			draw_line(t_pos v1, t_pos v2, int color, t_img *img);
void			draw_triangle(t_triangle tri, int color, t_img *minimap);

/*
** Minimap
*/

int				make_minimap(t_cub *cub, int ratio_x, int ratio_y);
double			get_minimap_ratio(t_cub *cub, int rato_x, int ratio_y);

/*
** Game Loop
*/

void			start_gameloop(t_cub *cub);

/*
** Key_Hooks
*/

int				key_press(int keycode, t_cub *cub);
int				key_release(int keycode, t_cub *cub);
int				click_cross(t_cub *cub);

/*
** Raycaster
*/

int				raycasting(t_cub *cub, t_img *frame);

/*
** Wall Caster
*/

void			wallcasting(t_cub *cub, t_raycasting *rc, t_img *frame);
void			draw_wall(t_cub *cub, t_raycasting *rc, int x, t_img *frame);

/*
** Sprite Caster
*/

void			sort_sprites(t_cub *cub);
void			spritecasting(t_cub *cub, t_spritecasting *sc, t_img *frame);
void			draw_sprite(t_cub *cub, t_spritecasting *sc, t_img tex,
					t_img *frame);

/*
** Movement & Camera
*/

int				update_pos(t_cub *cub);

void			move_forward(t_cub *cub, double speed);
void			move_backwards(t_cub *cub, double speed);
void			strafe_left(t_cub *cub, double speed);
void			strafe_right(t_cub *cub, double speed);

void			turn_left(t_cub *cub, double rotspeed);
void			turn_right(t_cub *cub, double rotspeed);

/*
** Screenshot
*/

void			save_screenshot(t_cub *cub);
void			cub_img_to_bmp(t_img screen, const char *filename, t_cub *cub);

/*
** Exitting & Freeing
*/

void			free_cub(t_cub *cub);
int				exit_done(t_cub *cub);

/*
** Errors
*/

int				file_error(char *path, int err);
int				setting_error(char **args, t_set_id set_id, int err);
int				map_error(t_cub *cub, int y, int x, int errcode);

#endif
