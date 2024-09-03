#include "cube3d.h"

bool	door_around(t_data *data, double x, double y)
{
	// return true if there is a door around theses coordinates
}

void	open_door(t_data *data)
{
	if (door_around(data, data->player->x, data->player->y)) {
		write(1, "Door opened\n", 12);
	}
}
