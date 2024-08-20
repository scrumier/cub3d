/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/20 16:49:47 by scrumier         ###   ########.fr       */
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

void	print_map(int map[10][10])
{
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			printf("%d", map[i][j]);
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

	while (line)
	{
		j = 0;
		k = 0;
		while (line[j])
		{
			data->map[i][j] = line[k] - '0';
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
	if (key == XK_Up)
	{
		data->move->up = false;
	}
	if (key == XK_Down)
	{
		data->move->down = false;
	}
	if (key == XK_Left)
	{
		data->move->left = false;
	}
	if (key == XK_Right)
	{
		data->move->right = false;
	}
	return (0);
}

void draw_square(t_data *data, int x, int y, int coef, int color)
{
	int i = 0;
	int j = 0;

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

// i want the player to be a little square in the middle of the square
// it will be green
void	draw_player(t_data *data)
{
	draw_square(data, data->player->x * COEF + (COEF / 2) - (PLAYER_SIZE / 2), data->player->y * COEF + (COEF / 2) - (PLAYER_SIZE / 2), PLAYER_SIZE, 0x0000FF00);
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
			// i want to scale the square by 30
			if (data->map[i][j] == 1)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00FF0000);
			if (data->map[i][j] == 0 && !data->created_player)
			{
				data->player->x = i;
				data->player->y = j;
				draw_player(data);
				data->created_player = true;
			}
			if (data->map[i][j] == 0 && data->created_player)
				draw_player(data);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	float_to_int(float x)
{
	// i want if the number is 1.2 to return 2
	// if the number is 1.6 to return 2
	// if the number is 1.5 to return 2

	if (x - (int)x > 0.5)
		return ((int)x + 1);
	return ((int)x);

}

bool	up_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x);
	int y = float_to_int(data->player->y - 0.2);

	if (data->map[x][y] == 1)
		return (false);
	return (true);
}

bool	down_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x);
	int y = float_to_int(data->player->y + 0.2);

	if (data->map[x][y] == 1)
		return (false);
	return (true);
}

bool	left_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x - 0.2);
	int y = float_to_int(data->player->y);

	if (data->map[x][y] == 1)
		return (false);
	return (true);
}

bool	right_is_valid_chunk(t_data *data)
{
	int x = float_to_int(data->player->x + 0.3);
	int y = float_to_int(data->player->y);

	if (data->map[x	][y] == 1)
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
			data->player->y -= 0.1;
	}
	if (data->move->down == true)
	{
		if (down_is_valid_chunk(data) == true)
			data->player->y += 0.1;
	}
	if (data->move->left == true)
	{
		if (left_is_valid_chunk(data) == true)
			data->player->x -= 0.1;
	}
	if (data->move->right == true)
	{
		if (right_is_valid_chunk(data) == true)
			data->player->x += 0.1;
	}
}

int	handle_keypressed(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (key == XK_Up)
	{
		data->move->up = true;
	}
	if (key == XK_Down)
	{
		data->move->down = true;
	}
	if (key == XK_Left)
	{
		data->move->left = true;
	}
	if (key == XK_Right)
	{
		data->move->right = true;
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
	create_image(data);
	mlx_loop_hook(data->mlx, handle_no_event, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_keypressed, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	mlx_destroy_display(data->mlx);
	return (0);
}
