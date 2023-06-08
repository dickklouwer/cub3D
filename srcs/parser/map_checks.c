/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:47:25 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/08 14:29:47 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				player->x = i;
				player->y = y;
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
