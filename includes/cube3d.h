/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:17:42 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/18 11:35:26 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

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
# elif __linux__
#  include <X11/keysym.h>
#  define KEY_ESC XK_Escape
#  define KEY_A   XK_a
#  define KEY_S   XK_s
#  define KEY_D   XK_d
#  define KEY_W   XK_w
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
#  define KEY_F XK_f
#  define KEY_E XK_e
# endif
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/time.h>
# include "errors.h"
# include "mlx.h"
# define MOUSEMOVE 6
# define KEYPRESS 2
# define KEYREALASE 3
# define DESTROYNOTIFY 17
# define HEIGHT 900
# define WIDTH 900
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
# define FXAA_ENABLED false
# define WALL_ACCURACY 50
# define THRESHOLD 1
# define RENDER_DISTANCE 100
# define TEXTURE_NB 6
# define HITBOX_RADIUS 0.2
// hitbox not below 0.1

typedef struct s_line
{
	double	x;
	double	y;
	double	angle;
	double	x1;
	double	y1;
}				t_line;

typedef struct s_color_antialiasing
{
	unsigned int	color_left;
	unsigned int	color_right;
	unsigned int	color_up;
	unsigned int	color_down;
}				t_color_antialiasing;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	dstx;
	double	dsty;
	int		color;
	int		face;
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
	char	*path;
}				t_texture;

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct s_bresenham
{
	double	x;
	double	y;
	double	angle;
	double	x1;
	double	y1;
	double	dx;
	double	dy;
	double	xinc;
	double	yinc;
	double	steps;
	double	x0;
	double	y0;
}				t_bresenham;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		player_angle;
	double		pdx;
	double		pdy;
}				t_player;

typedef struct s_move
{
	bool		forward;
	bool		backward;
	bool		turn_left;
	bool		turn_right;
	bool		go_left;
	bool		go_right;
}				t_move;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct s_draw_wall
{
	int		i;
	int		wall_face;
	int		ray_nbr;
	double	line_height;
	double	line_start;
}				t_draw_wall;

typedef struct s_line_3d
{
	double	line_height;
	double	line_start;
}				t_line_3d;

typedef struct s_llist
{
	char			*content;
	struct s_llist	*next;
}				t_llist;

typedef struct s_data
{
	int				animated_texture_index;
	int				next_image;
	void			*mlx;
	void			*win;
	t_img			img;
	int				ceiling_color;
	int				floor_color;
	t_player		*player;
	t_move			*move;
	bool			created_player;
	char			**map;
	int				mapx;
	int				mapy;
	double			ray_len[RAYS];
	struct timeval	current_time;
	struct timeval	last_time;
	double			fps;
	int				frame;
	bool			flash_light;
	t_texture		*texture[TEXTURE_NB];
	double			last_fps[FPS];
}				t_data;

typedef enum e_texture
{
	WALL_EA = 0,
	WALL_WE,
	WALL_SO,
	WALL_NO,
	BEAM,
	DOOR,
	CEILING,
	FLOOR
}				t_texture_enum;

int				parse(t_data *data, char *file);
int				load_texture(t_data *data, t_texture *texture, char *path);
int				handle_keypressed(int key, t_data *data);
int				handle_keyrelease(int key, t_data *data);
void			apply_custom_antialiasing(t_data *data);
void			move_player(t_data *data);
int				deg_to_rad(int deg);
void			print_minimap(t_data *data, int mode);
double			find_angle(int total_rays);
double			ft_dabs(double d);
void			draw_square(t_data *data, t_coord coord, int coef, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				double_to_int(double x);
int				ft_abs(int x);
int				find_ray_texture(t_data *data, t_ray *ray);
double			draw_line(t_ray *ray, t_data *data, int mode, \
							int wall_accuracy);
bool			wall_around_01(t_data *data, double x, double y);
bool			wall_around_05(t_data *data, double x, double y);
void			parse_rays(t_data *data);
int				find_wall_facing(t_data *data, t_ray *ray);
void			open_door(t_data *data);
void			render_wall_texture(t_data *data, t_ray *ray, int ray_nbr, \
									t_line_3d line);
void			print_tab(double *tab);
size_t			strarray_len(char **array);
void			free_strarray(char **array);
void			free_texture(t_data *data);
void			free_all(t_data *data);
bool			check_x_collision(t_data *data, double new_x, \
								double player_y, double radius);
bool			check_y_collision(t_data *data, double player_x, double new_y, \
										double radius);
bool			is_wall(t_data *data, double x, double y);
bool			door_around(t_data *data, double x, double y);
bool			closed_door_around(t_data *data, double x, double y);
void			close_door(t_data *data);
unsigned int	get_pixel_color(t_data *data, int x, int y);
double			calculate_distance(double x0, double y0, double xo, double yo);
int				is_out_of_bounds(int map_x, int map_y);
int				is_wall_hit(char **map, int map_x, int map_y);
void			update_ray_destination(t_ray *ray, double x0, double y0);
void			init_bresenham(t_bresenham *bresenham, t_ray *ray, \
								int wall_accuracy);
double			find_cube_center_y(t_data *data, double y);
double			find_cube_center_x(t_data *data, double x);
int				find_closest_to_05(double x, double y);
bool			is_wall(t_data *data, double x, double y);
bool			check_corner_collision(t_data *data, double new_x, \
										double new_y, double radius);
bool			is_out_of_the_map(t_data *data, double x, double y);
void			set_pixel_color(t_data *data, int x, int y, unsigned int color);
void			free_mlx_image(t_data *data, t_img *img);
void			free_all(t_data *data);
void			free_parse(t_data *data);
int				free_exit(t_data *data);
void			cast_rays(t_data *data, t_ray *ray, int total_rays, \
							double ray_angle);
int				get_texture_color(t_texture *texture, \
									double texture_offset, int tex_x);
int				darken_color(int color, double distance, double max_distance);
void			draw_player_on_minimap(t_data *data);
void			render_wall_texture(t_data *data, t_ray *ray, int ray_nbr, \
							t_line_3d line);
double			draw_and_correct_ray(t_ray *ray, t_data *data, \
								int wall_accuracy);
size_t			texture_array_len(t_texture *array);
bool			is_color_line(char *line);
bool			is_valid_char_color(char *line);
int				check_colors(t_data *data, char *line);
int				colors_init_check(size_t *i, char **line, size_t *start, size_t *color);
int				init_color_return(size_t color, t_texture_enum type, t_data *data, int *rgb);
int				color_line_check(char *line, size_t *i, size_t color);
int				init_colors(t_data *data, char *line, t_texture_enum type);
int				parse_colors(t_data *data, char **line_trimmed, char **line, int fd);
void			free_strarray(char **array);
void			free_llist(t_llist *list);
void			free_texture(t_data *data);
int				parse_init(size_t *i, char *file, int *fd);
int				parse_return(t_data *data, int fd);
int				parse_iter(char **line, char **line_trimmed, int fd);
int				parse_process(t_data *data, char **line, char **line_trimmed, int fd);
int				parse(t_data *data, char *file);
bool			is_map_char(char c);
void			map_fill_spaces(t_data *data);
int				map_check_init_x(size_t *x, size_t y, t_data *data);
char			*add_spaces(char *str, size_t amount);
int				padding_map(t_data *data, t_llist *map);
bool			is_everything_init(t_data *data);
int				space_check_diagonal(t_data *data, size_t x, size_t y);
int				space_check(t_data *data, size_t x, size_t y);
int				map_check(t_data *data);
double			get_player_angle(char c);
int				first_map_node(t_data *data, char *line, t_llist **map, t_llist **last);
int				add_map_node(t_data *data, char *line, t_llist **map, t_llist **last);
int				parse_map_iterate(t_data *data, char **line, int fd);
int				map_info_parse(t_data *data);
int				parse_map(t_data *data, char *line, int fd);
void			print_error(char *reason);
size_t			strarray_len(char **array);
char			*ft_strndup(const char *s, size_t n);
int				get_line_trimmed(char **line, char **line_trimmed, int fd);
int				load_texture(t_data *data, t_texture *texture, char *path);
int				init_walls_texture(t_data *data, char *line, t_texture_enum texture);
int				init_wall(t_data *data, char *line);
size_t			get_max_size(t_llist *list);
#endif