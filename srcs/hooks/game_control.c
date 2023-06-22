/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_control.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 10:07:52 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/22 10:09:34 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* 
** Updates the player position on the map.
*/
void	update_player(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
}

/* 
** Updates the tile on the X- and Y- axis on the map.
*/
void	update_map(t_game *game, int x, int y, char tile)
{
	game->map.map[y][x] = tile;
}