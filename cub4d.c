/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub4d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2024/12/15 13:01:01 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub4d.h"

void	foo() {
	system("leaks -q cub3D");
}

void	print_map(t_mapscan *mapscan)
{
	printf("floor: %s | ceilling: %s\n", mapscan->colors.fcolor_str, mapscan->colors.ccolor_str);
	
	printf("id: %c | path: %s\n", 'N', mapscan->textures.north_tex);
	printf("id: %c | path: %s\n", 'S', mapscan->textures.south_tex);
	printf("id: %c | path: %s\n", 'E', mapscan->textures.east_tex);
	printf("id: %c | path: %s\n", 'W', mapscan->textures.west_tex);

	int i = 0;
	while (mapscan->map[i])
	{
		printf("%s\n", mapscan->map[i++]);
	}
	printf("\n");
}










t_mapscan	*readmap(char *mapfile)
{
	t_mapscan *mapscan;

	mapscan = init_mapscan(mapfile);
	if (!mapscan)
		return (NULL);
	mp_loadmap(mapscan);
	if (!mp_verifymap(mapscan))
		exit(EXIT_FAILURE);
	return (mapscan);
}


int	main(int ac, char **av) {
	t_mapscan *mapscan;

	atexit(foo);
	mapscan = readmap(av[1]);
	if (!mapscan)
		return (EXIT_FAILURE);
	print_map(mapscan);
	mp_clearmap(mapscan);
	// mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Cub4D", true);
	// if (!mlx)
	// 	return (EXIT_FAILURE);

	
	// // mlx loop.
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
