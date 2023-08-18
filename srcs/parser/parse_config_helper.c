/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_config_helper.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 14:36:30 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/18 14:53:29 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_config_variables(char **line)
{
	if (line[0][0] == '1' || line[0][0] == '0')
		return (EXIT_FAILURE);
	if ((ft_strncmp("N", line[0], 2)) && (ft_strncmp("S", line[0], 1))
		&& (ft_strncmp("W", line[0], 1)) && (ft_strncmp("E", line[0], 1))
		&& (ft_strncmp("F ", line[0], 2)) && (ft_strncmp("C ", line[0], 2))
		&& !line[1])
		err_exit("Wrong variable in config file");
	return (EXIT_SUCCESS);
}

void	set_config_variables(t_config *config, char **line)
{
	if (ft_strncmp("N", *line, 1) == 0)
		config->north_texture = ft_strdup(line[1]);
	else if (ft_strncmp("S", *line, 1) == 0)
		config->south_texture = ft_strdup(line[1]);
	else if (ft_strncmp("W", *line, 1) == 0)
		config->west_texture = ft_strdup(line[1]);
	else if (ft_strncmp("E", *line, 1) == 0)
		config->east_texture = ft_strdup(line[1]);
	else if (ft_strncmp("F ", *line, 1) == 0)
		parse_color(config->floor_color, line[1]);
	else if (ft_strncmp("C ", *line, 1) == 0)
		parse_color(config->ceiling_color, line[1]);
}

int	check_dup_config_vars(t_config *config, char **line)
{
	if (ft_strncmp("N", line[0], 2) == 0 && config->north_texture != NULL)
		return (EXIT_FAILURE);
	else if (ft_strncmp("S", line[0], 2) == 0 && config->south_texture != NULL)
		return (EXIT_FAILURE);
	else if (ft_strncmp("W", line[0], 2) == 0 && config->west_texture != NULL)
		return (EXIT_FAILURE);
	else if (ft_strncmp("E", line[0], 2) == 0 && config->east_texture != NULL)
		return (EXIT_FAILURE);
	else if (ft_strncmp("F", line[0], 1) == 0 && config->floor_color[0] != -1)
		return (EXIT_FAILURE);
	else if (ft_strncmp("C", line[0], 1) == 0 && config->ceiling_color[0] != -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
