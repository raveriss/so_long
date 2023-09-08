/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_existence_check.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:44:56 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:10:43 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Fonction : get_xpm_filename
**
** Description : Renvoie le nom du fichier XPM correspondant à l'index donné.
**
** Paramètres :
**     - i : L'index du fichier XPM souhaité.
**
** Retour : Le nom du fichier XPM correspondant à l'index donné.
**
** Note : La fonction `get_xpm_filename` est utilisée pour obtenir le nom du
**        fichier XPM correspondant à l'index spécifié. Elle utilise un tableau
**        statique de noms de fichiers XPM, où chaque élément du tableau est
**        associé à un index spécifique. Lorsqu'on appelle la fonction avec un
**        index valide, elle renvoie le nom du fichier XPM correspondant. Cette
**        fonction est utile pour faciliter l'accès aux fichiers XPM nécessaires
**        dans le cadre du programme So_Long.
*/
char	*get_xpm_filename(int i)
{
	static char	*xpm_filename[] = {
		"xpm/border_bottom.xpm", "xpm/border_right.xpm", "xpm/border_left.xpm",
		"xpm/border_top.xpm", "xpm/collectible1.xpm", "xpm/collectible2.xpm",
		"xpm/collectible3.xpm", "xpm/collectible4.xpm", "xpm/collectible5.xpm",
		"xpm/collectible6.xpm", "xpm/collectible7.xpm", "xpm/collectible8.xpm",
		"xpm/collectible9.xpm", "xpm/collectible10.xpm",
		"xpm/collectible11.xpm", "xpm/collectible12.xpm",
		"xpm/corner_bottom_left.xpm", "xpm/corner_top_left.xpm",
		"xpm/corner_bottom_right.xpm", "xpm/corner_top_right.xpm",
		"xpm/exit_close.xpm", "xpm/exit_open.xpm", "xpm/ground_texture.xpm",
		"xpm/lethal_enemies_down.xpm", "xpm/player_up.xpm",
		"xpm/player_right.xpm", "xpm/player_down.xpm", "xpm/player_left.xpm",
		"xpm/player_dies.xpm", "xpm/wall_texture.xpm",
	};

	return (xpm_filename[i]);
}

/*
** Fonction : check_images_exist
**
** Description : Vérifie l'existence des fichiers d'images nécessaires au jeu.
**
** Arguments :
**     - game (t_game *) : Pointeur vers la structure de jeu contenant les
**                          informations nécessaires.
**
** Note : La fonction `check_images_exist` vérifie si les fichiers d'images
**        nécessaires au jeu existent. Elle parcourt une liste d'images en
**        utilisant une boucle while et utilise la fonction auxiliaire
**        `get_collect_filename` pour obtenir le nom de fichier correspondant
**        à chaque image. Ensuite, pour chaque fichier d'image, la fonction
**        tente d'ouvrir le fichier en mode lecture seule en utilisant la
**        fonction `open`. Si l'ouverture du fichier échoue (retourne -1),
**        cela signifie que le fichier n'existe pas, et la fonction
**        `put_error_message` est appelée pour afficher un message d'erreur
**        spécifique au fichier manquant.
**
** Note : Il est important de noter que la fonction ne retourne pas de valeur
**        ni ne renvoie d'erreur explicite. Elle se contente d'afficher les
**        messages d'erreur pour les fichiers d'images manquants.
*/
void	check_images_exist(t_game *game)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	while (i < XPM_IMG_COUNT)
	{
		filename = get_xpm_filename(i);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			put_error_message(game, filename);
		}
		close(fd);
		i++;
	}
}
