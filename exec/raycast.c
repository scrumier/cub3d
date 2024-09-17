/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:16:58 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/17 16:28:55 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_valid_texture(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->texture[i] != NULL)
	{
		j = 0;
		if (data->texture[i][j].addr == NULL)
			return (false);
		i++;
	}
	return (true);
}

int	create_image(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->next_image++;
	if (data->next_image == 10)
	{
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

int	mouse_hook(int button, t_data *data)
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

void	init_all(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	data->player->x = -1;
	data->player->y = -1;
	data->next_image = 0;
	data->move = malloc(sizeof(t_move));
	data->move->forward = false;
	data->move->backward = false;
	data->move->go_left = false;
	data->move->go_right = false;
	data->move->turn_left = false;
	data->move->turn_right = false;
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
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (printf("Error\n"), 0);
	data = malloc(sizeof(t_data));
	init_all(data);
	data->mlx = mlx_init();
	if (parse(data, av[1]))
		return (free_parse(data), 0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, \
						&data->img.line_len, &data->img.endian);
	mlx_loop_hook(data->mlx, create_image, data);
	mlx_hook(data->win, KEYPRESS, 1L << 0, &handle_keypressed, data);
	mlx_hook(data->win, KEYREALASE, 1L << 1, &handle_keyrelease, data);
	mlx_hook(data->win, DESTROYNOTIFY, 1L << 17, &free_exit, data);
	mlx_loop(data->mlx);
	free(data->player);
	free(data->move);
	free(data->mlx);
	free_strarray(data->map);
	free_texture(data);
	free(data);
	return (0);
}
