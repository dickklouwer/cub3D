/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrow_keys.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 10:42:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/02 17:13:01 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// #define MOVE_SPEED 1
// #define ROTATE_SPEED 3

static void move(t_game *game, double new_px, double new_py)
{
	int grid_x;
	int grid_y;

	grid_x = new_px / game->config.tile_size;
	grid_y = new_py / game->config.tile_size;
	if (game->map.map[grid_y][grid_x] != '1')
	{
		game->map.update_screen = true;
		game->player.px = new_px;
		game->player.py = new_py;
	}
}

static void key_up(t_game *game)
{
	double new_px;
	double new_py;

	new_px = game->player.px + (game->config.move_speed * cos(game->player.pa * M_PI / 180));
	new_py = game->player.py + (game->config.move_speed * sin(game->player.pa * M_PI / 180));
	move(game, new_px, new_py);
}

static void key_down(t_game *game)
{
	double new_px;
	double new_py;

	new_px = game->player.px - (game->config.move_speed * cos(game->player.pa * M_PI / 180));
	new_py = game->player.py - (game->config.move_speed * sin(game->player.pa * M_PI / 180));
	move(game, new_px, new_py);
}

static void key_left(t_game *game)
{
	double new_px;
	double new_py;

	new_px = game->player.px - (game->config.move_speed * cos((game->player.pa + 90) * M_PI / 180));
	new_py = game->player.py - (game->config.move_speed * sin((game->player.pa + 90) * M_PI / 180));
	move(game, new_px, new_py);
}

static void key_right(t_game *game)
{
	double new_px;
	double new_py;

	new_px = game->player.px + (game->config.move_speed * cos((game->player.pa + 90) * M_PI / 180));
	new_py = game->player.py + (game->config.move_speed * sin((game->player.pa + 90) * M_PI / 180));
	move(game, new_px, new_py);
}

static void	look_left(t_game *game)
{
	game->player.pa -= game->config.rotate_speed;
	if (game->player.pa < 0)
	{
		game->player.pa += 360;
	}
	game->map.update_screen = true;
}

static void look_right(t_game *game)
{
	game->player.pa += game->config.rotate_speed;
	if (game->player.pa >= 360)
	{
		game->player.pa -= 360;
	}
	game->map.update_screen = true;
}

static	void	key_m(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT_SHIFT))
		game->map.show_minimap = false;
	else
		game->map.show_minimap = true;
	game->map.update_screen = true;
}

void ft_hook(void *param)
{
	t_game *game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		key_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		key_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		look_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		look_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
		key_m(game);
	if (game->map.update_screen)
		update_screen(game);
}
