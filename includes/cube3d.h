/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:17:42 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/28 10:40:20 by scrumier         ###   ########.fr       */
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
#  define KEY_F 3
#elif __linux__
# include <X11/keysym.h>
    #define KEY_ESC XK_Escape
    #define KEY_A   XK_a
    #define KEY_S   XK_s
    #define KEY_D   XK_d
    #define KEY_W   XK_w
	#define KEY_LEFT XK_Left
	#define KEY_RIGHT XK_Right
	#define KEY_F XK_f
#endif
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/time.h>
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define MOUSEMOVEMASK (1L<<6)
# define MOUSEMOVE 6
# define KEYPRESS 2
# define KEYREALASE 3
# define HEIGHT (900)
# define WIDTH (900)
# define COEF 7
# define COEF3D 5
# define PLAYER_SIZE 5
# define PLAYER_SPEED 0.03
# define PLAYER_ROTATE 0.01
# define PI 3.14159265359
# define FOV 85
# define RAYS 900
# define FPS_OPTI 0
# define BEAM_WIDTH 64
# define FPS 50
# define MAP_SIZE 40
# define FXAA_ENABLED true
# define WALL_ACCURACY 1000
# define THRESHOLD 8
# define RENDER_DISTANCE 100000

typedef struct s_line
{
	double x;
	double y;
	double angle;
	double x1;
	double y1;
}				t_line;

typedef struct s_ray
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	double rx;
	double ry;
	double ra;
	double xo;
	double yo;
	double dstx;
	double dsty;
	int	color;
	int face;
}				t_ray;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
}				t_texture;

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

typedef struct s_bresenham
{
	double	x;
	double	y;
	double angle;
	double x1;
	double y1;
	double dx;
	double dy;
	double xinc;
	double yinc;
	double steps;
	double x0;
	double y0;
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
	double		x;
	double		y;
	double		player_angle;
	double		pdx;
	double		pdy;
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
	void			*mlx;
	void			*win;
	t_img			img;
	int				ceiling_color;
	int				floor_color;
	t_player		*player;
	t_move			*move;
	bool			created_player;
	char			**map;
	int				mapX;
	int				mapY;
	double			ray_len[RAYS];
	struct timeval	current_time;
	struct timeval	last_time;
	double			fps;
	int				frame;
	bool			flash_light;
	t_texture		texture[5];
	double			last_fps[FPS];
}				t_data;

int	handle_keypressed(int key, t_data *data);
int	handle_keyrelease(int key, t_data *data);
void apply_custom_antialiasing(t_data *data);
double find_lowest_value(double *tab, int size);
double find_highest_value(double *tab, int size);
void	move_player(t_data *data);
int deg_to_rad(int deg);
void	print_minimap(t_data *data, int mode);
double	find_angle(int total_rays);
double	ft_dabs(double d);
void draw_square(t_data *data, int x, int y, int coef, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	double_to_int(double x);
void	print_map(char **map);
int ft_abs(int x);
int	find_ray_face(t_data *data, t_ray *ray);
double	draw_line(t_ray *ray, t_data *data, int mode);
bool	wall_around_01(t_data *data, double x, double y);
bool	wall_around_05(t_data *data, double x, double y);
double get_fps_average(t_data *data);
int	optimize_fps(double last_fps);
void	parse_rays(t_data *data);
void	mini_parse(t_data *data, char *file);
int	find_wall_facing(t_data *data, t_ray *ray);
void	draw_rectangle(t_data *data, int x, int y, int height, int width, int color);


void	print_tab(double *tab);
#endif