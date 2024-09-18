/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:21:04 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/18 10:18:05 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_mlx_image(t_data *data, t_img *img)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
}

void	free_all(t_data *data)
{
	free_texture(data);
	free_mlx_image(data, &data->img);
	free(data->player);
	free(data->move);
	free_strarray(data->map);
	free(data->mlx);
	free(data);
}

void	free_parse(t_data *data)
{
	free_texture(data);
	free(data->player);
	free(data->move);
	free_strarray(data->map);
	free(data->mlx);
	free(data);
}

int	free_exit(t_data *data)
{
	free_all(data);
	exit(0);
}
