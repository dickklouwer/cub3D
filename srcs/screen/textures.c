/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 11:54:43 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/18 11:54:49 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_textures(t_game *game)
{
	game->p.texture_n = mlx_load_png(game->config.north_texture);
	game->p.texture_s = mlx_load_png(game->config.south_texture);
	game->p.texture_w = mlx_load_png(game->config.west_texture);
	game->p.texture_e = mlx_load_png(game->config.east_texture);
}
