/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 11:58:05 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/22 14:48:57 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_walls(t_game *game)
{

}

void	draw_screen(t_game *game)
{
	game->img = mlx_new_image(game->mlx, GAME_WIDTH, GAME_HEIGHT);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		err_exit("Failed to draw screen");
	game->minimap = mlx_new_image(game->mlx, game->map.height * 32, game->map.width * 32);
	if (!game->minimap || (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0))
		err_exit("Failed to draw miniscreen");
	game->minimap->instances->x = round(game->player.px) + (MINIMAP_WIDTH / 2) - (PLAYER_SIZE / 2);
	game->minimap->instances->y = round(game->player.py) + (MINIMAP_HEIGHT / 2) - (PLAYER_SIZE / 2);
	update_screen(game);
}

void	update_screen(t_game *game)
{
	// draw_floor_and_cailing(game);
	if (game->map.show_minimap)
		draw_minimap(game);
	mlx_set_instance_depth(game->img->instances, 1);
	mlx_set_instance_depth(game->minimap->instances, 1);
	game->map.update_screen = false;
}
