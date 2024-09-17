/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/16 14:46:12 by scrumier         ###   ########.fr       */
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
	move_player(data);
	parse_rays(data);
	print_minimap(data, 2);

	if (FXAA_ENABLED == true)
		apply_custom_antialiasing(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
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

void init_all(t_data *data)
{
	data->move->forward = false;
	data->move->backward = false;
	data->move->go_left = false;
	data->move->go_right = false;
	data->move->turn_left = false;
	data->move->turn_right = false;
}

void	free_all(t_data *data)
{
	free_texture(data);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->player);
	free(data->move);
	free_strarray(data->map);
	free(data->mlx);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (printf("Error\n"), 0);
	data = malloc(sizeof(t_data));
	data->player = malloc(sizeof(t_player));
	data->player->x = -1;
	data->player->y = -1;
	data->next_image = 0;
	data->move = malloc(sizeof(t_move));
	data->flash_light = false;
	data->animated_texture_index = 0;
	data->created_player = false;
	data->map = NULL;
	data->ceiling_color = -1;
	data->floor_color = -1;
	data->texture[0] = NULL;
	data->texture[1] = NULL;
	data->texture[2] = NULL;
	data->texture[3] = NULL;
	data->texture[4] = NULL;
	data->texture[5] = NULL;
	data->mlx = mlx_init();
	init_all(data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	if (parse(data, av[1]))
		return (free_all(data), 0);
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, &handle_keypressed, data);
	mlx_hook(data->win, KEYREALASE, KEYRELEASEMASK, &handle_keyrelease, data);
	mlx_loop(data->mlx);
	free(data->player);
	free(data->move);
	free(data->mlx);
	free_strarray(data->map);
	free_texture(data);
	free(data);
	return (0);
}