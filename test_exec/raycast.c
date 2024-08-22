/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/22 12:04:24 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	print_map(data->map);
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
	bresenham->xinc *= (float)bresenham->dx / bresenham->steps;
	bresenham->yinc *= (float)bresenham->dy / bresenham->steps;
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

bool	is_looking_up(int ray_angle)
{
	if (ray_angle > 0 && ray_angle < PI)
		return (true);
	return (false);
}

bool	is_looking_down(int ray_angle)
{
	if (ray_angle > PI && ray_angle < 2 * PI)
		return (true);
	return (false);
}

bool	is_looking_left(int ray_angle)
{
	if (ray_angle > 3 * PI / 2 || ray_angle < PI / 2)
		return (true);
	return (false);
}

bool	is_looking_right(int ray_angle)
{
	if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2)
		return (true);
	return (false);
}

float	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	t_bresenham bresenham;
	int i;

	i = 0;
	bresenham.x = x0;
	bresenham.y = y0;
	bresenham.x1 = x1;
	bresenham.y1 = y1;
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
	bresenham.xinc *= (float)bresenham.dx / bresenham.steps;
	bresenham.yinc *= (float)bresenham.dy / bresenham.steps;
	bresenham.x0 = bresenham.x;
	bresenham.y0 = bresenham.y;
	while (i < bresenham.steps)
	{
		if (data->map[ft_abs(bresenham.x0) / COEF][ft_abs(bresenham.y0) / COEF] == '1')
			return (sqrt(pow(bresenham.x0 - x0, 2) + pow(bresenham.y0 - y0, 2)));
		my_mlx_pixel_put(data, bresenham.x0, bresenham.y0, 0x00FFFFFF);
		bresenham.x0 += bresenham.xinc;
		bresenham.y0 += bresenham.yinc;
		i++;
	}
	return (sqrt(pow(bresenham.x0 - x0, 2) + pow(bresenham.y0 - y0, 2)));
}

float	find_angle()
{
	float rad;

	rad = FOV * PI / 180;
	return (rad / RAYS);
}

bool	wall_face_north(t_data *data, t_ray ray)
{
	if (is_looking_up(ray.ra))
	{
		if (data->map[(int)ray.rx / COEF][(int)ray.ry / COEF] == '1')
			return (true);
	}
	return (false);
}

bool	wall_face_south(t_data *data, t_ray ray)
{
	if (is_looking_down(ray.ra))
	{
		if (data->map[(int)ray.rx / COEF][(int)ray.ry / COEF] == '1')
			return (true);
	}
	return (false);
}

bool	wall_face_east(t_data *data, t_ray ray)
{
	if (is_looking_right(ray.ra))
	{
		if (data->map[(int)ray.rx / COEF][(int)ray.ry / COEF] == '1')
			return (true);
	}
	return (false);
}

bool	wall_face_west(t_data *data, t_ray ray)
{
	if (is_looking_left(ray.ra))
	{
		if (data->map[ft_abs(ray.rx) / COEF][ft_abs(ray.ry) / COEF] == '1')
			return (true);
	}
	return (false);
}

int	find_wall_color(t_data *data, t_ray ray)
{
	if (wall_face_north(data, ray))
		return (0x00FF0000);
	if (wall_face_south(data, ray))
		return (0x0000FF00);
	if (wall_face_east(data, ray))
		return (0x000000FF);
	if (wall_face_west(data, ray))
		return (0x00FF00FF);
	return (0x00FFFFFF);
}

void	parse_rays(t_data *data)
{
	t_ray ray;
	int ray_nbr;
	float ray_angle;
	int color = 0x0000FF00;

	ray.ra = data->player->player_angle;
	ray.dof = 0;
	ray_nbr = 0;
	ray_angle = find_angle();
	while (ray_nbr < RAYS)
	{
		ray.rx = data->player->x * COEF + (COEF / 2);
		ray.ry = data->player->y * COEF + (COEF / 2);
		ray.xo = ray.rx;
		ray.yo = ray.ry;
		ray.rx += RENDER_DISTANCE * cos(ray.ra);
		ray.ry += RENDER_DISTANCE * sin(ray.ra);
		data->ray_len[ray_nbr] = draw_line(ray.xo, ray.yo, ray.rx, ray.ry, data);
		float line_height = HEIGHT * 20 / data->ray_len[ray_nbr];
		float line_start = (WIDTH / 2) - (line_height / 2);
		int i = 0;
		color = find_wall_color(data, ray);
		while (i < line_height)
		{
			int n = -1;
			if (ray_nbr * (WIDTH / RAYS) < WIDTH && i + line_start < HEIGHT)
			{
				while (++n < WIDTH / RAYS)
					my_mlx_pixel_put(data, ray_nbr * (WIDTH / RAYS) + n, i + line_start, color);
			}
			i++;
		}
		ray.ra += ray_angle;
		ray_nbr++;
	}
}

void	print_tab(float *tab)
{
	int i = 0;

	while (i < RAYS)
	{
		printf("Ray[%i] = %f\n", i, tab[i]);
		i++;
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

void	create_image(t_data *data)
{
	int 	i = 0;
	int 	j = 0;

	draw_rectangle(data, 0, 0, HEIGHT, WIDTH / 2, 0x000000aa);
	draw_rectangle(data, 0, WIDTH / 2, HEIGHT, WIDTH / 2, 0x00aa0000);
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (data->map[i][j] == '1')
				draw_square(data, i * COEF, j * COEF, COEF, 0x00FF0000);
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
}

int	float_to_int(float x)
{
	if (x - (int)x > 0.5)
		return ((int)x + 1);
	return ((int)x);

}

bool	forward_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x + 0.20 * cos(data->player->player_angle + ((FOV / 2) * PI / 180)));
	int y = float_to_int(data->player->y + 0.20 * sin(data->player->player_angle + ((FOV / 2) * PI / 180)));

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

bool	backward_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x - (PLAYER_SPEED - 10) * cos(data->player->player_angle + ((FOV / 2) * PI / 180)));
	int y = float_to_int(data->player->y - (PLAYER_SPEED - 10) * sin(data->player->player_angle + ((FOV / 2) * PI / 180)));

	if (data->map[x][y] == '1')
		return (false);
	return (true);
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
		if (forward_is_valid_chunk(data) == true)
		{
			data->player->x += PLAYER_SPEED * cos(data->player->player_angle + ((FOV / 2) * PI / 180));
			data->player->y += PLAYER_SPEED * sin(data->player->player_angle + ((FOV / 2) * PI / 180));
		}
	}
	if (data->move->backward == true)
	{
		if (backward_is_valid_chunk(data) == true)
		{
			data->player->x -= 0.15 * cos(data->player->player_angle + ((FOV / 2) * PI / 180));
			data->player->y -= 0.15 * sin(data->player->player_angle + ((FOV / 2) * PI / 180));
		}
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
	move_player(data);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	create_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	handle_no_event(t_data *data)
{
	(void)data;
	return (0);
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
	data->win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "Cube3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->player->player_angle = PI;
	create_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_loop_hook(data->mlx, handle_no_event, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, &handle_keypressed, data);
	mlx_hook(data->win, KEYREALASE, KEYRELEASEMASK, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	return (0);
}
