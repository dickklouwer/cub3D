/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_and_ceiling.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 11:54:54 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/08 14:23:20 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_floor_and_cailing(t_game *game)
{
	mlx_put_pixel(game->img, 1, 1, 0x00FF0000);
}

