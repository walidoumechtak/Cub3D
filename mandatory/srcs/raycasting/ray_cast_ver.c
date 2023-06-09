/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_ver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:10:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/06/24 13:34:57 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	check_wall(t_cub *cub)
{
	if (cub->map[(int)(cub->pv_inter_y / CARRE)][(int)(cub->pv_inter_x
			/ CARRE)] == '1')
		return (1);
	else
	{
		cub->pv_inter_x += (cub->dv_x_ray);
		cub->pv_inter_y += (cub->dv_y_ray);
	}
	return (0);
}

int	check_x(t_cub *cub)
{
	int	flag;

	flag = 0;
	if (cub->pv_inter_x >= (x_size(cub) * CARRE - CARRE))
	{
		cub->pv_inter_x = x_size(cub) * CARRE - CARRE;
		flag = 1;
	}
	else if (cub->pv_inter_x <= 0)
	{
		cub->pv_inter_x = CARRE;
		flag = 1;
	}
	return (flag);
}

int	ray_cast_ver(t_cub *cub)
{
	int	x;

	x = 0;
	if (cub->pv_inter_y <= 0)
	{
		cub->pv_inter_y = CARRE;
		x = 1;
	}
	else if (cub->pv_inter_y >= (y_size(cub)) * CARRE)
	{
		cub->pv_inter_y = (y_size(cub)) * CARRE - CARRE;
		x = 1;
	}
	if (check_x(cub) == 1 || x == 1)
		return (1);
	if (check_wall(cub) == 1)
		return (1);
	return (0);
}
