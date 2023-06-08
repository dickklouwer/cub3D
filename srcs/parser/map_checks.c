/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:47:25 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/07 12:04:04 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    map_prerequisites(t_player *player, char *line, int y)
{
    int     i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1')
        {
            if (line[i] == 'W' || line[i] == 'E'
                || line[i] == 'S' || line[i] == 'N')
            {
                player->start_x = i;
                player->start_y = y;
                player->orientation = line[i];
                player->player_count++;
            }
            else if (line[i] == ' ')
                break ;
            else
                err_exit("Wrong map tile");
        }
        i++;
    }
}

int	is_map_surrounded(t_map *map)
{
    char **linesplit;
	int	i;
	int j;

    j = 0;
	i = 1;
    if (ft_strspn(map->map[0], "1") != ft_strlen(map->map[0]))
        return (EXIT_FAILURE);
    if (ft_strspn(map->map[map->map_y - 1], "1") != ft_strlen(map->map[map->map_y - 1]))
        return (EXIT_FAILURE);
	while (i < map->map_y)
	{
        linesplit = ft_split(map->map[i], ' ');
        j = 0;
        while (linesplit[j])
        {
            printf("%s", linesplit[j]);
            map->map_x = ft_strlen(linesplit[j]);
            if (linesplit[j][0] != '1' ||linesplit[j][map->map_x - 1] != '1')
                return (EXIT_FAILURE);
            j++;
        }
        free(linesplit);
		i++;
	}
	return (EXIT_SUCCESS);
}
