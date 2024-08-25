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
	int j;
	int k;
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
		data->move->forward = false;
	if (key == KEY_S)
		data->move->backward = false;
	if (key == KEY_A)
		data->move->turn_left = false;
	if (key == KEY_D)
		data->move->turn_right = false;
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

double find_cube_center(double x)
{
	int i = 0;

	while (i < 10)
	{
		if (x >= i && x < i + 1)
			return (i + 0.5);
		i++;
	}
	return (0);
}

double get_fractional_part(double number)
{
	int integer_part;
	double fractional_part;

	integer_part = (int)number;
	fractional_part = number - (double)integer_part;
	return (fractional_part);
}

double	ft_dabs(double d)
{
	if (d < 0)
		d = -d;
	return (d);
}

int find_closest_to_05(double x, double y)
{
	// this function find if (x, -x) or (y, -y) is the closest to 0.5
	double delta_x = ft_dabs(x - 0.5);
	double delta_y = ft_dabs(y - 0.5);

	if (delta_x < delta_y)
		return (0);
	return (1);
}

int	find_wall_facing(t_data *data, t_ray *ray)
{
	(void)data;
	double x = ray->dstx;
	double y = ray->dsty;
	double x_center = find_cube_center(x);
	double y_center = find_cube_center(y);
	double x_fractional = get_fractional_part(x);
	double y_fractional = get_fractional_part(y);
	int face = 0;

	if (x_fractional < y_fractional)
	{
		if (x_center < x)
			face = 'w';
		else if (x_center > x)
			face = 'e';
	}
	else if (x_fractional > y_fractional)
	{
		if (y_center < y)
			face = 'n';
		else if (y_center > y)
			face = 's';
	}
	else
		face = 0;
	return (face);
}

int	find_ray_color(t_data *data, t_ray *ray)
{
	int face = find_wall_facing(data, ray);

	if (face == 'n') // purple
		return (0x00FF00FF);
	else if (face == 's') // red
		return (0x00FF0033);
	else if (face == 'e') // blue
		return (0x007777FF);
	else if (face == 'w') // green
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
	bresenham.dx = ft_dabs(bresenham.dx);
	bresenham.dy = ft_dabs(bresenham.dy);
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
		if (data->map[ft_abs((int)bresenham.x0) / COEF][ft_abs((int)bresenham.y0) / COEF] == '1')
		{
			// move 1 pixel more to get the exact position of the wall
			bresenham.x0 += bresenham.xinc / WALL_ACCURACY;
			bresenham.y0 += bresenham.yinc / WALL_ACCURACY;
			ray->dstx = bresenham.x0 / COEF;
			ray->dsty = bresenham.y0 / COEF;
			return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->yo, 2)));
		}
		if (mode == 1)
		{
			my_mlx_pixel_put(data, (int)bresenham.x0, (int)bresenham.y0, 0x00FFFFFF);
		}
		bresenham.x0 += bresenham.xinc / WALL_ACCURACY;
		bresenham.y0 += bresenham.yinc / WALL_ACCURACY;
		i++;
	}
	ray->dstx = bresenham.x0 / COEF;
	ray->dsty = bresenham.y0 / COEF;
	return (sqrt(pow(bresenham.x0 - ray->xo, 2) + pow(bresenham.y0 - ray->ry, 2)));
}

double	find_angle(int total_rays)
{
	double rad;

	rad = FOV * PI / 180;
	return (rad / total_rays);
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

double get_fps_average(t_data *data)
{
	int i = 0;
	double sum = 0;

	while (i < FPS)
	{
		sum += data->last_fps[i];
		i++;
	}
	return (sum / FPS);
}

int	optimize_fps(double last_fps)
{
	if (FPS_OPTI == 1)
	{
		if (last_fps < 20)
			return (RAYS / 8);
		else if (last_fps < 40)
			return (RAYS / 4);
		else if (last_fps < 60)
			return (RAYS);
		else
			return (RAYS * 2);
	}
	else if (FPS_OPTI == 2)
	{
		if (last_fps < 20)
			return (RAYS / 4);
		else if (last_fps < 40)
			return (RAYS / 2);
		else
			return (RAYS);
	}
	return (RAYS);
}

void	parse_rays(t_data *data)
{
	t_ray ray;
	int ray_nbr;
	double ray_angle;
	int total_rays;

	ray.ra = data->player->player_angle - (FOV / 2) * PI / 180;
	ray.dof = 0;
	ray_nbr = 0;
	total_rays = RAYS;
	double last_fps = get_fps_average(data);
	if (FPS_OPTI != 0)
		total_rays = optimize_fps(last_fps);
	ray_angle = find_angle(total_rays);
	print_minimap(data, 1);
	draw_square(data, data->player->x * COEF + (COEF / 2) - (PLAYER_SIZE / 2), data->player->y * COEF + (COEF / 2) - (PLAYER_SIZE / 2), PLAYER_SIZE, 0x0000FF00);
	while (ray_nbr < total_rays)
	{
		ray.rx = data->player->x * COEF + (COEF / 2);
		ray.ry = data->player->y * COEF + (COEF / 2);
		ray.xo = ray.rx + 1;
		ray.yo = ray.ry + 1;
		ray.rx += RENDER_DISTANCE * cos(ray.ra);
		ray.ry += RENDER_DISTANCE * sin(ray.ra);
		//remove fish eye effect
		double corrected_angle = ray.ra - data->player->player_angle;
		if (corrected_angle < 0)
			corrected_angle += 2 * PI;
		if (corrected_angle > 2 * PI)
			corrected_angle -= 2 * PI;
		data->ray_len[ray_nbr] = draw_line(&ray, data, 1);
		data->ray_len[ray_nbr] *= cos(corrected_angle);  // Correct the fish-eye effect
		double line_height = HEIGHT * COEF3D / data->ray_len[ray_nbr];
		double line_start = (WIDTH / 2) - (line_height / 2);
		int i = 0;
		ray.color = find_ray_color(data, &ray);
		while (i < line_height)
		{
			if (ray_nbr * (double)(WIDTH / total_rays) < WIDTH && i + line_start < HEIGHT)
			{
				int n = -1;
				while (++n < (double)(WIDTH / total_rays)) {
					// i dont want to print if i am on the area of the minimap
					if (!(n + ray_nbr * (double)(WIDTH / total_rays) < 150 && i + line_start < 150))
						my_mlx_pixel_put(data, ray_nbr * (double) (WIDTH / total_rays) + n, i + line_start, ray.color);
				}
			}
			i++;
		}
		ray.ra += ray_angle;
		ray_nbr++;
	}
}

void	draw_player(t_data *data)
{
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
		data->player->x += PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y += PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->backward == true)
	{
		data->player->x -= PLAYER_SPEED * cos(data->player->player_angle);
		data->player->y -= PLAYER_SPEED * sin(data->player->player_angle);
	}
	if (data->move->turn_left == true)
	{
		data->player->player_angle = (data->player->player_angle - PI / 30);
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);
	}
	if (data->move->turn_right == true)
	{
		data->player->player_angle = (data->player->player_angle + PI / 30);
		data->player->pdx = PLAYER_ROTATE * cos(data->player->player_angle);
		data->player->pdy = PLAYER_ROTATE * sin(data->player->player_angle);

	}
}

double find_lowest_value(double *tab, int size)
{
	int i = 0;
	double lowest = tab[0];

	while (i < size)
	{
		if (tab[i] < lowest)
			lowest = tab[i];
		i++;
	}
	return (lowest);
}

double find_highest_value(double *tab, int size)
{
	int i = 0;
	double highest = tab[0];

	while (i < size)
	{
		if (tab[i] > highest)
			highest = tab[i];
		i++;
	}
	return (highest);
}

// Helper function to blend colors of neighboring pixels
unsigned int blend_colors(unsigned int color, unsigned int color_left, unsigned int color_right, unsigned int color_up, unsigned int color_down)
{
	int r = 0, g = 0, b = 0;

	r += (color >> 16) & 0xFF;
	g += (color >> 8) & 0xFF;
	b += color & 0xFF;

	r += (color_left >> 16) & 0xFF;
	g += (color_left >> 8) & 0xFF;
	b += color_left & 0xFF;

	r += (color_right >> 16) & 0xFF;
	g += (color_right >> 8) & 0xFF;
	b += color_right & 0xFF;

	r += (color_up >> 16) & 0xFF;
	g += (color_up >> 8) & 0xFF;
	b += color_up & 0xFF;

	r += (color_down >> 16) & 0xFF;
	g += (color_down >> 8) & 0xFF;
	b += color_down & 0xFF;

	// Average the colors
	r /= 5;
	g /= 5;
	b /= 5;

	return (r << 16) | (g << 8) | b;
}

// Helper function to retrieve the pixel color at a specific location
unsigned int get_pixel_color(t_data *data, int x, int y)
{
	char *dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	return *(unsigned int *)dst;
}

// Helper function to set the pixel color at a specific location
void set_pixel_color(t_data *data, int x, int y, unsigned int color)
{
	char *dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

// Helper function to determine if there is a significant color difference between pixels
int color_difference(unsigned int color1, unsigned int color2)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	return abs(r1 - r2) + abs(g1 - g2) + abs(b1 - b2);
}

void apply_custom_antialiasing(t_data *data)
{
	for (int y = 1; y < HEIGHT - 1; y++) {
		for (int x = 1; x < WIDTH - 1; x++) {
			unsigned int color = get_pixel_color(data, x, y);

			unsigned int color_left = get_pixel_color(data, x - 1, y);
			unsigned int color_right = get_pixel_color(data, x + 1, y);
			unsigned int color_up = get_pixel_color(data, x, y - 1);
			unsigned int color_down = get_pixel_color(data, x, y + 1);

			// Determine if the current pixel is part of an edge by checking color difference
			if (color_difference(color, color_left) > THRESHOLD ||
				color_difference(color, color_right) > THRESHOLD ||
				color_difference(color, color_up) > THRESHOLD ||
				color_difference(color, color_down) > THRESHOLD) {

				// Blend the colors to smooth the edge
				unsigned int blended_color = blend_colors(color, color_left, color_right, color_up, color_down);
				set_pixel_color(data, x, y, blended_color);
			}
		}
	}
}

int create_image(t_data *data)
{
	int i = 0;
	int j;

	gettimeofday(&data->current_time, NULL);
	double elapsed_time = (data->current_time.tv_sec - data->last_time.tv_sec) +
						  (data->current_time.tv_usec - data->last_time.tv_usec) / 1000000.0;
	data->fps = 1.0 / elapsed_time;
	data->last_time = data->current_time;
	move_player(data);
	if (data->player->x < 0 || data->player->x > 9 || data->player->y < 0 || data->player->y > 9 ||
		data->map[double_to_int(data->player->x)][double_to_int(data->player->y)] == '1') {
		data->created_player = false;
	}
	draw_rectangle(data, 0, 0, HEIGHT, WIDTH / 2, 0x000000aa);
	draw_rectangle(data, 0, WIDTH / 2, HEIGHT, WIDTH / 2, 0x00aa0000);
	while (i < 10) {
		j = 0;
		while (j < 10) {
			if (data->map[i][j] == '0' && !data->created_player) {
				data->player->x = i;
				data->player->y = j;
				draw_player(data);
				data->created_player = true;
			}
			if (data->map[i][j] == '0' && data->created_player) {
				draw_player(data);
			}
			j++;
		}
		i++;
	}

	print_minimap(data, 2);

	data->last_fps[data->frame % FPS] = data->fps;
	data->frame++;

	char fps_str[20];
	char lowest_fps_str[20];
	char highest_fps_str[20];
	snprintf(lowest_fps_str, sizeof(lowest_fps_str), "Lowest FPS: %.2f", find_lowest_value(data->last_fps, FPS));
	snprintf(highest_fps_str, sizeof(highest_fps_str), "Highest FPS: %.2f", find_highest_value(data->last_fps, FPS));
	snprintf(fps_str, sizeof(fps_str), "FPS: %.2f", data->fps);
	if (FXAA_ENABLED == true)
		apply_custom_antialiasing(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_string_put(data->mlx, data->win, WIDTH - 125, 30, 0xFFFFFF, lowest_fps_str);
	mlx_string_put(data->mlx, data->win, WIDTH - 130, 50, 0xFFFFFF, highest_fps_str);
	mlx_string_put(data->mlx, data->win, WIDTH - 75, 10, 0xFFFFFF, fps_str);
	return (0);
}



int	handle_keypressed(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (key == KEY_W)
		data->move->forward = true;
	if (key == KEY_S)
		data->move->backward = true;
	if (key == KEY_A)
		data->move->turn_left = true;
	if (key == KEY_D)
		data->move->turn_right = true;
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
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->player->player_angle = (FOV / 2) * PI / 180;
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, &handle_keypressed, data);
	mlx_hook(data->win, KEYREALASE, KEYRELEASEMASK, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	return (0);
}
