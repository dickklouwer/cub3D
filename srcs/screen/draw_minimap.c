/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/02 21:15:03 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;

void draw_tile(t_game *game, int color, int x, int y)
{
	int dx;
	int dy;
	int map_x = x * game->config.tile_size;
	int map_y = y * game->config.tile_size;

	dx = 0;
	while (dx < game->config.tile_size)
	{
		dy = 0;
		while (dy < game->config.tile_size)
		{
			if(map_x + dx >= 0 && map_x + dx < MINIMAP_WIDHT && map_y + dy >= 0 && map_y + dy < MINIMAP_HEIGHT)
				mlx_put_pixel(game->img, map_x + dx, map_y + dy, color);
			dy++;
		}
		dx++;
	}
}

void draw_tile_new(t_game *game, int color, int mx, int my)
{
	mlx_put_pixel(game->img, mx, my, color);
}

void draw_borders(t_game *game)
{
	int x;
	int y;
	int color;
	t_map *map;

	x = 0;
	map = &game->map;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			// if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
			// 	color = 0x12ADB3;
			if (game->map.map[y][x] == '1')
				color = 0x12ADB3;
			else if (game->map.map[y][x] == '0')
				color = 0xAAAAAAFF;
			else if (game->map.map[y][x] == ' '|| game->map.map[y][x] == '\0')
				color = 0x00000000;
			draw_tile(game, color, x, y);
			y++;
		}
		x++;
	}	
}

int	round_tail_down(int num)
{
	return ((((int)num>>5)<<5)-0.0001);
}

int	round_tail_up(int num)
{
	return ((((int)num>>5)<<5) + 32);
}

void	calculate_ray(t_game *game)
{
	
}

void	calculate_rays(t_game *game)
{
	int		ray_index;
	int		dof;
	double	aTan;
	
	dof = 0;
	ray_index = -game->config.num_rays / 2;
	while (ray_index <= game->config.num_rays / 2)
	{
		if (ray_index != 0)
		{
			ray_index++;
			continue;
		}
		game->ray->angle = game->player.pa + (ray_index * game->config.angle_step);
		aTan = -1 / tan(game->ray->angle * M_PI / 180);
		if (game->ray->angle > 180)
		{
			printf("up\n");
			game->ray->ry = round_tail_down(game->player.py);
			game->ray->rx = (game->player.py - game->ray->ry) * aTan + game->player.px;
			game->ray->yo = -game->config.tile_size;
			game->ray->xo = -game->ray->yo * aTan;
		}
		else if (game->ray->angle < 180)
		{
			printf("down\n");
			game->ray->ry = round_tail_up(game->player.py);
			game->ray->rx = (game->player.py - game->ray->ry) * aTan + game->player.px;
			game->ray->yo = game->config.tile_size;
			game->ray->xo = -game->ray->yo * aTan;
		}
		else if (game->ray->angle == 0 || game->ray->angle == 180)
			dof = 8;
		while (dof < 8)
		{
			game->ray->mx = (int)(game->ray->rx)>>5;
			game->ray->my = (int)(game->ray->ry)>>5;
			printf("map: '%c'\n", game->map.map[game->ray->mx][game->ray->my]);
			// if (game->ray->mp > 0 && game->ray->mp < game->map.width * game->map.height && game->map.map[game->ray->mp] == '1')
			// 	dof = 8;
			if (game->ray->mx >= 0 && game->ray->my >= 0 && game->ray->mx < game->map.width && game->ray->my < game->map.height && game->map.map[game->ray->mx][game->ray->my] == '1')
				dof = 8;
			else
			{
				mlx_put_pixel(game->img, game->ray->rx, game->ray->ry, 0x00FF00FF);
				game->ray->rx += game->ray->xo;
				game->ray->ry += game->ray->yo;
				dof++;
			}
			mlx_put_pixel(game->img, game->ray->rx, game->ray->ry, 0x00FF00FF);
		}
		printf("ray angle: %f\n\n", game->ray->angle);
		ray_index++;
	}
}

void	draw_player_in_minimap(t_game *game)
{
	int x;
	int y;

	x = -PLAYER_SIZE / 2;
	while (x < PLAYER_SIZE / 2)
	{
		y = -PLAYER_SIZE / 2;
		while (y < PLAYER_SIZE / 2)
		{
			mlx_put_pixel(game->img, game->player.px + x, game->player.py + y, 0x00FF00FF);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < PLAYER_SIZE * 2)
	{
		mlx_put_pixel(game->img, game->player.px + (cos(game->player.pa * M_PI / 180) * x), game->player.py + (sin(game->player.pa * M_PI / 180) * x), 0x00FF00FF);
		x++;
	}
}

void	draw_game(t_game *game)
{
	// t_ray *rays;
	// const int px = game->player.px;
	// const int py = game->player.py;

	// rays = (t_ray *)ft_calloc(sizeof(t_ray),  game->config.num_rays + 1);
	// if (!rays)
	// 	perror("Failed to allocate memory");
	if (game->map.show_minimap)
	{
		draw_borders(game);
		draw_player_in_minimap(game);
	}
	// draw_minimap_player(game);
	calculate_rays(game);
	// calculate_raycast(game, rays, px, py);
	// draw_player(game, rays, px, py);
	// free(rays);
}
