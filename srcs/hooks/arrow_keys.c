/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrow_keys.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 10:42:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/21 13:05:53 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_hook(void *param)
{
	t_game	*game;
	bool	redraw;

	game = param;
	redraw = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->minimap->instances->y += 1;
		redraw = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->minimap->instances->y -= 1;
		redraw = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->minimap->instances->x += 1;
		redraw = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->minimap->instances->x -= 1;
		redraw = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT_SHIFT))
			game->map.show_minimap = false;
		else
			game->map.show_minimap = true;
		redraw = true;
	}
	if (redraw)
		update_screen(game);
}