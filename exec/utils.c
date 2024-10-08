/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:36:06 by scrumier          #+#    #+#             */
/*   Updated: 2024/09/18 10:13:02 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	deg_to_rad(int deg)
{
	return (deg * PI / 180);
}

double	find_angle(int total_rays)
{
	double	rad;

	rad = FOV * PI / 180;
	return (rad / total_rays);
}

double	ft_dabs(double d)
{
	if (d < 0)
		d = -d;
	return (d);
}

int	double_to_int(double x)
{
	if (x - (int)x >= 0.4)
		return ((int)x + 1);
	return ((int)x);
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
