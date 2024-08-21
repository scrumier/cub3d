/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/21 18:11:54 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

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
		data->move->up = false;
	}
	if (key == KEY_S)
	{
		data->move->down = false;
	}
	if (key == KEY_A)
	{
		data->move->left = false;
	}
	if (key == KEY_D)
	{
		data->move->right = false;
	}
	if (key == KEY_LEFT)
	{
		data->move->turn_left = false;
	}
	if (key == KEY_RIGHT)
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
			//my_mlx_pixel_put(data, x + i, y + j, color);
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

bool	is_looking_up(t_data *data)
{
	if (data->player->player_angle > 0 && data->player->player_angle < PI)
		return (true);
	return (false);
}

bool	is_looking_down(t_data *data)
{
	if (data->player->player_angle > PI && data->player->player_angle < 2 * PI)
		return (true);
	return (false);
}

bool	is_looking_left(t_data *data)
{
	if (data->player->player_angle > 3 * PI / 2 || data->player->player_angle < PI / 2)
		return (true);
	return (false);
}

bool	is_looking_right(t_data *data)
{
	if (data->player->player_angle > PI / 2 && data->player->player_angle < 3 * PI / 2)
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
		//my_mlx_pixel_put(data, bresenham.x0, bresenham.y0, 0x00FFFFFF);
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

void	parse_rays(t_data *data)
{
	t_ray ray;
	int ray_nbr;
	float ray_angle;
	
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
		data->ray_len[ray_nbr] = draw_line(ray.xo, ray.yo, ray.rx, ray.ry, data)
		float line_height = HEIGHT * 20 / data->ray_len[ray_nbr];
		float line_start = (WIDTH / 2) - (line_height / 2);
		int i = 0;
		while (i < line_height)
		{
			if (ray_nbr * (WIDTH / RAYS) < WIDTH && i + line_start < HEIGHT)
				my_mlx_pixel_put(data, ray_nbr * (WIDTH / RAYS), i + line_start, 0x00FFFFFF);
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
	//draw_square(data, data->player->x * COEF + (COEF / 2) - (PLAYER_SIZE / 2), data->player->y * COEF + (COEF / 2) - (PLAYER_SIZE / 2), PLAYER_SIZE, 0x0000FF00);
	parse_rays(data);
}

void	create_image(t_data *data)
{
	int 	i = 0;
	int 	j = 0;

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

bool	up_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x);
	int y = float_to_int(data->player->y - 0.15);

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

bool	down_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x);
	int y = float_to_int(data->player->y + 0.15);

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

bool	left_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x - 0.15);
	int y = float_to_int(data->player->y);

	if (data->map[x][y] == '1')
		return (false);
	return (true);
}

bool	right_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x + 0.15);
	int y = float_to_int(data->player->y);

	if (data->map[x	][y] == '1')
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
	if (data->move->up == true)
	{
		if (up_is_valid_chunk(data) == true)
			data->player->y -= PLAYER_SPEED;
	}
	if (data->move->down == true)
	{
		if (down_is_valid_chunk(data) == true)
			data->player->y += PLAYER_SPEED;
	}
	if (data->move->left == true)
	{
		if (left_is_valid_chunk(data) == true)
			data->player->x -= PLAYER_SPEED;
	}
	if (data->move->right == true)
	{
		if (right_is_valid_chunk(data) == true)
			data->player->x += PLAYER_SPEED;
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
		data->move->up = true;
	}
	if (key == KEY_S)
	{
		data->move->down = true;
	}
	if (key == KEY_A)
	{
		data->move->left = true;
	}
	if (key == KEY_D)
	{
		data->move->right = true;
	}
	if (key == KEY_LEFT)
	{
		data->move->turn_left = true;
	}
	if (key == KEY_RIGHT)
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
