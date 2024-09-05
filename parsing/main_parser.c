#include "cube3d.h"

void	mini_parse(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	int		k;

	data->ceiling_color = 0x404040;
	data->floor_color = 0x5C4033;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	data->map = ft_calloc(600, sizeof(char *));
	while (line)
	{
		j = 0;
		k = 0;
		data->map[i] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		while (line[j])
		{
			if (line[j] == ' ')
				j++;
			else
			{
				data->map[i][k] = line[j];
				j++;
				k++;
			}
		}
		line = get_next_line(fd);
		i++;
	}
	data->mapX = i;
	data->mapY = j;
	print_map(data->map);
}

void	init_textures(t_data *data)
{
	load_texture(data, &data->texture[0], "textures/wall_1.xpm");
	load_texture(data, &data->texture[1], "textures/wall_2.xpm");
	load_texture(data, &data->texture[2], "textures/wall_3.xpm");
	load_texture(data, &data->texture[3], "textures/wall_4.xpm");
	load_texture(data, &data->texture[4], "textures/beam.xpm");
	load_texture(data, &data->texture[5], "textures/door.xpm");
}

int	init_texture(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		while (line[i] && line[i] != ' ')
			i++;
		data->texture[0].path = ft_strdup(line + i);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		while (line[i] && line[i] != ' ')
			i++;
		data->texture[1].path = ft_strdup(line + i);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		while (line[i] && line[i] != ' ')
			i++;
		data->texture[2].path = ft_strdup(line + i);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		while (line[i] && line[i] != ' ')
			i++;
		data->texture[3].path = ft_strdup(line + i);
	}
	else
		return (-1);
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
		return (perror("cube3d: "), -1);
	tmp = get_next_line(fd); // might modify strtrim to free from inside
	line = ft_strtrim(tmp, " \t\n\v\f\r");
	while (line)
	{

	}
}
