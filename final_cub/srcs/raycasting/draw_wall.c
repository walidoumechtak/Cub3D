/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:04:16 by woumecht          #+#    #+#             */
/*   Updated: 2023/06/19 13:36:32 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int    get_pixel(t_cub *cub, int i , int j, void *ptr)
{
    int line_len;
    int bpp;   
    int endian;
    (void)cub;

    char    *add = mlx_get_data_addr(ptr, &bpp, &line_len, &endian);
    int *color = NULL;
    color = (int *)(add + (i * line_len) + (j * (bpp / 8)));
    return (*color);
}


void    draw_textures(t_cub *cub, int wall_height, double start_wall, int col, void *TX, int tex_height)
{
    int color;
    double inc;
    
    inc = (tex_height / (double) wall_height);
    double i = 0;
    if (wall_height >= HEIGHT)
    {
        double s =  (wall_height / 2) - (HEIGHT / 2);
        i = (((s * 100) / (wall_height / 2)) / (100)) * (tex_height / 2);
    }
    if (start_wall < 0)
        start_wall = 0;
    double j = start_wall;
    while (start_wall < (int)(wall_height) + j)
    {
        if (start_wall >= HEIGHT)
        {
            break;
        }
        color = get_pixel(cub, (int)i, cub->x_offset, TX);
        my_mlx_pixel_put(&cub->data, col, start_wall, color);
        start_wall++;
        if (i < tex_height)
            i += inc;
    }
}


void    draw_wal(t_cub *cub, char flag, int x, int WALL_TEXTR)
{
    double wall_height;
    int start_wall;
    double rest = 0;

    start_wall = 0;
    if (flag == 'H')
    {
        rest = (cub->ph_inter_x / CARRE) - (int)(cub->ph_inter_x / CARRE);
        
        cub->dis_h = fabs(cos(fabs(cub->ray_dir - cub->ply.dir)) * (cub->dis_h));
        wall_height = ((CARRE / cub->dis_h) * cub->dis_proj_plan);
        start_wall = ((HEIGHT / 2) - (wall_height / 2));
        if (WALL_TEXTR == 'T')
        {
            cub->x_offset = rest * cub->tex_size.no_width;
            draw_textures(cub, wall_height,  start_wall, x, cub->no_ptr, cub->tex_size.no_height);
        }
        else
        {
            cub->x_offset = rest * cub->tex_size.so_width;
            draw_textures(cub, wall_height, start_wall, x, cub->so_ptr, cub->tex_size.so_height);
        }
            
    }
    else
    {
        rest = (cub->pv_inter_y / CARRE) - (int)(cub->pv_inter_y / CARRE);            
        cub->dis_v = fabs(cos(fabs(cub->ray_dir - cub->ply.dir)) * (cub->dis_v));
        wall_height = ((CARRE / cub->dis_v) * cub->dis_proj_plan);
        start_wall = ((HEIGHT / 2) - (wall_height / 2));
        if (WALL_TEXTR == 'R')
        {
            cub->x_offset = rest * cub->tex_size.we_width;
            draw_textures(cub, wall_height,  start_wall, x, cub->we_ptr, cub->tex_size.we_height);
        }
        else if (WALL_TEXTR == 'L')
        {
            cub->x_offset = rest * cub->tex_size.ea_width;
            draw_textures(cub, wall_height,  start_wall, x, cub->ea_ptr, cub->tex_size.ea_height);
        }
    }
    
}