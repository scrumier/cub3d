/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:33:03 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/18 10:58:32 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, \
		&texture->width, &texture->height);
	if (texture->img == NULL)
		return (print_error(FAILED_LOAD_TEXTURE), -1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, \
		&texture->line_len, &texture->endian);
	if (texture->addr == NULL)
		return (print_error(FAILED_LOAD_TEXTURE), -1);
	texture->path = ft_strdup(path);
	if (!texture->path)
		return (print_error(FAILED_LOAD_TEXTURE), -1);
	return (0);
}

int	init_walls_texture(t_data *data, char *line, t_texture_enum texture)
{
	char	**sprites;
	size_t	i;

	if (data->texture[texture])
		return (print_error(ALREADY_INIT), 127);
	if (strncmp(line + strlen(line) - 4, ".xpm", 4) != 0)
		return (print_error(INVALID_TEXTURE_FORMAT), 127);
	i = 0;
	sprites = ft_split(line, ' ');
	if (!sprites)
		return (1);
	data->texture[texture] = ft_calloc(strarray_len(sprites) + 1, \
		sizeof(t_texture));
	if (!data->texture[texture])
		return (free_strarray(sprites), 1);
	while (sprites[i])
	{
		if (load_texture(data, &(data->texture[texture][i]), sprites[i]) == -1)
			return (free_strarray(sprites), 1);
		i++;
	}
	return (free_strarray(sprites), 0);
}

int	init_wall(t_data *data, char *line)
{
	if (data->map)
		return (print_error(VALUE_AFTER_MAP), 1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (init_walls_texture(data, line + 3, WALL_NO));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (init_walls_texture(data, line + 3, WALL_SO));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (init_walls_texture(data, line + 3, WALL_WE));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (init_walls_texture(data, line + 3, WALL_EA));
	else if (ft_strncmp(line, "BEAM ", 5) == 0)
		return (init_walls_texture(data, line + 5, BEAM));
	else if (ft_strncmp(line, "DOOR ", 5) == 0)
		return (init_walls_texture(data, line + 5, DOOR));
	else
		return (print_error(IDENTIFIER_NOT_FOUND), 127);
}

size_t	get_max_size(t_llist *list)
{
	size_t	max;
	size_t	len;

	max = 0;
	while (list)
	{
		len = ft_strlen(list->content);
		if (len > max)
			max = len;
		list = list->next;
	}
	return (max);
}
