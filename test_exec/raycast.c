/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/20 10:49:39 by scrumier         ###   ########.fr       */
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
	(void)data;
	(void)key;
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
void	create_player(t_data *data, int x, int y)
{
	draw_square(data, x * COEF + COEF / 3, y * COEF + COEF / 3, COEF / 3, 0x0000FF00);
}

void	create_image(t_data *data)
{
	int 	i = 0;
	int 	j = 0;
	bool	created_player = false;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			// i want to scale the square by 30
			if (data->map[i][j] == 1)
				draw_square(data, i * COEF, j * COEF, COEF, 0x00FF0000);
			if (data->map[i][j] == 0 && !created_player)
			{
				create_player(data, i, j);
				created_player = true;
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	handle_keypressed(int key, t_data *data)
{
	if (key == XK_Escape)
		return (0);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	create_image(data);
	return (0);
}

int	handle_no_event(t_data *data)
{
	(void)data;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data = NULL;
	data = malloc(sizeof(t_data));

	if (ac != 2)
	{
		printf("Error\n");
		return (0);
	}
	mini_parse(data, av[1]);
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
