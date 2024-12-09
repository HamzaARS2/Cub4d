/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:09:53 by helarras          #+#    #+#             */
/*   Updated: 2024/12/09 12:01:15 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

t_mapscan	*init_mapscan(char *mapfile)
{
	t_mapscan *mapscan;

	mapscan = malloc(sizeof(t_mapscan));
	if (!mapscan)
		return (NULL);
	if (!chk_format(mapfile))
	{
		mp_post_error(ERR_FILE_FORMAT);
		return (NULL);
	}
	mapscan->mapfd = open(mapfile, O_RDONLY, 0777);
	if (mapscan->mapfd < 0)
		mp_post_error(ERR_FILE_READ);
	mapscan->map = NULL;
	mapscan->textures = (t_textures) {NULL};
	mapscan->error = NO_ERROR;
	mapscan->floor = 0;
	mapscan->ceilling = 0;
	return (mapscan);
}



void	mp_loadmap(t_mapscan *mapscan)
{
	char	*line;
	
	if (!rdr_read_data(mapscan))
	{
		mp_post_error(mapscan->error);
		exit(EXIT_FAILURE);
	}
	mapscan->map = rdr_readmap(mapscan);
	if (!mapscan->map)
	{
		mp_post_error(ERR_MAP_NOT_FOUND);
		exit(EXIT_FAILURE);
	}
}

bool	mp_verifymap(t_mapscan *mapscan)
{
	if (!chk_color(mapscan->floor))
		return (false);
	return (true);
}

void	mp_clearmap(t_mapscan *mapscan)
{
	int i;
	t_textures textures;
	
		
	i = 0;
	free(mapscan->textures.north_tex);
	free(mapscan->textures.south_tex);
	free(mapscan->textures.east_tex);
	free(mapscan->textures.west_tex);
	free(mapscan->floor);
	free(mapscan->ceilling);
	while (mapscan->map && mapscan->map[i])
	{
		free(mapscan->map[i]);
		mapscan->map[i++] = NULL;
	}
	free(mapscan->map);
	ft_memset(mapscan, 0, sizeof(t_mapscan));
	free(mapscan);
}

void	mp_post_error(t_mperror error)
{
	if (error == ERR_INVALID_DATA)
		ft_putstr_fd("Error\nInvalid data!.\n", 2);
	else if (error == ERR_MISSING_DATA)
		ft_putstr_fd("Error\nMissing data!.\n", 2);
	else if (error == ERR_DUPLICATED_DATA)
		ft_putstr_fd("Error\nDuplicated data!.\n", 2);
	else if (error == ERR_MAP_NOT_FOUND)
		ft_putstr_fd("Error\nMap not found!.\n", 2);
	else if (error == ERR_FILE_FORMAT)
		ft_putstr_fd("Error\nWrong file format!.\n", 2);
	else if (error == ERR_FILE_READ)
		ft_putstr_fd("Error\nCan't read file!.\n", 2);
	else if (error == ERR_INVALID_COLOR)
		ft_putstr_fd("Error\nInvalid color!.\n", 2);

}
