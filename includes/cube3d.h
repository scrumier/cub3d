/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:17:42 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/05 13:27:12 by scrumier         ###   ########.fr       */
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
#  define KEY_E 14
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
	#define KEY_E XK_e
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
# define PLAYER_SPEED 0.09
# define PLAYER_ROTATE 0.5
# define PI 3.14159265359
# define FOV 60
# define RAYS WIDTH
# define BEAM_WIDTH 256
# define FPS 40
# define FXAA_ENABLED true
# define WALL_ACCURACY 200
# define THRESHOLD 0.1
# define RENDER_DISTANCE 200
# define TEXTURE_NB 6
typedef struct s_line
{
	double x;
	double y;
	double angle;
	double x1;
	double y1;
}				t_line;

typedef struct s_color_antialiasing
{
	unsigned int color_left;
	unsigned int color_right;
	unsigned int color_up;
	unsigned int color_down;
}				t_color_antialiasing;

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
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	char 	*path; // debug
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
	bool		go_left;
	bool		go_right;
}				t_move;

typedef struct	s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct	s_draw_wall
{
	int		i;
	int		wall_face;
	int		ray_nbr;
	double	line_height;
	double	line_start;
}				t_draw_wall;

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
	t_texture		*texture[TEXTURE_NB];
	double			last_fps[FPS];
}				t_data;

// tmp parsing code

typedef enum
{
	WALL_EA = 0,
	WALL_WE,
	WALL_SO,
	WALL_NO,
	BEAM,
	DOOR,
	CEILING,
	FLOOR
}	e_texture;

int	parse(t_data *data, char *file);
void	load_texture(t_data *data, t_texture *texture, char *path);
// end

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
void draw_square(t_data *data, t_coord coord, int coef, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	double_to_int(double x);
void	print_map(char **map);
int ft_abs(int x);
int	find_ray_texture(t_data *data, t_ray *ray);
double draw_line(t_ray *ray, t_data *data, int mode, int wall_accuracy);
bool	wall_around_01(t_data *data, double x, double y);
bool	wall_around_05(t_data *data, double x, double y);
double get_fps_average(t_data *data);
int	optimize_fps(double last_fps);
void	parse_rays(t_data *data);
void	mini_parse(t_data *data, char *file);
int	find_wall_facing(t_data *data, t_ray *ray);
void	draw_rectangle(t_data *data, int x, int y, int height, int width, int color);
void	open_door(t_data *data);
void render_wall_texture(t_data *data, t_ray *ray, int ray_nbr, double line_height, double line_start);
void	print_tab(double *tab);

#endif