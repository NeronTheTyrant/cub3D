# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 11:51:44 by mlebard           #+#    #+#              #
#    Updated: 2021/07/14 20:46:34 by mlebard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME			=	cub3D
LIB				=	libft.a
MLX				=	libmlx.a

# Directories

S_DIR			=	srcs/

# S_DIR		=	bonus/
S_BMP_DIR		=	bmp/
S_CONTROL_DIR	=	controls/
S_DRAW_DIR		=	draw/
S_ERROR_DIR		=	error/
S_PARSE_DIR		=	parse/
S_RAYCAST_DIR	=	raycast/
S_SPRITES_DIR	=	sprites/
S_EVENTS_DIR	=	events/
S_HUD_DIR		=	hud/
S_MOB_DIR		=	mobs/
S_COLLISION_DIR	=	collision/
S_GAME_DIR		=	game/

I_DIR			=	include/
LIB_DIR			=	libft/
MLX_DIR			=	mlx/
MAP_DIR			=	map/

# Sources
# SOURCES			=	main.c \
# 					error.c \
# 					parse_cub.c \
# 					get_settings.c \
# 					get_settings_id.c \
# 					get_map.c \
# 					check_map.c \
# 					mlx_utils.c \
# 					gameloop.c \
# 					raycasting.c \
# 					wallcasting.c \
# 					draw_wall.c \
# 					sprites_utils.c \
# 					spritecasting.c \
# 					draw_sprite.c \
# 					draw_lines.c \
# 					key_hooks.c \
# 					camera.c \
# 					movement.c \
# 					make_bmp.c
# SRCS 			=	$(addprefix $(S_DIR),$(SOURCES))

# Objects
# OBJS			=	$(SRCS:.c=.o)

# Sources

SOURCES_BMP		=	make_bmp.c
S_BMP			=	$(addprefix $(S_BMP_DIR),$(SOURCES_BMP))

SOURCES_CONTROL	=	key_hooks.c \
					camera.c \
					movement.c
S_CONTROL		=	$(addprefix $(S_CONTROL_DIR),$(SOURCES_CONTROL))

SOURCES_DRAW	=	draw_lines.c \
					draw_triangle.c \
					mlx_utils.c \
					make_minimap.c \
					img_to_img.c \
					img_utils.c
S_DRAW			=	$(addprefix $(S_DRAW_DIR),$(SOURCES_DRAW))

SOURCES_ERROR	=	error.c
S_ERROR			=	$(addprefix $(S_ERROR_DIR),$(SOURCES_ERROR))

SOURCES_PARSE	=	parse_cub.c \
					parse_utils.c \
					tex_parse_utils.c \
					parse_config.c \
					parse_sprite_config.c \
					parse_surf_config.c \
					get_settings.c \
					get_settings_id.c \
					setting_handlers.c \
					setting_handle_mobs.c \
					setting_handle_sprites.c \
					setting_handle_teleporters.c \
					setting_handle_tex_anim.c \
					get_map.c \
					get_map_id.c \
					check_map.c \
					get_map_fc.c 
S_PARSE			=	$(addprefix $(S_PARSE_DIR),$(SOURCES_PARSE))

SOURCES_RAYCAST	=	raycasting.c \
					floorcasting.c \
					get_tex.c \
					skybox.c \
					wallcasting.c \
					draw_wall.c \
					spritecasting.c \
					draw_sprite.c
S_RAYCAST		=	$(addprefix $(S_RAYCAST_DIR),$(SOURCES_RAYCAST))

SOURCES_SPRITES	=	set_sprites.c \
					sprites_utils.c \
					sprites_update_utils.c
S_SPRITES		=	$(addprefix $(S_SPRITES_DIR),$(SOURCES_SPRITES))

SOURCES_EVENTS	=	event_hub.c \
					event_utils.c \
					event_goal.c \
					event_collect.c \
					event_remove.c \
					event_teleporter.c \
					event_projectile.c \
					event_heal.c
S_EVENTS		=	$(addprefix $(S_EVENTS_DIR),$(SOURCES_EVENTS))

SOURCES_HUD		=	init_hud.c \
					resize_hud.c \
					get_hud_tex.c \
					draw_hud.c \
					draw_hud_health.c
S_HUD			=	$(addprefix $(S_HUD_DIR),$(SOURCES_HUD))

SOURCES_MOB		=	mob_hub.c \
					set_mob.c \
					set_mob_ai.c \
					mobs_utils.c \
					find_target.c \
					change_behaviour.c \
					mob_behave.c \
					move_mob.c
S_MOB			=	$(addprefix $(S_MOB_DIR),$(SOURCES_MOB))

SOURCES_COLLISION	=	angle_to_vect.c \
						angles.c \
						hit_detection.c \
						sprite_collision.c
S_COLLISION		=	$(addprefix $(S_COLLISION_DIR),$(SOURCES_COLLISION))

SOURCES_GAME	=	init_game.c \
					gameloop.c \
					game_state.c \
					update_world.c \
					viewbobbing.c \
					action.c \
					action_change.c \
					player_attack.c \
					spawn_projectile.c \
					hit.c \
					damage.c \
					health.c
S_GAME			=	$(addprefix $(S_GAME_DIR),$(SOURCES_GAME))

SOURCES	=			main.c \
					init_cub.c \
					struct_utils.c \
					exit.c \
					free_cub.c \
					free_map_specific.c

SOURCES	+=	$(S_BMP) \
					$(S_CONTROL) \
					$(S_DRAW) \
					$(S_ERROR) \
					$(S_PARSE) \
					$(S_RAYCAST) \
					$(S_SPRITES) \
					$(S_EVENTS) \
					$(S_HUD) \
					$(S_MOB) \
					$(S_COLLISION) \
					$(S_GAME)


SRCS		=	$(addprefix $(S_DIR),$(SOURCES))
# Objects

OBJS		=	${SRCS:.c=.o}

# Headers
HEAD		=	${LIB_DIR}libft.h ${I_DIR}cub3d.h ${I_DIR}bmp.h

# Dependencies
#LIBFT_DEP	=	$(addprefix $(LIB_DIR),$(LIBFT_OBJS))
DEPEND			=	${HEAD}

# Compile
CC				=	gcc
CFLAGS			=	-Werror -Wextra -Wall -ffast-math -O2 -g3 -I${I_DIR} -I${LIB_DIR}
#LINKS			=	-Lmlx -lmlx_Linux -L/usr/lib -I/usr/lib -Imlx -lXext -lX11 -lm -lz
LINKS			= -L $(MLX_DIR) -lmlx_Linux -Imlx -L /usr/lib -lXext -lX11 -lm -lbsd -L $(LIB_DIR) -lft
LEAKS			=	-fsanitize=address

# Delete
RM				=	rm -f

.c.o			: ${DEPEND}
				${CC} ${CFLAGS} ${LINKS} -c $< -o ${<:.c=.o}

all				:	${NAME}

$(NAME)			:	libft mlx ${OBJS} ${DEPEND}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LINKS}

bonus			:	libft mlx ${OBJS} ${DEPEND}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LINKS}

libft			:
				make -C ${LIB_DIR}

mlx				:
				make -C ${MLX_DIR}

sanitize		:	libft mlx ${OBJS} ${DEPEND}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LEAKS} ${LINKS} 

san		:	libft mlx ${OBJS} ${DEPEND}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LEAKS} ${LINKS}

norm			:
				norminette ${SRCS} ${HEAD} ${SRCS} ${HEAD}

clean			:
				${RM} ${OBJS} ${OBJS}
				make clean -C ${LIB_DIR}
				make clean -C ${MLX_DIR}

fclean			:	clean
				${RM} ${NAME}
				make fclean -C ${LIB_DIR}

re				:	fclean all

.PHONY			:	all libft mlx bonus sanitize san norm clean fclean re
