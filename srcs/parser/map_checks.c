/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:47:25 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/07/13 08:17:26 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	map_prerequisites(t_player *player, char *line, int y)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1')
		{
			if (line[i] == 'W' || line[i] == 'E'
				|| line[i] == 'S' || line[i] == 'N')
			{
				player->sx = i + 1;
				player->sy = y + 1;
				player->orientation = line[i];
				player->player_count++;
			}
			else if (line[i] == ' ')
				i++;
			else
				err_exit("Given map not parseable");
		}
		i++;
	}
}

