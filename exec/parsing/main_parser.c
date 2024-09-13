/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:41:33 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/13 05:24:08 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

size_t	strarray_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_strarray(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_llist(t_llist *list)
{
	t_llist	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

void	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (texture->img == NULL)
	{
		printf("Error: Failed to load texture %s\n", path);
		exit(0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	texture->path = ft_strdup(path);
}

char *texture_to_string(e_texture texture)
{
	if (texture == WALL_EA)
		return ("WALL_EA");
	else if (texture == WALL_WE)
		return ("WALL_WE");
	else if (texture == WALL_SO)
		return ("WALL_SO");
	else if (texture == WALL_NO)
		return ("WALL_NO");
	else if (texture == BEAM)
		return ("BEAM");
	else if (texture == DOOR)
		return ("DOOR");
	else
		return ("UNKNOWN");
}

int	init_walls_texture(t_data *data, char *line, e_texture texture)
{
	char	**sprites;
	size_t	i;

	if (data->texture[texture])
		return (127); // TODO: print texture already initialized
	i = 0;
	while (line[i] == ' ')
		i++;
	sprites = ft_split(line, ' ');
	if (!sprites)
		return (-1);
	data->texture[texture] = ft_calloc(strarray_len(sprites) + 1, sizeof(t_texture));
	if (!data->texture[texture])
		return (free_strarray(sprites), -1);
	while (sprites[i])
	{
		load_texture(data, &(data->texture[texture][i]), sprites[i]); // TODO: check return for invalid path
		i++;
	}
	return (free_strarray(sprites), 0);
}
int	init_wall(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_NO));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_SO));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_WE));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return(init_walls_texture(data, line + 3, WALL_EA));
	else if (ft_strncmp(line, "BEAM ", 5) == 0)
		return(init_walls_texture(data, line + 5, BEAM));
	else if (ft_strncmp(line, "DOOR ", 5) == 0)
		return(init_walls_texture(data, line + 5, DOOR));
	else
		return (127); // TODO: print identifier not found
}

int	init_colors(t_data *data, char *line, e_texture type)
{
	int		rgb[3];
	size_t	i;
	size_t	start;
	size_t	color;

	i = 0;
	color = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (22); // TODO: print invalid arg
	start = i;
	while (line[i])
	{
		if (line[i] == ',' && color == 2)
			return (22); // TODO: print invalid arg
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (22); // TODO: print invalid arg
		if (line[i] == ',' || !line[i + 1])
		{
			if (i == start && line[i + 1])
				return (22); // TODO: print invalid arg
			rgb[color] = ft_atoi(line + start);
			if (rgb[color] < 0 || rgb[color] > 255)
				return (22); // TODO: print invalid arg
			color++;
			start = i + 1;
		}
		i++;
	}
	if (type == CEILING)
		data->ceiling_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	else
		data->floor_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (0);
}

void free_texture(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (data->texture[i][j].path)
		{
			free(data->texture[i][j].path);
			mlx_destroy_image(data->mlx, data->texture[i][j].img);
			j++;
		}
		free(data->texture[i]);
		i++;
	}
}

char	*ft_strndup(const char *s, size_t n)
{
    char	*dup;
    size_t	i;

    dup = (char *)malloc((n + 1) * sizeof(char));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
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

char	*add_spaces(char *str, size_t amount)
{
	char	*tmp;
	size_t	i;

	i = ft_strlen(str);
	tmp = ft_calloc(i + amount + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, str, i + 1);
	while (amount--)
		tmp[i++] = '*';
	return (tmp);
}

void	padding_map(t_data *data, t_llist *map) // TODO: optimize by putting the space only where needed
{
	size_t	i;
	t_llist	*tmp;
	char	**padded_map;

	data->mapX = get_max_size(map);
	padded_map = ft_calloc(data->mapY + 1, sizeof(char *));
	i = 0;
	tmp = map;
	while (tmp)
	{
		padded_map[i] = add_spaces(tmp->content, data->mapX - ft_strlen(tmp->content)); //TODO: check return
		tmp = tmp->next;
		i++;
	}
	data->map = padded_map;
}

void	parse_map(t_data *data, char *line, int fd)
{
	// TODO : protect mallocs
	t_llist	*map;
	t_llist	*last;
	size_t	len;

	map = NULL;
	last = NULL;
	data->mapY = 0;
	while (line && line[0] != '\n')
	{
		if (!map)
		{
			map = ft_calloc(1, sizeof(t_llist));
			map->content = ft_strndup(line, ft_strlen(line) - 1);
			last = map;
		}
		else
		{
			last->next = ft_calloc(1, sizeof(t_llist));
			last = last->next;
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				last->content = ft_strndup(line, len - 1);
			else
				last->content = ft_strdup(line);
		}
		data->mapY++;
		free(line);
		line = get_next_line(fd);
	}
	padding_map(data, map);
	//print data->map
	free_llist(map);
	size_t i = 0;
	while (i < data->mapY)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

int	parse(t_data *data, char *file)
{
	int		fd;
	char	*line;
	char	*tmp;
	size_t	i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("cube3d: "), -1); // Error\n ?
	tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
	line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	while (line)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			printf("%d\n", init_colors(data, line + 2, CEILING));
		else if (ft_strncmp(line, "F ", 2) == 0)
			printf("%d\n", init_colors(data, line + 2, FLOOR));
		else if (line[0] == '1' || line[0] == '0')
		{
			parse_map(data, tmp, fd);
			free(line);
			break;
		}
		else
			init_wall(data, line);
		free(tmp);
		free(line);
		tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
		line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	}
	// check if all data is present and if there isn't any redefinition after map
	
	printf("ceiling: %x\nfloor: %x\n", data->ceiling_color, data->floor_color);
	//print every texture path
	i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		printf("Texture %s\n", texture_to_string((e_texture)i));
		while (data->texture[i][j].path)
		{
			printf("%s\n", data->texture[i][j].path);
			j++;
		}
		i++;
	}
	
	return (close(fd), 0);
}

/*
check if nothing after map
check if 1 letter in map
*/
