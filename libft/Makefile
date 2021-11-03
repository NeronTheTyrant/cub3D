# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 16:05:10 by mlebard           #+#    #+#              #
#    Updated: 2021/06/16 19:18:10 by mlebard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_SRCS		=	ft_atoi.c ft_atof.c \
					ft_swap.c \
					ft_itoa.c ft_itoa_abs.c ft_itoa_base.c \
					ft_uitoa_base.c ft_uitoa_base_ptr.c \
					ft_check_base.c \
					ft_calloc.c ft_realloc.c \
					ft_isalnum.c ft_isalpha.c ft_islowercase.c ft_isuppercase.c ft_isascii.c ft_isdigit.c ft_isnumber.c ft_isfloat.c ft_isprint.c ft_isspace.c ft_iswspace.c \
					ft_tolower.c ft_toupper.c \
					ft_ishigher.c ft_islower.c ft_abs.c ft_absd.c ft_pow.c ft_getnbrlen_us.c \
					ft_bzero.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memswap.c \
					ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
					get_next_line.c filecheck.c \
					ft_strlen.c ft_isin.c ft_strchr.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strwchr.c \
					ft_split.c ft_splitset.c ft_strdup.c ft_strjoin.c ft_strtrim.c ft_substr.c strfill.c \
					ft_strlcat.c ft_strlcpy.c ft_strncpy.c \
					ft_strmapi.c ft_strcheck_each.c \
					ft_tabint.c \
					ft_argcheck_each.c ft_argcount.c ft_freeargs.c \
					make_argb.c argb_to_a.c argb_to_r.c argb_to_g.c argb_to_b.c str_to_rgb.c \
					ft_wctomb.c ft_wclen.c ft_wcslen.c \
					ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c \
					ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
					ft_lstsortif.c ft_lstswapone.c \
					ft_putlst.c

LIBFT_OBJS	=	${LIBFT_SRCS:.c=.o}

DEPEND		=	libft.h

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall -O2 -ffast-math -g3

RM			=	rm -f

NAME		=	libft.a

ifdef SANITIZE
	CFLAGS +=  -fsanitize=address -g3
endif

.c.o		: ${DEPEND}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all			:	${NAME}

$(NAME)		:	${LIBFT_OBJS} ${DEPEND}
			ar rc ${NAME} ${LIBFT_OBJS}
			ranlib ${NAME}

norm		:
			norminette ${LIBFT_SRCS} ${DEPEND}

sanitize	:	clean
			make SANITIZE:=1 $(NAME)

clean		:
			${RM} ${LIBFT_OBJS} ${BONUS_OBJS}

fclean		:	clean
			${RM} ${NAME}

re			:	fclean all

.PHONY		:	all bonus clean fclean re
