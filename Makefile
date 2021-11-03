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

S_BONUS_DIR		=	bonus/
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
SOURCES			=	main.c \
					error.c \
					parse_cub.c \
					get_settings.c \
					get_settings_id.c \
					get_map.c \
					check_map.c \
					mlx_utils.c \
					gameloop.c \
					raycasting.c \
					wallcasting.c \
					draw_wall.c \
					sprites_utils.c \
					spritecasting.c \
					draw_sprite.c \
					draw_lines.c \
					key_hooks.c \
					camera.c \
					movement.c \
					make_bmp.c
SRCS 			=	$(addprefix $(S_DIR),$(SOURCES))

# Objects
OBJS			=	$(SRCS:.c=.o)

# Bonus Sources

SOURCES_BMP		=	make_bmp_bonus.c
S_BMP			=	$(addprefix $(S_BMP_DIR),$(SOURCES_BMP))

SOURCES_CONTROL	=	key_hooks_bonus.c \
					camera_bonus.c \
					movement_bonus.c
S_CONTROL		=	$(addprefix $(S_CONTROL_DIR),$(SOURCES_CONTROL))

SOURCES_DRAW	=	draw_lines_bonus.c \
					draw_triangle_bonus.c \
					mlx_utils_bonus.c \
					make_minimap_bonus.c \
					img_to_img_bonus.c \
					img_utils_bonus.c
S_DRAW			=	$(addprefix $(S_DRAW_DIR),$(SOURCES_DRAW))

SOURCES_ERROR	=	error_bonus.c
S_ERROR			=	$(addprefix $(S_ERROR_DIR),$(SOURCES_ERROR))

SOURCES_PARSE	=	parse_cub_bonus.c \
					parse_utils_bonus.c \
					tex_parse_utils_bonus.c \
					parse_config_bonus.c \
					parse_sprite_config_bonus.c \
					parse_surf_config_bonus.c \
					get_settings_bonus.c \
					get_settings_id_bonus.c \
					setting_handlers_bonus.c \
					setting_handle_mobs_bonus.c \
					setting_handle_sprites_bonus.c \
					setting_handle_teleporters_bonus.c \
					setting_handle_tex_anim_bonus.c \
					get_map_bonus.c \
					get_map_id_bonus.c \
					check_map_bonus.c \
					get_map_fc_bonus.c 
S_PARSE			=	$(addprefix $(S_PARSE_DIR),$(SOURCES_PARSE))

SOURCES_RAYCAST	=	raycasting_bonus.c \
					floorcasting_bonus.c \
					get_tex_bonus.c \
					skybox_bonus.c \
					wallcasting_bonus.c \
					draw_wall_bonus.c \
					spritecasting_bonus.c \
					draw_sprite_bonus.c
S_RAYCAST		=	$(addprefix $(S_RAYCAST_DIR),$(SOURCES_RAYCAST))

SOURCES_SPRITES	=	set_sprites_bonus.c \
					sprites_utils_bonus.c \
					sprites_update_utils_bonus.c
S_SPRITES		=	$(addprefix $(S_SPRITES_DIR),$(SOURCES_SPRITES))

SOURCES_EVENTS	=	event_hub_bonus.c \
					event_utils_bonus.c \
					event_goal_bonus.c \
					event_collect_bonus.c \
					event_remove_bonus.c \
					event_teleporter_bonus.c \
					event_projectile_bonus.c \
					event_heal_bonus.c
S_EVENTS		=	$(addprefix $(S_EVENTS_DIR),$(SOURCES_EVENTS))

SOURCES_HUD		=	init_hud_bonus.c \
					resize_hud_bonus.c \
					get_hud_tex_bonus.c \
					draw_hud_bonus.c \
					draw_hud_health_bonus.c
S_HUD			=	$(addprefix $(S_HUD_DIR),$(SOURCES_HUD))

SOURCES_MOB		=	mob_hub_bonus.c \
					set_mob_bonus.c \
					set_mob_ai_bonus.c \
					mobs_utils_bonus.c \
					find_target_bonus.c \
					change_behaviour_bonus.c \
					mob_behave_bonus.c \
					move_mob_bonus.c
S_MOB			=	$(addprefix $(S_MOB_DIR),$(SOURCES_MOB))

SOURCES_COLLISION	=	angle_to_vect_bonus.c \
						angles_bonus.c \
						hit_detection_bonus.c \
						sprite_collision_bonus.c
S_COLLISION		=	$(addprefix $(S_COLLISION_DIR),$(SOURCES_COLLISION))

SOURCES_GAME	=	init_game_bonus.c \
					gameloop_bonus.c \
					game_state_bonus.c \
					update_world_bonus.c \
					viewbobbing_bonus.c \
					action_bonus.c \
					action_change_bonus.c \
					player_attack_bonus.c \
					spawn_projectile_bonus.c \
					hit_bonus.c \
					damage_bonus.c \
					health_bonus.c
S_GAME			=	$(addprefix $(S_GAME_DIR),$(SOURCES_GAME))

SOURCES_BONUS	=	main_bonus.c \
					init_cub_bonus.c \
					struct_utils_bonus.c \
					exit_bonus.c \
					free_cub_bonus.c \
					free_map_specific_bonus.c

SOURCES_BONUS	+=	$(S_BMP) \
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


SRCS_BONUS		=	$(addprefix $(S_BONUS_DIR),$(SOURCES_BONUS))
# Bonus Objects

OBJS_BONUS		=	${SRCS_BONUS:.c=.o}

# Headers
HEAD			=	${LIB_DIR}libft.h ${I_DIR}cub3d.h ${I_DIR}bmp.h
HEAD_BONUS		=	${LIB_DIR}libft.h ${I_DIR}cub3d_bonus.h ${I_DIR}bmp_bonus.h

# Dependencies
#LIBFT_DEP	=	$(addprefix $(LIB_DIR),$(LIBFT_OBJS))
DEPEND			=	${HEAD}
DEPEND_BONUS	=	${HEAD_BONUS}

# Compile
CC				=	gcc
CFLAGS			=	-Werror -Wextra -Wall -ffast-math -O2 -g3 -I${I_DIR} -I${LIB_DIR}
#LINKS			=	-Lmlx -lmlx_Linux -L/usr/lib -I/usr/lib -Imlx -lXext -lX11 -lm -lz
LINKS = -L $(MLX_DIR) -lmlx_Linux -Imlx -L /usr/lib -lXext -lX11 -lm -lbsd -L $(LIB_DIR) -lft
LEAKS			=	-fsanitize=address

# Delete
RM				=	rm -f

.c.o			: ${DEPEND_BONUS}
				${CC} ${CFLAGS} ${LINKS} -c $< -o ${<:.c=.o}

all				:	${NAME}

$(NAME)			:	libft mlx ${OBJS} ${DEPEND}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LINKS}

bonus			:	libft mlx ${OBJS_BONUS} ${DEPEND_BONUS}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS_BONUS} ${LINKS}

libft			:
				make -C ${LIB_DIR}

mlx				:
				make -C ${MLX_DIR}

sanitize		:	libft mlx ${OBJS} ${DEPEND}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LEAKS} ${LINKS} 

san_bonus		:	libft mlx ${OBJS_BONUS} ${DEPEND_BONUS}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS_BONUS} ${LEAKS} ${LINKS}

norm			:
				norminette ${SRCS} ${HEAD} ${SRCS_BONUS} ${HEAD_BONUS}

clean			:
				${RM} ${OBJS} ${OBJS_BONUS}
				make clean -C ${LIB_DIR}
				make clean -C ${MLX_DIR}

fclean			:	clean
				${RM} ${NAME}
				make fclean -C ${LIB_DIR}

re				:	fclean all

.PHONY			:	all libft mlx bonus sanitize san_bonus norm clean fclean re
