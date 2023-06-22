/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrow_keys.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 10:42:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/22 11:36:37 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	key_up(t_game *game)
{
	game->player.px -= game->player.pdx;
	game->player.py -= game->player.pdy;
	game->minimap->instances->x = round(game->player.px) + (MINIMAP_WIDTH / 2) - (PLAYER_SIZE / 2);
	game->minimap->instances->y = round(game->player.py) + (MINIMAP_HEIGTH / 2) - (PLAYER_SIZE / 2);
	game->map.updata_screen = true;
}

static	void	key_down(t_game *game)
{
	game->player.px += game->player.pdx;
	game->player.py += game->player.pdy;
	game->minimap->instances->x = round(game->player.px) + (MINIMAP_WIDTH / 2) - (PLAYER_SIZE / 2);
	game->minimap->instances->y = round(game->player.py) + (MINIMAP_HEIGTH / 2) - (PLAYER_SIZE / 2);
	game->map.updata_screen = true;
}

static	void	key_left(t_game *game)
{
	if (game->player.pa <= 2)
		game->player.pa += 360;
	game->player.pa -= 2;
	game->player.pdx = cos(game->player.pa / 180 * M_PI);
	game->player.pdy = sin(game->player.pa / 180 * M_PI);
	game->map.updata_screen = true;
}
static	void	key_right(t_game *game)
{
	if (game->player.pa > 360 -2)
		game->player.pa -= 360;
	game->player.pa += 2;
	game->player.pdx = cos(game->player.pa / 180 * M_PI);
	game->player.pdy = sin(game->player.pa / 180 * M_PI);
	game->map.updata_screen = true;
}

static	void	key_m(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT_SHIFT))
		game->map.show_minimap = false;
	else
		game->map.show_minimap = true;
	game->map.updata_screen = true;
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		key_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		key_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		key_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		key_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
		key_m(game);
	if (game->map.updata_screen)
		update_screen(game);
}