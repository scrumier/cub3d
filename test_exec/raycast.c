/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/22 20:31:39 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	double_to_int(double x)
{
	if (x - (int)x > 0.5)
		return ((int)x + 1);
	return ((int)x);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_len + x * \
			(data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

// the coef is a value to scale the square

void	print_map(char map[10][10])
{
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	mini_parse(t_data *data, char *file)
{
	int fd = open(file, O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	int j = 0;
	int k = 0;
	data->mapX = 10;
	data->mapY = 10;

	while (line)
	{
		j = 0;
		k = 0;
		while (line[j])
		{
			data->map[i][j] = line[k];
			j++;
			k += 2;
		}
		line = get_next_line(fd);
		i++;
	}
	
}

int	handle_keyrelease(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->move->forward = false;
	}
	if (key == KEY_S)
	{
		data->move->backward = false;
	}
	if (key == KEY_A)
	{
		data->move->turn_left = false;
	}
	if (key == KEY_D)
	{
		data->move->turn_right = false;
	}
	return (0);
}

void draw_square(t_data *data, int x, int y, int coef, int color)
{
	int i = 0;
	int j = 0;
	(void)color;
	(void)data;
	(void)x;
	(void)y;


	while (i < coef)
	{
		j = 0;
		while (j < coef)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void init_bresenham(t_data *data, t_bresenham *bresenham)
{
	bresenham->x = data->player->x * COEF + (COEF / 2);
	bresenham->y = data->player->y * COEF + (COEF / 2);
	bresenham->angle = data->player->player_angle;
	bresenham->x1 = bresenham->x + 30 * cos(bresenham->angle);
	bresenham->y1 = bresenham->y + 30 * sin(bresenham->angle);
	bresenham->dx = bresenham->x1 - bresenham->x;
	bresenham->dy = bresenham->y1 - bresenham->y;
	if (bresenham->dx < 0)
	{
		bresenham->xinc = -1;
		bresenham->dx = -bresenham->dx;
	}
	else
		bresenham->xinc = 1;
	if (bresenham->dy < 0)
	{
		bresenham->yinc = -1;
		bresenham->dy = -bresenham->dy;
	}
	else
		bresenham->yinc = 1;
	bresenham->dx = ft_abs(bresenham->dx);
	bresenham->dy = ft_abs(bresenham->dy);
	if (bresenham->dx > bresenham->dy)
		bresenham->steps = bresenham->dx;
	else
		bresenham->steps = bresenham->dy;
	bresenham->xinc *= (double)bresenham->dx / bresenham->steps;
	bresenham->yinc *= (double)bresenham->dy / bresenham->steps;
	bresenham->x0 = bresenham->x;
	bresenham->y0 = bresenham->y;
}

void	bresenham(t_data *data)
{
	t_bresenham bresenham;
	int i;

	i = -40;
	init_bresenham(data, &bresenham);
	while (i < bresenham.steps)
	{
		my_mlx_pixel_put(data, bresenham.x0, bresenham.y0, 0x00FFFFFF);
		bresenham.x0 += bresenham.xinc;
		bresenham.y0 += bresenham.yinc;
		i++;
	}
}

int	find_wall_facing(t_data *data, t_ray *ray)
{
	(void)data;
	double wall_center_x = (double)double_to_int(ray->dstx) + 0.5;
	double wall_center_y = (double)double_to_int(ray->dsty) + 0.5;
	double x = ray->dstx - wall_center_x;
	double y = ray->dsty - wall_center_y;
	int north = 0;
	int south = 0;
	int east = 0;
	int west = 0;

	while (ray->dstx)
	if (north < south && north < east && north < west)
		return (1);
	if (south < north && south < east && south < west)
		return (2);
	if (east < north && east < south && east < west)
		return (3);
	if (west < north && west < south && west < east)
		return (4);
	return (0);
}

int	find_ray_color(t_data *data, t_ray *ray)
{
	int face = find_wall_facing(data, ray);
	if (face == 1) // purple
		return (0x00FF00FF);
	else if (face == 2) // red
		return (0x00FF0033);
	else if (face == 3) // blue
		return (0x007777FF);
	else if (face == 4) // green
		return (0x0044FF44);
	return (0x00000000);
}

double	draw_line(t_ray *ray, t_data *data, int mode)
{
	t_bresenham bresenham;
	int i;

	i = 0;
	bresenham.x = ray->xo;
	bresenham.y = ray->yo;
	bresenham.x1 = ray->rx;
	bresenham.y1 = ray->ry;
	bresenham.dx = bresenham.x1 - bresenham.x;
	bresenham.dy = bresenham.y1 - bresenham.y;
	if (bresenham.dx < 0)
	{
		bresenham.xinc = -1;
		bresenham.dx = -bresenham.dx;
	}
	else
		bresenham.xinc = 1;
	if (bresenham.dy < 0)
	{
		bresenham.yinc = -1;
		bresenham.dy = -bresenham.dy;
	}
	else
		bresenham.yinc = 1;
	bresenham.dx = ft_abs(bresenham.dx);
	bresenham.dy = ft_abs(bresenham.dy);
	if (bresenham.dx > bresenham.dy)
		bresenham.steps = bresenham.dx;
	else
		bresenham.steps = bresenham.dy;
	bresenham.xinc *= (double)bresenham.dx / bresenham.steps;
	bresenham.yinc *= (double)bresenham.dy / bresenham.steps;
	bresenham.x0 = bresenham.x;
	bresenham.y0 = bresenham.y;
	while (i < bresenham.steps)
	{
		if (data->map[ft_abs(bresenham.x0) / COEF][ft_abs(bresenham.y0) / COEF] == '1')
		{
			ray->dstx = bresenham.x0;
			ray->dsty = bresenham.y0;
			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));
		}
		if (mode == 1)
		{
			my_mlx_pixel_put(data, bresenham.x0, bresenham.y0, ray->color);
		}
		bresenham.x0 += bresenham.xinc;
		bresenham.y0 += bresenham.yinc;
		i++;
	}
	ray->dstx = bresenham.x0;
	ray->dsty = bresenham.y0;
	return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->ry, 2)));
}

double	find_angle()
{
	double rad;

	rad = FOV * PI / 180;
	return (rad / RAYS);
}

int	round_double(double x)
{
	int result;

	result = (int)x;
	if (x > result)
		return (result);
	return (result - 1);
}


void	print_minimap(t_data *data, int mode)
{
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (data->map[i][j] == '1' && mode == 2)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00FF0000);
			else if (data->map[i][j] == '0' && mode == 1)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00000000);
			
			j++;
		}
		i++;
	}
}

void	print_tab(double *tab)
{
	int i = 0;

	while (i < RAYS)
	{
		printf("Ray[%i] = %f\n", i, tab[i]);
		i++;
	}
}

int deg_to_rad(int deg)
{
	return (deg * PI / 180);
}

void	parse_rays(t_data *data)
{
	t_ray ray;
	int ray_nbr;
	double ray_angle;

	ray.ra = data->player->player_angle;
	ray.dof = 0;
	ray_nbr = 0;
	ray_angle = find_angle();
	while (ray_nbr < RAYS)
	{
		ray.rx = data->player->x * COEF + (COEF / 2);
		ray.ry = data->player->y * COEF + (COEF / 2);
		ray.xo = ray.rx + 1;
		ray.yo = ray.ry + 1;
		ray.rx += RENDER_DISTANCE * cos(ray.ra);
		ray.ry += RENDER_DISTANCE * sin(ray.ra);
		//remove fish eye effect
		double angle = ray.ra - (data->player->player_angle + deg_to_rad(FOV / 2));
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		data->ray_len[ray_nbr] = draw_line(&ray, data, 1);
		double line_height = HEIGHT * COEF3D / data->ray_len[ray_nbr];
		double line_start = (WIDTH / 2) - (line_height / 2);
		int i = 0;
		ray.color = find_ray_color(data, &ray);
		while (i < line_height)
		{
			int n = -1;
			if (ray_nbr * (double)(WIDTH / RAYS) < WIDTH && i + line_start < HEIGHT)
			{
				while (++n < (double)(WIDTH / RAYS))
					my_mlx_pixel_put(data, ray_nbr * (double)(WIDTH / RAYS) + n, i + line_start, ray.color);
			}
			i++;
		}
		ray.ra += ray_angle;
		ray_nbr++;
	}
}

void	draw_player(t_data *data)
{
	draw_square(data, data->player->x * COEF + (COEF / 2) - (PLAYER_SIZE / 2), data->player->y * COEF + (COEF / 2) - (PLAYER_SIZE / 2), PLAYER_SIZE, 0x0000FF00);
	parse_rays(data);
}

void	draw_rectangle(t_data *data, int x, int y, int height, int width, int color)
{
	int i = 0;
	int j = 0;

	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	move_player(t_data *data)
{

	if (data->player->x < 0 || data->player->x > 9 || data->player->y < 0 || data->player->y > 9)
	{
		data->created_player = false;
		return ;
	}
	if (data->move->forward == true)
	{
		data->player->x += PLAYER_SPEED * cos(data->player->player_angle + ((FOV / 2) * PI / 180));
		data->player->y += PLAYER_SPEED * sin(data->player->player_angle + ((FOV / 2) * PI / 180));
	}
	if (data->move->backward == true)
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle + ((FOV / 2) * PI / 180));
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle + ((FOV / 2) * PI / 180));
	}
	if (data->move->turn_left == true)
	{
		data->player->player_angle = (data->player->player_angle - PI / 30);
		data->player->pdx = 50 * cos(data->player->player_angle);
		data->player->pdy = 50 * sin(data->player->player_angle);
	}
	if (data->move->turn_right == true)
	{
		data->player->player_angle = (data->player->player_angle + PI / 30);
		data->player->pdx = 50 * cos(data->player->player_angle);
		data->player->pdy = 50 * sin(data->player->player_angle);
	}
}

int	create_image(t_data *data)
{
	int 	i = 0;
	int 	j = 0;
\
	move_player(data);
	if (data->player->x < 0 || data->player->x > 9 || data->player->y < 0 || data->player->y > 9 \
		|| data->map[double_to_int(data->player->x)][double_to_int(data->player->y)] == '1')
		data->created_player = false;
	draw_rectangle(data, 0, 0, HEIGHT, WIDTH / 2, 0x000000aa);
	draw_rectangle(data, 0, WIDTH / 2, HEIGHT, WIDTH / 2, 0x00aa0000);
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (data->map[i][j] == '0' && !data->created_player)
			{
				data->player->x = i;
				data->player->y = j;
				draw_player(data);
				data->created_player = true;
			}
			if (data->map[i][j] == '0' && data->created_player)
				draw_player(data);
			j++;
		}
		i++;
	}
	print_minimap(data, 2);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

bool	forward_is_valid_chunk(t_data *data)
{
	int x = double_to_int(data->player->x + 0.20 * cos(data->player->player_angle + ((FOV / 2) * PI / 180)));
	int y = double_to_int(data->player->y + 0.20 * sin(data->player->player_angle + ((FOV / 2) * PI / 180)));

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

bool	backward_is_valid_chunk(t_data *data)
{
	int x = double_to_int(data->player->x - (PLAYER_SPEED - 10) * cos(data->player->player_angle + ((FOV / 2) * PI / 180)));
	int y = double_to_int(data->player->y - (PLAYER_SPEED - 10) * sin(data->player->player_angle + ((FOV / 2) * PI / 180)));

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}


int	handle_keypressed(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (key == KEY_W)
	{
		data->move->forward = true;
	}
	if (key == KEY_S)
	{
		data->move->backward = true;
	}
	if (key == KEY_A)
	{
		data->move->turn_left = true;
	}
	if (key == KEY_D)
	{
		data->move->turn_right = true;
	}
	return (0);
}

int	handle_no_event(t_data *data)
{
	create_image(data);
	return (0);
}

bool left_is_valid_chunk(t_data *data)
{
	int x = double_to_int(data->player->x + 0.20 * cos(data->player->player_angle + ((FOV / 2) * PI / 180)));
	int y = double_to_int(data->player->y + 0.20 * sin(data->player->player_angle + ((FOV / 2) * PI / 180)));

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

bool right_is_valid_chunk(t_data *data)
{
	int x = double_to_int(data->player->x + 0.20 * cos(data->player->player_angle - ((FOV / 2) * PI / 180)));
	int y = double_to_int(data->player->y + 0.20 * sin(data->player->player_angle - ((FOV / 2) * PI / 180)));

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data		*data = NULL;
	t_player	*player = NULL;
	t_move		*move = NULL;
	char 		*line = NULL;
	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
	move = malloc(sizeof(t_move));
	data->player = player;
	data->move = move;

	if (ac != 2)
	{
		printf("Error\n");
		return (0);
	}
	data->created_player = false;
	line = ft_strdup(av[1]);
	mini_parse(data, line);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->player->player_angle = 0;
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, &handle_keypressed, data);
	mlx_hook(data->win, KEYREALASE, KEYRELEASEMASK, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	return (0);
}
