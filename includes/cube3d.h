/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:17:42 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/22 11:54:54 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# ifdef __APPLE__
#  include "../mlx_mac/mlx.h"
# elif __linux__
#  include "../mlx_linux/mlx.h"
# endif
# include "libft.h"
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_S   1
#  define KEY_A   0
#  define KEY_W   13
#  define KEY_D   2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#elif __linux__
# include <X11/keysym.h>
    #define KEY_ESC XK_Escape
    #define KEY_A   XK_a
    #define KEY_S   XK_s
    #define KEY_D   XK_d
    #define KEY_W   XK_w
	#define KEY_LEFT XK_Left
	#define KEY_RIGHT XK_Right
#endif
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define KEYPRESS 2
# define KEYREALASE 3
# define HEIGHT 800
# define WIDTH 800
# define COEF 15
# define PLAYER_SIZE 10
# define PLAYER_SPEED 0.1
# define PLAYER_ROTATE 0.1
# define PI 3.14159265359
# define FOV 95
# define RAYS 100
# define RENDER_DISTANCE 1000

typedef struct s_line
{
	float x;
	float y;
	float angle;
	float x1;
	float y1;
}				t_line;

typedef struct s_ray
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
}				t_ray;

typedef struct s_bresenham
{
	float	x;
	float	y;
	float angle;
	float x1;
	float y1;
	float dx;
	float dy;
	float xinc;
	float yinc;
	float steps;
	float x0;
	float y0;
}				t_bresenham;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_player
{
	float		x;
	float		y;
	float		player_angle;
	float		pdx;
	float		pdy;
}				t_player;

typedef struct	s_move
{
	bool		forward;
	bool		backward;
	bool		turn_left;
	bool		turn_right;
}				t_move;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	*player;
	t_move		*move;
	bool		created_player;
	char		map[10][10];
	int			mapX;
	int			mapY;
	float		ray_len[RAYS];
}				t_data;

#endif