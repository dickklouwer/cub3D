/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:44:19 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/07 11:53:39 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    prep_map_data(t_map *map, t_player *player)
{
    char    *temp;
    int     y;

    y = 0;
    
    map->map_fd = open(map->path, O_RDONLY);
    if (map->map_fd < 0)
        err_exit("Failed to open map");
    while(get_next_line(map->map_fd, &temp) == 1)
    {
        map_prerequisites(player, temp, y);
        free(temp);
        y++;
    }
    map->map_y = y + 1;
    free(temp);
    close(map->map_fd);
}

void map_copy(t_map *map)
{
    int i;

    i = 0;
    map->map_cpy = (char **)ft_calloc(map->map_y, sizeof(char *));
    if (!map->map_cpy)
        err_exit("Memory allocation failed");
    while (i < map->map_y)
    {
        map->map_cpy[i] = ft_strdup(map->map[i]);
        if (!map->map_cpy[i])
            err_exit("Failed to copy map");
        i++;
    }
}

void parse_map(t_map *map, t_player *player)
{
    int i;

    i = 0;
    prep_map_data(map, player);
    map->map = (char **)ft_calloc(map->map_y, sizeof(char *));
    if (!map->map)
        err_exit("Memory allocation failed");
    map->map_fd = open(map->path, O_RDONLY);
    if (map->map_fd < 0)
        err_exit("Failed to open map");
    while (i < map->map_y)
    {
        get_next_line(map->map_fd, &map->map[i]);
        i++;
    }
    map_copy(map);
    close(map->map_fd);
}