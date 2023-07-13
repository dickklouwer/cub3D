/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 13:49:45 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/07/13 13:53:00 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     print_textures(t_game *game)
{
    printf("%s\n", game->config.east_texture);
    printf("%s\n", game->config.south_texture);
    printf("%s\n", game->config.north_texture);
    printf("%s", game->config.west_texture);
}