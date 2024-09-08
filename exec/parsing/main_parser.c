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

void	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (texture->img == NULL)
	{
		printf("Error: Failed to load texture %s\n", path);
		exit(0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
}

int	init_walls_texture(t_parsedata *data, char *line, e_texture texture)
{
	char	**sprites;
	size_t	i;

	i = 0;
	sprites = ft_split(line, ' ');
	if (!sprites)
		return (-1);
	data->texture[texture] = ft_calloc(strarray_len(sprites), sizeof(t_texture));
	if (!data->texture[texture])
		return (free_strarray(sprites), -1);
	while (sprites[i])
	{
		//load_texture(data, &data->texture[texture], sprites[i]);
		i++;
	}
	return (free_strarray(sprites), 0);
}
int	init_wall(t_parsedata *data, char *line)
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

int	init_colors(t_parsedata *data, char *line, e_texture type)
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

int	parse(t_parsedata *data, char *file)
{
	int		fd;
	char	*line;
	char	*tmp;
	size_t	i;
	int		ret;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("cube3d: "), -1);
	tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
	line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	while (line)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			printf("%d\n", init_colors(data, line + 2, CEILING));
		else if (ft_strncmp(line, "F ", 2) == 0)
			printf("%d\n", init_colors(data, line + 2, FLOOR));
		//elseif (ft_isdigit(line[0]))
		//else
		//	init_wall(data, line);
		free(tmp);
		free(line);
		tmp = get_next_line(fd); // might modify strtrim to free from inside + TODO: check function's return
		line = ft_strtrim(tmp, " \t\n\v\f\r"); //TODO: check function's return
	}
	// print ceiling and floor colors
	printf("ceiling: %x\nfloor: %x\n", data->ceiling_color, data->floor_color);
}
