/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:07:04 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 15:36:26 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# include <time.h>
# include <stdlib.h>
# include <pthread.h>

/*
** Error Defines
*/

# define SUCCESS				0
# define ERR_MALLOC				-1
# define ERR_FILE_EXTENSION		-2
# define ERR_NOT_FILE			-3
# define ERR_WRONG_ID			-4
# define ERR_DUP_ID				-5
# define ERR_ARG_NB				-6
# define ERR_BAD_ARG			-7
# define ERR_SET_OPEN			-8
# define ERR_SET_CLOSE			-9
# define ERR_EOF				-10
# define ERR_MAP_BORDERS		-11
# define ERR_MAP_INVALID		-12
# define ERR_MAP_OPEN			-13
# define ERR_MAP_PLAYERS		-14
# define ERR_MAP_NOPLAYER		-15
# define ERR_MAP_SMALL			-16
# define ERR_MAP_LINE			-17
# define ERR_MINI_SMALL			-18
# define ERR_TP_OUT_OF_BOUNDS	-19
# define ERR_TP_WALL			-20
# define ERR_READ				-21
# define ERR_WRITE				-22
# define ERR_HUD_SMALL			-23
# define ERR_BAD_SAVE_ARG		-24
# define ERR_MOB_OUT_OF_BOUNDS	-25
# define ERR_MOB_WALL			-25

/*
** ID Defines
*/

# define ID_MAP				1
# define ID_MAPF			2
# define ID_MAPC			3

typedef enum e_set_id
{
	DUP_ID = -2,
	WRONG_ID,
	RES,
	MINIMAP,
	SPRITE_POS,
	TELEPORTERS,
	MOBS,
	NEXT_LEVEL
}				t_set_id;

/*
** Key Flag Defines
*/

# define KEY_W				0x1
# define KEY_A				0x2
# define KEY_S				0x4
# define KEY_D				0x8
# define KEY_Q				0x10
# define KEY_E				0x20
# define KEY_UP_ARR			0x40
# define KEY_DW_ARR			0x80
# define KEY_SPACE			0x100
# define KEY_CTRL			0x200
# define KEY_SHIFT			0x400

/*
** Event Defines
*/

# define EVENT_COLLECT				1
# define EVENT_TELEPORT				2
# define EVENT_REMOVE				3
# define EVENT_HEAL_1				4
# define EVENT_GOAL					99
# define EVENT_PROXIMITY_THRESHOLD	100
# define EVENT_PROJECTILE			101
# define EVENT_MOB_PROJECTILE		102
# define EVENT_ANIMATION			103

/*
** Mob Defines
*/

# define AI_TURRET		1
# define AI_FIGHTER		2

# define BH_IDLE		0
# define BH_WALKING		1
# define BH_ATTACKING	2
# define BH_HURT		3
# define BH_DEATH		4

/*
** HUD Defines
*/

# define ACT_IDLE		0
# define ACT_FIREBALL	1
# define ACT_MACE		2

/*
** Attack Defines
*/

# define ATK_FIREBALL	0
# define ATK_MACE		1

/*
** Other Defines
*/

# define WALL_NBR			62
# define SET_NBR			6
# define SHADE_DIST			3
# define STATE_WIN			42
# define STATE_NEXT_LEVEL	21
# define STATE_DEAD			84

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_posmax
{
	intmax_t	x;
	intmax_t	y;
}				t_posmax;

typedef struct s_dpos
{
	double		x;
	double		y;
}				t_dpos;

typedef struct s_vect
{
	double		x;
	double		y;
}				t_vect;

typedef struct s_triangle
{
	t_pos		v1;
	t_pos		v2;
	t_pos		v3;
}				t_triangle;

typedef struct s_floorcast
{
	t_dpos		wall;
	t_dpos		pos;
	double		currdist;
}				t_floorcast;

typedef struct s_skybox
{
	t_dpos		raydirmin;
	t_dpos		raydirmax;
	double		rightside;
	double		leftside;
	t_dpos		step;
	double		pitch_adjust;
	t_pos		texel;
}				t_skybox;

typedef struct s_raycast
{
	t_vect		dir;
	t_pos		pos;
	t_dpos		delt;
	t_dpos		dist;
	t_pos		step;
	int			side;
	double		perp_dist;
	double		hit;
	int			wallheight;
	int			walltop;
	int			wallbot;
}				t_raycast;

typedef struct s_spritecast
{
	t_dpos		transform;
	int			screenx;
	int			height;
	int			width;
	int			move_screen;
	int			top;
	int			bot;
	int			left;
	int			right;
	int			stripe;
	t_posmax	texel;
}				t_spritecast;

typedef struct s_player
{
	int			flag;
	t_dpos		pos;
	double		z;
	t_dpos		render;
	double		renderz;
	double		bob;
	t_vect		dir;
	t_vect		plane;
	double		pitch;
	double		movspeed;
	double		rotspeed;
	int			act;
	int			sprites_collected;
	int			teleport;
	int			proj;
	int			proj_expl;
	int			maxhealth;
	int			health;
	clock_t		last_hit;
}				t_player;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				linelen;
	int				height;
	int				width;
	int				endi;
	struct s_img	*next_tex;
	clock_t			delay;
}				t_img;

typedef struct s_sprite
{
	int			id;
	int			ev_id;
	int			mob_id;
	t_dpos		pos;
	t_vect		dir;
	double		speed;
	int			teleport;
	double		dist;
	int			collision;
	int			hmove;
	int			hdiv;
	int			wdiv;
	int			event;
	t_img		*tex;
	clock_t		last_update;
	int			update;
}				t_sprite;

typedef struct s_surface
{
	clock_t		last_update;
	t_img		*tex;
}				t_surface;

typedef struct s_textures
{
	int			texnbr;
	t_img		*tex;
}				t_textures;

typedef struct s_minimap
{
	int			on;
	int			off;
	t_pos		ratio;
	t_pos		limits;
	t_pos		range;
	int			tilesize;
	int			wall_color;
	int			floor_color;
	int			player_color;
}				t_minimap;

typedef struct s_hudobj
{
	int			xcurroff;
	int			ycurroff;
	int			xbaseoff;
	int			ybaseoff;
	t_img		*tex;
	clock_t		last_update;
}				t_hudobj;

typedef struct s_hud
{
	t_img		hp_full;
	t_img		hp_empty;
	t_img		hp_half;
	t_img		crosshair;
	t_img		hands_idle[3];
	t_img		hands_attack[7];
	t_hudobj	hands;
	t_img		mace_idle;
	t_img		mace_attack[7];
	t_hudobj	mace;
}				t_hud;

typedef struct s_event
{
	int					id;
	int					sp_id;
	int					type;
	t_dpos				pos;
	t_dpos				tp;
	double				range;
	int					hit;
	int					val1;
	int					val2;
	void				*data;
}						t_event;

typedef struct s_mob
{
	int					id;
	int					sp_type;
	int					sp_id;
	int					ai;
	int					behaviour;
	int					hp;
	int					hpmax;
	t_dpos				pos;
	t_vect				dir;
	double				speed;
	double				proj_speed;
	t_img				*base;
	t_img				*walking;
	t_img				*attack;
	t_img				*projectile;
	t_img				*explosion;
	t_img				*hurt;
	t_img				*death;
	int					death_height;
	double				attackrange;
	clock_t				lastattack;
	clock_t				attackdelay;
}						t_mob;

typedef struct s_cub
{
	int				fd;
	void			*mlx;
	void			*win;
	clock_t			timeref;
	clock_t			time;
	double			frametime;
	t_pos			res;
	char			set_id[3];
	t_player		*play;
	t_raycast		*ray;
	t_spritecast	*sprite;
	t_floorcast		*floor;
	t_skybox		*sky;
	int				sp_type_nb;
	t_sprite		*sp_type;
	int				sp_nb;
	int				mob_type_nb;
	t_mob			*mob_type;
	int				mob_nb;
	t_list			*sp;
	t_list			*event;
	t_list			*mob;
	int				event_count;
	t_textures		*tex_sf;
	t_textures		*tex_sp;
	t_img			tex_sky;
	t_hud			*hud;
	char			**map;
	char			**mapf;
	char			**mapc;
	t_surface		sf[WALL_NBR];
	char			*wallc;
	char			*wallplayc;
	t_minimap		*mini;
	int				map_w;
	int				map_h;
	double			*z;
	uint32_t		keys;
	int				save;
	int				in_sf_config;
	int				in_sp_config;
	char			*nextmap;
	int				state;
	int				goal;
	int				error;
}				t_cub;

int				init_cub(t_cub *cub);

/*****
****** ** Parser **
*****/

/*
** a. Parse Manager
*/

int				load_map(t_cub *cub, char *path);
int				parse_cub(t_file map, t_cub *cub);

/*
** b. Settings
*/

t_set_id		get_id(char *arg);
int				get_settings(char **args, int fd, int *check, t_cub *cub);
int				get_next_setting(char ***args, int fd);

int				parse_config_textures(t_file config, t_textures *tx,
					t_cub *cub);
int				parse_config_animation(t_file config, t_textures *tx,
					t_cub *cub);
int				get_surface_config(int fd, t_cub *cub);
int				get_sprite_config(int fd, t_cub *cub);
int				parse_config_mob_info(t_file config, t_cub *cub);

/*
** c. Setting Handlers
*/

int				open_set(int fd);
int				close_set(int fd);

int				handle_textures(int fd, t_cub *cub, int limit, t_img *path);
int				get_tex_nbr(char *args, int limit);

int				handle_anim(int fd, t_cub *cub, int limit, t_img *texpath);
void			set_anim(t_img *f1, t_img *f2, double delay);

int				handle_sprite_info(int fd, t_cub *cub);

int				handle_resolution(char **args, t_cub *cub);
int				handle_skybox(char **args, t_cub *cub);
int				handle_sprites(int fd, t_cub *cub);
int				handle_teleporters(int fd, t_cub *cub);
int				handle_minimap(char **args, t_cub *cub);
int				handle_mobs(int fd, t_cub *cub);
int				handle_next_level(char **args, t_cub *cub);

int				check_tex(char *args, int limit, t_img *path);
int				assign_texture(char **args, t_cub *cub, t_img *img);
int				assign_texture_from_path(char *path, t_cub *cub, t_img *img);

/*
** d. Map
*/

int				parse_map(t_file mapfile, t_cub *cub);
int				check_map(t_cub *cub);
int				handle_map_floor(char **args, t_file mapfile, t_cub *cub);
int				handle_map_ceil(char **args, t_file mapfile, t_cub *cub);
int				check_map_id(char **args, t_cub *cub, int map_id);

/*****
****** ** Controls **
*****/

/*
** a. Key_Hooks
*/

int				key_press(int keycode, t_cub *cub);
int				key_release(int keycode, t_cub *cub);
int				mouse_move(int x, int y, t_cub *cub);
int				click_cross(t_cub *cub);

/*
** b. Movement & Camera
*/

int				update_pos(t_cub *cub, t_player *play);

void			check_next_move(t_cub *cub, double *nextx, double *nexty);

int				move_forward(t_cub *cub, t_dpos *pos, t_vect dir, double speed);
int				move_backwards(t_cub *cub, t_dpos *pos, t_vect dir,
					double speed);
int				strafe_left(t_cub *cub, t_dpos *pos, t_vect plane,
					double speed);
int				strafe_right(t_cub *cub, t_dpos *pos, t_vect plane,
					double speed);

void			turn_left(t_cub *cub, double rotspeed);
void			turn_right(t_cub *cub, double rotspeed);
void			look_up(t_cub *cub, double rotspeed);
void			look_down(t_cub *cub, double rotspeed);

/*****
****** ** Game Systems **
*****/

/*
** a. Game Loop
*/

void			init_game(t_cub *cub);
void			init_game_values(t_cub *cub);
int				set_sprite_update(t_cub *cub);
int				set_surface_tex(t_cub *cub);
int				gameloop(t_cub *cub);

void			check_game_state(t_cub *cub);
void			update_world(t_cub *cub);

void			update_sprite_status(t_cub	*cub, t_list *sp_lst);
int				update_sprite_textures(t_cub *cub);
int				update_surface_textures(t_cub *cub);
void			update_action(t_cub *cub);
void			update_viewbobbing(t_cub *cub, t_player *play);

/*
** b. Events
*/

int				add_event_from_sprite(t_cub *cub, t_sprite sp);
int				add_event(t_cub *cub, t_event ev);

t_list			*get_event_lst_by_id(t_list *ev_ptr, int id);
t_event			*get_event_by_id(t_list *ev_ptr, int id);

int				in_range(t_dpos pos, t_dpos pos2, double range);

int				event_hub(t_cub *cub, t_list *lst);
int				event_check_proximity(t_cub *cub, t_event *event,
					t_list *ev_lst);
int				event_check_other(t_cub *cub, t_event *event, t_list *ev_lst);

int				event_collect(t_cub *cub, t_event *event, t_list *lst);
int				add_event_collect(t_cub *cub, t_sprite sp);

int				event_remove(t_cub *cub, t_event *event);
int				add_event_remove(t_cub *cub, t_sprite sp);

int				event_teleport(t_dpos *pos, int *teleport_flag, t_event *event);
int				add_event_teleport(t_cub *cub, t_sprite sp, t_dpos tp);
int				check_teleport_pos(t_cub *cub);

int				spawn_player_projectile(t_cub *cub, t_player *play);
int				event_projectile(t_cub *cub, t_event *event, t_list *ev_ptr);
int				check_teleport(t_list *ev_lst, t_dpos *pos, int *teleport_flag);

int				spawn_mob_projectile(t_cub *cub, t_mob *mob);
int				event_mob_projectile(t_cub *cub, t_event *event,
					t_list *ev_ptr);
int				move_mob_proj_forward(t_cub *cub, t_sprite *sp, double speed);

int				spawn_projectile_explosion(t_cub *cub, t_event *proj,
					t_sprite *sp);

int				event_heal(t_cub *cub, t_event *event, t_list *lst);
int				add_event_heal(t_cub *cub, t_sprite sp);

int				event_goal(t_cub *cub);
int				add_event_goal(t_cub *cub, t_sprite sp);

/*
** c. Sprites & Entities
*/

int				set_sprite(char **args, t_sprite *sp, t_cub *cub);
void			set_sprite_posxy(double x, double y, t_sprite *sp);
void			set_sprite_div(int hdiv, int wdiv, t_sprite *sp);

int				add_sprite(t_sprite sp, t_cub *cub);
int				add_sprite_from_mob(t_cub *cub, t_mob mob);

t_list			*get_sprite_lst_by_id(t_list *lst, int id);
t_sprite		*get_sprite_by_id(t_list *lst, int id);

void			check_sprite_update(t_cub *cub, t_sprite *sp);
void			update_sprite_tex(t_cub *cub, t_sprite *sprite,
					t_img *nextframe);

/*
** d. MOBS
*/

int				add_mob(t_mob mob, t_cub *cub);
int				set_mob(char **args, t_mob *mob, t_cub *cub);
void			set_mob_posxy(double x, double y, t_mob *mob);
int				check_mob_type(char *args, t_cub *cub);
void			set_mob_ai_fighter(t_mob *mob);
void			set_mob_ai_turret(t_mob *mob);

void			mob_hub(t_cub *cub, t_list *mob_lst);
t_list			*get_mob_lst_by_id(t_list *lst, int id);
t_mob			*get_mob_by_id(t_list *lst, int id);
int				check_mob_pos(t_cub *cub);

int				find_target(t_cub *cub, t_dpos pos, t_vect dir, double limit);

void			change_behaviour_idle(t_cub *cub, t_mob *mob, t_sprite *sp);
void			change_behaviour_walk(t_cub *cub, t_mob *mob, t_sprite *sp);
void			change_behaviour_attack(t_cub *cub, t_mob *mob, t_sprite *sp);
void			change_behaviour_hurt(t_cub *cub, t_mob *mob, t_sprite *sp);
void			change_behaviour_dying(t_cub *cub, t_mob *mob, t_sprite *sp);

void			mob_behave(t_cub *cub, t_mob *mob, t_sprite *sprite);

int				mob_move_forward(t_cub *cub, t_mob *mob);

/*
** e. Hit detection
*/

int				check_sprite_collision(t_cub *cub, t_dpos pos, int id_ignore);
int				check_sprite_collision_ignore_mobs(t_cub *cub, t_dpos pos);

int				check_hit(t_cub *cub, t_event *event);
int				check_mob_hit(t_cub *cub, t_event *proj);

int				hit_event(t_cub *cub, int atk_type, t_event *hit);
void			hit_mob(t_cub *cub, int atk_type, t_mob *mob);
void			hit_player(t_cub *cub, t_event *ev);

void			player_attack(t_cub *cub, double dist);
void			mob_attack(t_cub *cub, t_mob *mob, t_sprite *mob_sp,
					double dist);

/*
** f. Damage & health
*/

void			add_health(t_cub *cub, int health);
void			remove_health(t_cub *cub, int damage);

int				atk_type_to_damage(int atk_type);
void			damage_mob(t_cub *cub, t_mob *mob, int damage);

/*
** g. Player Actions
*/

void			fireball(t_cub *cub);
void			mace(t_cub *cub);

void			change_action_idle(t_cub *cub);
void			change_action_fireball(t_cub *cub);
void			change_action_mace(t_cub *cub);

/*
** lol. math / geometrics
*/

t_vect			angle_to_vect(double angle);
double			angle_atan_to_angle_cardinal(double angle);
int				angle_diff(t_vect reference, t_vect target, double threshold);
double			angle_atan_to_angle_cardinal(double angle);
double			get_angle_from_pos(t_dpos origin, t_dpos target);

/*****
****** ** Render **
*****/

/*
** a. Raycaster
*/

int				raycasting(t_cub *cub, t_img *frame);
t_img			get_sf_tex(t_cub *cub, t_raycast *ray);

/*
** b. Wall Caster
*/

void			wallcasting(t_cub *cub, t_raycast *ray, t_img *frame);
void			draw_wall(t_cub *cub, t_raycast *ray, int x, t_img *frame);

/*
** c. Vertical Caster
*/

void			floorcasting(t_cub *cub, t_floorcast *floor, int x,
					t_img *frame);
void			init_skybox(t_cub *cub, t_skybox *sky, t_player *play);
void			draw_skybox(t_cub *cub, int x, int y, t_img *frame);
t_img			get_floor_tex(t_cub *cub, t_floorcast *floor);
t_img			get_ceil_tex(t_cub *cub, t_floorcast *floor);

/*
** d. Sprite Caster
*/

void			get_sprite_dist(t_cub *cub, t_list *lst);
int				sort_sprites(t_sprite *sp1, t_sprite *sp2);
void			spritecasting(t_cub *cub, t_spritecast *sprite, t_img *frame);
void			draw_sprite(t_cub *cub, t_spritecast *sprite, t_sprite *sp,
					t_img *frame);

/*
** e. Minimap
*/

int				init_minimap(t_cub *cub, t_minimap *mini);
void			display_minimap(t_cub *cub, t_minimap *mini, t_img *frame);

/*****
****** ** HUD **
*****/

/*
** a. Init & Resize
*/

int				init_hud(t_cub *cub);
int				resize_hud(t_cub *cub, t_hud *hud);
int				get_hud_tex(t_cub *cub, t_hud *hud);
void			init_hud_obj(t_hudobj *obj, int xoffset, int yoffset,
					t_img *tex);

/*
** b. Draw hud
*/

int				draw_hud(t_cub *cub, t_img *frame);
int				draw_health(t_cub *cub, t_img *frame);

/*****
****** ** Minilibx **
*****/

/*
** a. MLX Utils
*/

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				get_pixel(intmax_t x, intmax_t y, t_img img);
t_img			make_img(void*mlx, int x, int y);
void			fill_img(int limitx, int limity, t_img *img, int color);
t_img			mlx_resize_img(void *mlx, t_img img, int sizex, int sizey);
void			free_mlx_image(t_cub *cub, void *img);

/*
** b. Image to Image
*/

int				put_img_to_frame(t_img *frame, t_img img, int startx,
					int starty);
int				put_img_to_frame_alpha(t_img *frame, t_img img, int startx,
					int starty);

/*
** c. Colour Utils
*/

int				add_shade(double dist, int color);
int				add_alpha(int bg_color, int top_color);

/*
** d. Geometric Shapes
*/

void			draw_circle(t_pos pos, int r, int color, t_img *img);
void			horline(int hor, t_pos coord, int color, t_img *img);
void			vertline(int vert, t_pos coord, int color, t_img *img);
void			draw_line(t_pos v1, t_pos v2, int color, t_img *img);
void			draw_triangle(t_triangle tri, int color, t_img *minimap);

/*****
****** ** Backend System **
*****/

/*
** a. Exitting & Freeing
*/

void			free_cub(t_cub *cub);
void			free_map_specific(t_cub *cub);
int				exit_done(t_cub *cub);
void			exit_error(t_cub *cub, int errcode, char *errstring);

/*
** b. Errors
*/

int				cub_error(t_cub *cub, int errcode, char *str);
int				setting_error(t_cub *cub, char **args, int errcode, char *str);
int				map_error(t_cub *cub, int y, int x, int errcode);

/*
** c. BMP Screenshot
*/

int				cub_img_to_bmp(t_img screen, const char *filename, t_cub *cub);
void			save_screenshot(t_cub *cub);

/*****
****** ** Misc. **
*****/

/*
** a. Struct Utils
*/

t_pos			get_pos(int x, int y);
t_dpos			get_dpos(double x, double y);
t_triangle		get_triangle(t_pos v1, t_pos v2, t_pos v3);

int				check_file_extension(char *path, char *extension);

#endif
