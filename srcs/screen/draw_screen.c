/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 11:58:05 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/21 13:11:44 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_walls(t_game *game)
{

}

void	draw_screen(t_game *game)
{
	game->img = mlx_new_image(game->mlx, GAME_WIDTH, GAME_HEIGTH);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		err_exit("Failed to draw screen");
	game->minimap = mlx_new_image(game->mlx, 300, 300);
	if (!game->minimap || (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0))
		err_exit("Failed to draw miniscreen");
	update_screen(game);
}

void	update_screen(t_game *game)
{
	draw_floor_and_cailing(game);
	if (game->map.show_minimap)
		draw_2d_map(game);
	mlx_set_instance_depth(game->img->instances, 2);
	mlx_set_instance_depth(game->minimap->instances, 1);
}
