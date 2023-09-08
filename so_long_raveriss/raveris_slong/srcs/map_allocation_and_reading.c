/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_and_reading.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:06:25 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 11:31:22 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Fonction : allocate_map
**
** Description : Alloue mémoire pour la carte de jeu selon les dimensions
**               dans la structure de jeu.
**
** Argument :
**     - game (t_game *) : Pointeur sur la structure de jeu contenant les
**                          infos sur la carte, incluant taille en lignes
**                          (sum_lines) et colonnes (sum_columns).
**                          L'espace alloué est stocké dans play_map.
**
** Valeur de retour : Aucune. Modifie directement la structure de jeu.
**
** Effet de bord :
**     - Cette fonction utilise malloc(). Si l'allocation échoue, malloc()
**       renvoie NULL, et play_map sera également NULL.
**       Toujours vérifier si l'allocation a réussi avant d'utiliser play_map.
*/
static	void	allocate_map(t_game *game)
{
	game->map.play_map = (char *)malloc(sizeof(char)
			* (game->map.sum_lines * game->map.sum_columns + 1));
}

/*
** Fonction : read_map
**
** Description : Lit le contenu d'une carte de jeu depuis un fichier, le
**               stocke dans la structure de jeu, et compte les éléments de
**               la carte.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure de jeu, où le contenu de
**                          la carte sera stocké, et où les éléments de la
**                          carte seront comptés.
**     - fd (int) : Descripteur de fichier depuis lequel la carte de jeu sera
**                  lue.
**
** Valeur de retour : Aucune.
**
** Effets de bord :
**     - Cette fonction modifie directement la structure de jeu.
**     - Si la lecture échoue, les résultats seront imprévisibles.
**     - Les éléments reconnus de la carte sont :
**       'P' (emplacement du joueur), 'E' (sortie), 'C' (collectible).
**       Le nombre de collectibles est compté, et les emplacements du joueur
**       et de la sortie sont notés.
*/
static void	read_map(t_game *game, int fd)
{
	int		i;
	char	buf[1];

	i = 0;
	while (read(fd, buf, 1))
	{
		if (buf[0] != '\n')
		{
			if (i >= game->map.sum_lines * game->map.sum_columns)
				break ;
			game->map.play_map[i] = buf[0];
			if (buf[0] == 'P')
				game->map.player_spot = i;
			else if (buf[0] == 'E')
				game->map.exit_spot = i;
			else if (buf[0] == 'C')
				game->map.colect_count += 1;
			i++;
		}
	}
	game->map.play_map[i] = '\0';
}

/*
** Fonction : edit_map
**
** Description : Alloue de la mémoire pour la carte de jeu, puis la remplit
**               en lisant le contenu d'un fichier.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure de jeu, où la carte sera
**                          stockée.
**     - path (char *)   : Chemin du fichier à partir duquel la carte sera lue.
**
** Valeur de retour : Aucune.
**
** Effets de bord :
**     - Cette fonction utilise allocate_map() pour allouer de la mémoire pour
**       la carte, et read_map() pour la remplir. Elle modifie donc directement
**       la structure de jeu.
**     - Si l'allocation de mémoire échoue, ou si la lecture du fichier échoue,
**       les résultats sont imprévisibles.
*/
void	edit_map(t_game *game, char *path)
{
	int	fd;

	allocate_map(game);
	if (!game->map.play_map)
	{
		print_error(game, "Map play alloc error\n");
		close_window(game);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	read_map(game, fd);
	close(fd);
}
