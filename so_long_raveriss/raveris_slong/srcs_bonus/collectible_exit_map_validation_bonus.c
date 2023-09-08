/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_exit_map_validation_bonus.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:42:01 by raveriss          #+#    #+#             */
/*   Updated: 2023/06/02 14:10:38 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Fonction : is_exit_accessible
** ----------------------------------
** Vérifie si l'exit du labyrinthe est accessible dans le jeu.
**
** game : Pointeur vers la structure t_game qui contient l'état actuel du jeu.
**
** Cette fonction vérifie si l'une des cellules adjacentes à l'exit est libre
** (F), c'est-à-dire qu'elle n'est pas occupée par un mur. Elle vérifie à
** gauche, à droite, en haut et en bas de la position de l'exit.
**
** La carte du jeu est stockée dans game->map.check_map, avec 'F' représentant
** une cellule libre. La position de l'exit est stockée dans
** game->map.check_exit_reach, et le nombre total de colonnes de la carte est
** stocké dans game->map.sum_columns.
**
** Retourne : 1 si l'exit est accessible, 0 sinon.
*/
int	is_exit_accessible(t_game *game)
{
	if (game->map.check_map[game->map.check_exit_reach - 1] == 'F'
		|| game->map.check_map[game->map.check_exit_reach + 1] == 'F'
		|| game->map.check_map[game->map.check_exit_reach
			- game->map.sum_columns] == 'F'
		|| game->map.check_map[game->map.check_exit_reach
			+ game->map.sum_columns] == 'F')
		return (1);
	return (0);
}

/*
** Fonction : check_no_collectibles
** -------------------------------------
** Vérifie s'il reste des collectibles sur la carte du jeu.
**
** check_map : Chaîne de caractères représentant la carte du jeu.
**
** Cette fonction parcourt chaque cellule de la carte du jeu pour vérifier s'il
** reste des collectibles. Un collectible est représenté par 'C' dans
** check_map.
**
** Si check_map est NULL, la fonction retourne 1, indiquant qu'il n'y a pas de
** collectibles (puisqu'il n'y a pas de carte).
**
** Elle itère sur chaque caractère de check_map jusqu'à la fin de la chaîne
** ('\0'). Si elle trouve un caractère 'C', elle retourne 0, indiquant qu'il
** reste au moins un collectible.
**
** Retourne : 1 s'il n'y a pas de collectibles restants, 0 sinon.
*/
int	check_no_collectibles(char *check_map)
{
	int	i;

	if (check_map == NULL)
		return (1);
	i = 0;
	while (check_map[i] != '\0')
	{
		if (check_map[i] == 'C')
			return (0);
		i++;
	}
	return (1);
}

/*
** Fonction : fill
**
** Description : Remplit récursivement un tableau donné, à partir d'une
**               position donnée, avec le caractère 'F'. S'arrête lorsque
**               elle rencontre les bords du tableau, le caractère '1' ou
**               le caractère 'F'.
**
** Arguments :
**     - tab (char *) : Le tableau à remplir.
**     - size (int)   : La taille du tableau.
**     - cur (int)    : La position actuelle dans le tableau à partir de
**                      laquelle remplir.
**     - v_step (int) : Le pas vertical, c'est-à-dire le nombre d'indices
**                      pour passer à la ligne suivante ou précédente.
**
** Valeur de retour : Aucune.
**
** Effets de bord :
**     - Modifie directement le tableau fourni.
**     - Peut entraîner un débordement de pile si la région à remplir est
**       grande, en raison de la nature récursive de la fonction.
*/
void	fill(char *tab, int size, int cur, int v_step)
{
	if (cur < 0 || cur >= size || tab[cur] == '1'
		|| tab[cur] == 'F' || tab[cur] == 'E'
		|| tab[cur] == 'K')
		return ;
	tab[cur] = 'F';
	fill(tab, size, cur - 1, v_step);
	fill(tab, size, cur + 1, v_step);
	fill(tab, size, cur - v_step, v_step);
	fill(tab, size, cur + v_step, v_step);
}

/*
** Fonction : flood_fill
**
** Description : Lance le remplissage récursif (via la fonction 'fill') sur
**               la carte de contrôle du jeu à partir de la position du joueur.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure du jeu, qui contient
**                          notamment la carte de contrôle et la position
**                          du joueur.
**
** Valeur de retour : Aucune.
**
** Effets de bord :
**     - Modifie la carte de contrôle du jeu en y effectuant le remplissage.
**     - Peut entraîner un débordement de pile si la région à remplir est
**       grande, en raison de l'appel récursif à 'fill'.
*/
void	flood_fill(t_game *game)
{
	int	size;
	int	i;

	i = 0;
	while (game->map.check_map[i] != 'P')
		i++;
	size = game->map.sum_columns * game->map.sum_lines;
	fill(game->map.check_map, size, i, game->map.sum_columns);
}

/*
** Fonction : validate_map
** -------------------------------
** Vérifie si la carte du jeu est valide.
**
** game : Pointeur vers la structure t_game qui contient l'état actuel du jeu.
**
** Cette fonction valide la carte du jeu en vérifiant deux conditions :
** 1. Il ne reste aucun collectible sur la carte.
** 2. L'exit du labyrinthe est accessible.
**
** Pour cela, elle utilise deux fonctions auxiliaires :
** 1. check_no_collectibles() vérifie s'il reste des collectibles sur la carte.
** 2. is_exit_accessible() vérifie si l'exit est accessible.
**
** Avant d'effectuer ces vérifications, elle exécute la fonction flood_fill(),
** qui remplit la carte pour faciliter ces vérifications.
**
** Si l'une de ces conditions n'est pas respectée, la fonction retourne 0,
** indiquant que la carte n'est pas valide. Si toutes les conditions sont
** respectées, elle retourne 1, indiquant que la carte est valide.
**
** Retourne : 1 si la carte est valide, 0 sinon.
*/
int	validate_map(t_game *game)
{
	flood_fill(game);
	if (!check_no_collectibles(game->map.check_map)
		|| !is_exit_accessible(game))
	{
		return (0);
	}
	return (1);
}
