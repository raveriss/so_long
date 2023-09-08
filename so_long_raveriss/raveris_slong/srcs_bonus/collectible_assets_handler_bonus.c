/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_assets_handler_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:20:10 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:06 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Description : Cette fonction retourne le nom du fichier d'un élément
**               collectible spécifique à partir d'un tableau de chaînes de
**               caractères en mémoire statique. Chaque élément collectible a
**               un nom de fichier associé, correspondant à une image .xpm
**               différente.
**
** Paramètre :
** - i : Index de l'élément collectible dont on veut obtenir le nom du fichier.
**       L'index est utilisé pour accéder au tableau des noms de fichiers.
**
** Retour :
** - Un pointeur vers une chaîne de caractères contenant le nom du fichier de
**   l'élément collectible demandé.
**
** Remarque : L'index i doit être dans la plage valide pour le tableau
**            (0 à 11 inclus), sinon le comportement est indéfini. Cette
**            fonction ne vérifie pas si l'index est valide.
*/
char	*get_collect_filename(int i)
{
	static char	*filenames[] = {
		"xpm/collectible1.xpm", "xpm/collectible2.xpm", "xpm/collectible3.xpm",
		"xpm/collectible4.xpm", "xpm/collectible5.xpm", "xpm/collectible6.xpm",
		"xpm/collectible7.xpm", "xpm/collectible8.xpm", "xpm/collectible9.xpm",
		"xpm/collectible10.xpm", "xpm/collectible11.xpm",
		"xpm/collectible12.xpm",
	};

	return (filenames[i]);
}

/*
** Description : Cette fonction charge une image d'élément collectible
**               spécifique à partir d'un fichier et l'ajoute aux textures du
**               jeu. Elle s'appelle récursivement pour charger toutes les
**               images d'éléments collectibles, jusqu'à atteindre la limite
**               définie par ANIMATE_COLLECT_IMG.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient les textures du jeu
**          et d'autres informations de jeu.
** - i    : Index de l'image de l'élément collectible à charger. L'index est
**          utilisé pour obtenir le nom du fichier et pour positionner l'image
**          dans le tableau des textures.
**
** Cette fonction ne renvoie pas de valeur. En cas d'erreur lors du chargement
** de l'image, elle affiche un message d'erreur et termine le programme.
**
** Remarque : L'index i doit être dans la plage valide pour le tableau des
**            textures (0 à ANIMATE_COLLECT_IMG-1 inclus), sinon la fonction
**            retourne immédiatement. La récursion est arrêtée lorsque i
**            atteint ANIMATE_COLLECT_IMG.
*/
void	load_single_collect_image(t_game *game, int i)
{
	char	*filename;

	if (i >= ANIMATE_COLLECT_IMG)
		return ;
	filename = get_collect_filename(i);
	game->textures.collect[i] = mlx_xpm_file_to_image(game->mlx, filename,
			&(game->map.width), &(game->map.height));
	if (!game->textures.collect[i])
		put_error_message(game, filename);
	load_single_collect_image(game, i + 1);
}

/*
** Description : Cette fonction initialise le processus de chargement des
**               images d'éléments collectibles dans les textures du jeu. Elle
**               déclenche une suite de chargements d'images en appelant
**               load_single_collect_image avec un index initial de 0.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient les textures du jeu
**          et d'autres informations de jeu.
**
** Cette fonction ne renvoie pas de valeur. En cas d'erreur lors du chargement
** des images, elle affiche un message d'erreur et termine le programme.
**
** Remarque : Cette fonction est généralement appelée au début du jeu pour
**            charger toutes les images nécessaires avant le début de la
**            boucle de jeu.
*/
void	load_collect_images(t_game *game)
{
	load_single_collect_image(game, 0);
}
