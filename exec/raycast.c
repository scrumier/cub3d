/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/16 11:29:25 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_rectangle(t_data *data, int x, int y, int height, int width, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
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

bool is_valid_texture(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->texture[i] != NULL)
	{
		j = 0;
		if (data->texture[i][j].addr == NULL)
			return (false);
		i++;
	}
	return (true);
}
int create_image(t_data *data)
{
	int i;
	int j;

	i = 0;

	data->next_image++;
	if (data->next_image == 10) {
		data->next_image = 0;
		data->animated_texture_index++;
	}
	gettimeofday(&data->current_time, NULL);
	double elapsed_time = (data->current_time.tv_sec - data->last_time.tv_sec) +
						  (data->current_time.tv_usec - data->last_time.tv_usec) / 1000000.0;
	data->fps = 1.0 / elapsed_time;
	data->last_time = data->current_time;
	move_player(data);
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
/* TODO : fix type
void	init_textures(t_data *data)
{
	load_texture(data, &data->texture[0][0], "textures/cobble-animated-1.xpm");
	load_texture(data, &data->texture[0][1], "textures/cobble-animated-2.xpm");
	load_texture(data, &data->texture[0][2], "textures/cobble-animated-3.xpm");
	load_texture(data, &data->texture[0][3], "textures/cobble-animated-4.xpm");
	load_texture(data, &data->texture[1][0], "textures/cobble-animated-1.xpm");
	load_texture(data, &data->texture[1][1], "textures/cobble-animated-2.xpm");
	load_texture(data, &data->texture[1][2], "textures/cobble-animated-3.xpm");
	load_texture(data, &data->texture[1][3], "textures/cobble-animated-4.xpm");
	load_texture(data, &data->texture[2][0], "textures/cobble-animated-1.xpm");
	load_texture(data, &data->texture[2][1], "textures/cobble-animated-2.xpm");
	load_texture(data, &data->texture[2][2], "textures/cobble-animated-3.xpm");
	load_texture(data, &data->texture[2][3], "textures/cobble-animated-4.xpm");
	load_texture(data, &data->texture[3][0], "textures/cobble-animated-1.xpm");
	load_texture(data, &data->texture[3][1], "textures/cobble-animated-2.xpm");
	load_texture(data, &data->texture[3][2], "textures/cobble-animated-3.xpm");
	load_texture(data, &data->texture[3][3], "textures/cobble-animated-4.xpm");
	load_texture(data, &data->texture[4][0], "textures/beam.xpm");
	load_texture(data, &data->texture[5][0], "textures/door_animated-1.xpm");
	load_texture(data, &data->texture[5][1], "textures/door_animated-2.xpm");
	load_texture(data, &data->texture[5][2], "textures/door_animated-3.xpm");
	load_texture(data, &data->texture[5][3], "textures/door_animated-4.xpm");
}
*/

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (printf("Error\n"), 0);
	data = malloc(sizeof(t_data));
	data->player = malloc(sizeof(t_player));
	data->player->x = 0;
	data->player->y = 0;
	data->move = malloc(sizeof(t_move));
	data->flash_light = false;
	data->animated_texture_index = 0;
	data->created_player = false;
	data->mlx = mlx_init();
	data->map = NULL;
	data->ceiling_color = -1;
	data->floor_color = -1;
	data->texture[0] = NULL;
	data->texture[1] = NULL;
	data->texture[2] = NULL;
	data->texture[3] = NULL;
	data->texture[4] = NULL;
	data->texture[5] = NULL;
	parse(data, av[1]);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);

	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, &handle_keypressed, data);
	mlx_hook(data->win, KEYREALASE, KEYRELEASEMASK, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	free(data->player);
	free(data->move);
	free(data->mlx);
	free(data);
	return (0);
}