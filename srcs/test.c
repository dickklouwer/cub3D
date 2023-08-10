/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 14:45:02 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/10 20:22:39 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int worldMap[8][8]=
{
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,2,1},
};

void	init_test(t_game *game)
{
	game->p.pos_x = 4;
	game->p.pos_y = 4;
	game->p.dir_x = -1.0;
	game->p.dir_y = 0.0;
	game->p.plane_x = 0;
	game->p.plane_y = 0.66;
	game->p.time = 0;
	game->p.old_time = 0;
	printf("x:y "GREEN"%f"NC":"RED"%f\n"NC"", game->p.pos_x, game->p.pos_y);
}

void	calculate_ray_position_and_direction(t_game *game, int x)
{
	game->p.camera_x = (2 * x / (double)GAME_WIDTH) - 1;
	game->p.ray_dir_x = game->p.dir_x + (game->p.plane_x * game->p.camera_x);
	game->p.ray_dir_y = game->p.dir_y + (game->p.plane_y * game->p.camera_x);
}

void	get_player_position(t_game *game)
{
	game->p.map_x = (int)game->p.pos_x;
	game->p.map_y = (int)game->p.pos_y;
}

void	calculate_delta_dis(t_game *game)
{
	if (game->p.ray_dir_x == 0)
		game->p.delta_dist_x = INFINITY;
	else
		game->p.delta_dist_x = fabs(1 / game->p.ray_dir_x);
	if (game->p.ray_dir_y == 0)
		game->p.delta_dist_y = INFINITY;
	else
		game->p.delta_dist_y = fabs(1 / game->p.ray_dir_y);
}

void	calculate_side_dis_x(t_game *game)
{
	if (game->p.ray_dir_x < 0)
	{
		game->p.step_x = -1;
		game->p.side_dist_x = (game->p.pos_x - game->p.map_x) * game->p.delta_dist_x;
	}
	else
	{
		game->p.step_x = 1;
		game->p.side_dist_x = (game->p.map_x + 1.0 - game->p.pos_x) * game->p.delta_dist_x;
	}
}

void	calculate_side_dis_y(t_game *game)
{
	if (game->p.ray_dir_y < 0)
	{
		game->p.step_y = -1;
		game->p.side_dist_y = (game->p.pos_y - game->p.map_y) * game->p.delta_dist_y;
	}
	else
	{
		game->p.step_y = 1;
		game->p.side_dist_y = (game->p.map_y + 1.0 - game->p.pos_y) * game->p.delta_dist_y;
	}
}

void	calculate_step(t_game *game)
{
		get_player_position(game);
		calculate_delta_dis(game);
		calculate_side_dis_x(game);
		calculate_side_dis_y(game);
}

void	digital_differential_analysis(t_game *game)
{
	game->p.hit = 0;
	while (game->p.hit == 0)
	{
		if (game->p.side_dist_x < game->p.side_dist_y)
		{
			game->p.side_dist_x += game->p.delta_dist_x;
			game->p.map_x += game->p.step_x;
			game->p.side = 0;
		}
		else
		{
			game->p.side_dist_y += game->p.delta_dist_y;
			game->p.map_y += game->p.step_y;
			game->p.side = 1;
		}
		// if (game->map.map[game->p.map_y][game->p.map_x] != '0')
		// 	game->p.hit = 1;
		if (worldMap[game->p.map_x][game->p.map_y] > 0)
			game->p.hit = 1;
	}
}

void	calculate_distance(t_game *game)
{
	if (game->p.side == 0)
		game->p.perp_wal_dist = game->p.side_dist_x - game->p.delta_dist_x;
	else
		game->p.perp_wal_dist = game->p.side_dist_y - game->p.delta_dist_y;
}

void	calculate_vertical_line(t_game *game)
{
	game->p.line_height = (int)(GAME_HEIGTH / game->p.perp_wal_dist);
	game->p.line_start_y = (GAME_HEIGTH / 2) - (game->p.line_height / 2);
	game->p.line_stop_y = (GAME_HEIGTH / 2) + (game->p.line_height / 2);
	if (game->p.line_start_y < 0)
		game->p.line_start_y = 0;
	if (game->p.line_stop_y >= GAME_HEIGTH)
		game->p.line_stop_y = GAME_HEIGTH - 1;
}

void	draw_vertical_line(t_game *game, int x)
{
	int	y;

	y = game->p.line_start_y;
	while (y < game->p.line_stop_y)
	{
		if (game->p.side == 0)
			mlx_put_pixel(game->img, x, y, 0xFFFFFFFF);
		else
			mlx_put_pixel(game->img, x, y, 0x0000FFFF);
		y++;
	}
}

void test_hook(void *param)
{
	t_game *game;
	double	move_speed;
	double	rotate_speed;

	move_speed = 0.1;
	rotate_speed = 0.05;
	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (worldMap[(int)(game->p.pos_x + game->p.dir_x * move_speed)][(int)game->p.pos_y] == false)
			game->p.pos_x += (game->p.dir_x * move_speed);
		if (worldMap[(int)game->p.pos_x][(int)(game->p.pos_y + game->p.dir_y * move_speed)] == false)
			game->p.pos_y += (game->p.dir_y * move_speed);
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (worldMap[(int)(game->p.pos_x - game->p.dir_x * move_speed)][(int)game->p.pos_y] == false)
			game->p.pos_x -= (game->p.dir_x * move_speed);
		if (worldMap[(int)game->p.pos_x][(int)(game->p.pos_y - game->p.dir_y * move_speed)] == false)
			game->p.pos_y -= (game->p.dir_y * move_speed);
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->p.old_dir_x = game->p.dir_x;
		game->p.dir_x = (game->p.dir_x * cos(-rotate_speed)) - (game->p.dir_y * sin(-rotate_speed));
		game->p.dir_y = (game->p.old_dir_x * sin(-rotate_speed)) + (game->p.dir_y * cos(-rotate_speed));
		game->p.old_plane_x = game->p.plane_x;
		game->p.plane_x = (game->p.plane_x * cos(-rotate_speed)) - (game->p.plane_y * sin(-rotate_speed));
		game->p.plane_y = (game->p.old_plane_x * sin(-rotate_speed)) + (game->p.plane_y * cos(-rotate_speed));
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->p.old_dir_x = game->p.dir_x;
		game->p.dir_x = (game->p.dir_x * cos(rotate_speed)) - (game->p.dir_y * sin(rotate_speed));
		game->p.dir_y = (game->p.old_dir_x * sin(rotate_speed)) + (game->p.dir_y * cos(rotate_speed));
		game->p.old_plane_x = game->p.plane_x;
		game->p.plane_x = (game->p.plane_x * cos(rotate_speed)) - (game->p.plane_y * sin(rotate_speed));
		game->p.plane_y = (game->p.old_plane_x * sin(rotate_speed)) + (game->p.plane_y * cos(rotate_speed));
		game->map.update_screen = true;
	}
	if (game->map.update_screen)
		update_screen(game);
}

void	test(t_game *game)
{
	int	i;

	i = 0;
	while (i < GAME_WIDTH)
	{
		// if (i != GAME_WIDTH / 2)
		// {
		// 	i++;
		// 	continue;
		// }
		calculate_ray_position_and_direction(game, i);
		calculate_step(game);
		digital_differential_analysis(game);
		calculate_distance(game);
		calculate_vertical_line(game);
		draw_vertical_line(game, i);
		i++;
	}
}
