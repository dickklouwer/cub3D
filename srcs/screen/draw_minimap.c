/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/09 14:42:25 by bprovoos      ########   odam.nl         */
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

void	draw_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int steps;
	int x;
	int y;

	dx = x2 - x1;
	dy = y2 - y1;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x = x1;
	y = y1;
	dx /= steps;
	dy /= steps;
	while (steps--)
	{
		mlx_put_pixel(game->img, x, y, color);
		x += dx;
		y += dy;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int dx;
	int dy;

	dx = 0;
	while (dx < size)
	{
		dy = 0;
		while (dy < size)
		{
			mlx_put_pixel(game->img, x + dx, y + dy, color);
			dy++;
		}
		dx++;
	}
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	calculate_rays(t_game *game)
{
	int		ray_index;
	int		dof;
	double	aTan;
	double	nTan;
	
	ray_index = -game->config.num_rays / 2;
	while (ray_index <= game->config.num_rays / 2)
	{
		// if (ray_index != 0)
		// {
		// 	ray_index++;
		// 	continue;
		// }
		game->ray->angle = game->player.pa + (ray_index * game->config.angle_step);
		// printf("ray angle: %f\n\n", game->ray->angle);
		/* Horizontal */
		aTan = -1 / tan(game->ray->angle * M_PI / 180);
		dof = 0;
		if (game->ray->angle > 180)
		{
			game->ray->ry = round_tail_down(game->player.py);
			game->ray->rx = (game->player.py - game->ray->ry) * aTan + game->player.px;
			game->ray->yo = -game->config.tile_size;
			game->ray->xo = -game->ray->yo * aTan;
		}
		else if (game->ray->angle < 180)
		{
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
			if (game->ray->mx < 0 || game->ray->mx >= game->map.width || game->ray->my < 0 || game->ray->my >= game->map.height)
				dof = 8;
			else if (game->map.map[game->ray->my][game->ray->mx] == '1')
			{
				game->ray->hx = game->ray->rx;
				game->ray->hy = game->ray->ry;
				game->ray->dis_h = distance(game->player.px, game->player.py, game->ray->rx, game->ray->ry);
				dof = 8;
			}
			else
			{
				mlx_put_pixel(game->img, game->ray->rx, game->ray->ry, 0xFF0000FF);
				game->ray->rx += game->ray->xo;
				game->ray->ry += game->ray->yo;
				dof++;
			}
		}
		// printf("hray rx: %d\n", game->ray->rx);
		// printf("hray ry: %d\n", game->ray->ry);
		/* Vertical */
		nTan = -tan(game->ray->angle * M_PI / 180);
		dof = 0;
		if (game->ray->angle < 90 || game->ray->angle > 270)
		{
			// printf("right\n");
			game->ray->rx = round_tail_up(game->player.px);
			game->ray->ry = (game->player.px - game->ray->rx) * nTan + game->player.py;
			game->ray->xo = game->config.tile_size;
			game->ray->yo = -game->ray->xo * nTan;
		}
		else if (game->ray->angle > 90 && game->ray->angle < 270)
		{
			// printf("left\n");
			game->ray->rx = round_tail_down(game->player.px);
			game->ray->ry = (game->player.px - game->ray->rx) * nTan + game->player.py;
			game->ray->xo = -game->config.tile_size;
			game->ray->yo = -game->ray->xo * nTan;
		}
		else if (game->ray->angle == 90 || game->ray->angle == 270)
			dof = 8;
		while (dof < 8)
		{
			game->ray->mx = (int)(game->ray->rx)>>5;
			game->ray->my = (int)(game->ray->ry)>>5;
			if (game->ray->mx < 0 || game->ray->mx >= game->map.width || game->ray->my < 0 || game->ray->my >= game->map.height)
				dof = 8;
			else if (game->map.map[game->ray->my][game->ray->mx] == '1')
			{
				game->ray->vx = game->ray->rx;
				game->ray->vy = game->ray->ry;
				game->ray->dis_v = distance(game->player.px, game->player.py, game->ray->rx, game->ray->ry);
				dof = 8;
			}
			else
			{
				mlx_put_pixel(game->img, game->ray->rx, game->ray->ry, 0x00FF00FF);
				game->ray->rx += game->ray->xo;
				game->ray->ry += game->ray->yo;
				dof++;
			}
		}
		game->ray->hit_h = -1;
		game->ray->hit_v = -1;
		if (game->ray->dis_h < game->ray->dis_v)
		{
			game->ray->hit_h = game->ray->hx;
			game->ray->hit_v = game->ray->hy;
			game->ray->length = game->ray->dis_h;
		}
		else
		{
			game->ray->hit_h = game->ray->vx;
			game->ray->hit_v = game->ray->vy;
			game->ray->length = game->ray->dis_v;
		}
		if (game->ray->hit_h != -1 && game->ray->hit_v != -1)
			mlx_put_pixel(game->img, game->ray->hit_h, game->ray->hit_v, 0xFFFFFFFF);
		// printf("hit h: %d\n", game->ray->hit_h);
		// printf("hit v: %d\n", game->ray->hit_v);
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
