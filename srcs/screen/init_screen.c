/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 10:55:02 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/13 10:52:21 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_screen(mlx_t **mlx)
{
	*mlx = mlx_init(GAME_WIDTH, GAME_HEIGTH, "Cub3D", false);
	if (!*mlx)
		err_exit("Failed to initialize mlx");
}
