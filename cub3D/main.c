/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:53:54 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/07 00:23:18 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	assigment_fov(t_ray *ray)
{
	if (ray->p_fov == 'N')
		ray->pa = 90;
	else if (ray->p_fov == 'S')
		ray->pa = 270;
	else if (ray->p_fov == 'W')
		ray->pa = 180;
	else if (ray->p_fov == 'E')
		ray->pa = 0;
}

void	ray_init(t_ray *ray)
{
	int	i;

	i = 0;
	ray->px = (ray->player_x << 6) + 20;
	ray->py = (ray->player_y << 6) + 50;
	ray->ray = malloc(sizeof(float) * 60);
	ray->drc = malloc(sizeof(char) * 61);
	assigment_fov(ray);
	ray->pdx = cos(deg_to_rad(ray->pa));
	ray->pdy = -sin(deg_to_rad(ray->pa));
	ray->ra = fix_ang(ray->pa + 30);
	ray->ray_xy = malloc(sizeof(float *) * 60);
	while (i < 60)
	{
		ray->ray_xy[i] = malloc(sizeof(float) * 2);
		i++;
	}
	ray->i = 0;
}

void	ft_map_free(t_main *main)
{
	int	i;

	i = 0;
	while (main->map->map[i])
		free(main->map->map[i++]);
	free(main->map->map);
	i = 0;
	while (main->map->c_map[i])
		free(main->map->c_map[i++]);
	i = 0;
	while (main->full_cub[i])
		free(main->full_cub[i++]);
	free(main->map->c_map);
	free(main->full_cub);
	free(main->map);
}

void	data_init(t_main **main, char *str, int *fd)
{
	*fd = open(str, O_RDONLY);
	(*main)->map = malloc(sizeof(t_map));
	(*main)->ray = malloc(sizeof(t_ray));
	(*main)->image_w = malloc(sizeof(t_image));
	(*main)->image_e = malloc(sizeof(t_image));
	(*main)->image_s = malloc(sizeof(t_image));
	(*main)->image_n = malloc(sizeof(t_image));
	(*main)->pixel_n = malloc(sizeof(float) * 60);
	(*main)->which_pixel = malloc(sizeof(int) * 60);
	(*main)->f = malloc(sizeof(int) * 3);
	(*main)->c = malloc(sizeof(int) * 3);
	(*main)->i = 0;
	(*main)->j = 0;
	(*main)->full_length = 0;
	(*main)->map->j = 0;
}

int	main(int ac, char **av)
{
	t_main	*main;
	int		fd;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (ac != 2)
		wrong_argument_exit(NULL, 10);
	main = malloc(sizeof(t_main));
	if (!main)
		allocation_exit(main);
	data_init(&main, av[1], &fd);
	main->map_name = av[1];
	check_file_name(main, av[1]);
	check_map(main);
	player_position(main);
	assault_map(main);
	ray_init(main->ray);
	main->mlx_ptr = mlx_init();
	image_creater(main);
	mlx_func(main);
}
