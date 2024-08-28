/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/27 13:41:11 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	if (data->created_player == false)
	{
		while (i < data->mapX)
		{
			j = 0;
			while (j < data->mapY)
			{
				if (data->map[i][j] == '0' && !data->created_player) {
					data->player->x = i;
					data->player->y = j;
					parse_rays(data);
					data->created_player = true;
					break ;
				}
				if (data->map[i][j] == '0' && data->created_player)
				{
					parse_rays(data);
					break ;
				}
				j++;
			}
			i++;
		}
	}
	else
		parse_rays(data);
	print_minimap(data, 2);
	data->last_fps[data->frame % FPS] = data->fps;
	data->frame++;

	char fps_str[20];
	char lowest_fps_str[20];
	char highest_fps_str[20];
	char *tmp = ft_itoa((int)get_fps_average(data));
	ft_strlcpy(fps_str, "FPS: ", 6);
	ft_strlcat(fps_str, tmp, 20);
	free(tmp);
	tmp = ft_itoa(find_lowest_value(data->last_fps, FPS));
	ft_strlcpy(lowest_fps_str, "Lowest FPS: ", 13);
	ft_strlcat(lowest_fps_str, tmp, 20);
	free(tmp);
	tmp = ft_itoa(find_highest_value(data->last_fps, FPS));
	ft_strlcpy(highest_fps_str, "Highest FPS: ", 14);
	ft_strlcat(highest_fps_str, tmp, 20);
	free(tmp);
	if (FXAA_ENABLED == true)
		apply_custom_antialiasing(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_string_put(data->mlx, data->win, WIDTH - 125, 30, 0xFFFFFF, lowest_fps_str);
	mlx_string_put(data->mlx, data->win, WIDTH - 130, 50, 0xFFFFFF, highest_fps_str);
	mlx_string_put(data->mlx, data->win, WIDTH - 75, 10, 0xFFFFFF, fps_str);
	return (0);
}

int mouse_hook(int button, t_data *data)
{
	// handle if he mouse move to the right or to the left
	if (button == 4)
	{
		data->move->turn_left = false;
		data->move->turn_right = true;
	}
	else if (button == 5)
	{
		data->move->turn_left = true;
		data->move->turn_right = false;
	}
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
	data->flash_light = false;
	data->created_player = false;
	line = ft_strdup(av[1]);
	mini_parse(data, line);
	data->ceiling_color = 0x000000FF;
	data->floor_color = 0x00A52A2A;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->player->player_angle = (FOV / 2) * PI / 180;
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, &handle_keypressed, data);
	mlx_hook(data->win, MOUSEMOVE, MOUSEMOVEMASK, &mouse_hook, data);
	mlx_hook(data->win, KEYREALASE, KEYRELEASEMASK, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	return (0);
}
