/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:34:44 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 13:37:29 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Charge une image à partir d'un fichier .xpm et la convertit en image mlx.
**
** Cette fonction utilise la fonction 'mlx_xpm_file_to_image' pour charger un
** fichier .xpm spécifié et le convertir en une image utilisable par la minilibx.
** Les dimensions de l'image sont également récupérées et stockées dans la
** structure du jeu.
**
** @param t_game *game - Pointeur vers la structure du jeu, qui contient le
** contexte mlx ainsi que les champs width et height qui seront remplis par cette
** fonction.
** @param char *filename - Le nom du fichier .xpm à charger.
**
** @return Un pointeur vers l'image mlx chargée, ou NULL en cas d'erreur.
*/
static void	*load_image(t_game *game, char *filename)
{
	return (mlx_xpm_file_to_image(game->mlx, filename, &game->map.width,
			&game->map.height));
}

/*
** Charge les textures de base pour le jeu.
**
** Cette fonction est responsable du chargement des textures fondamentales
** nécessaires pour le jeu, y compris le personnage du joueur, les coins, et
** les ennemis. Elle utilise la fonction 'load_image' pour charger chaque
** texture à partir de son fichier .xpm respectif.
**
** @param t_game *game - Pointeur vers la structure du jeu, qui contient entre
** autres, le contexte mlx et les champs de texture qui seront remplis par
** cette fonction.
*/
static void	load_base_textures(t_game *game)
{
	game->textures.player = load_image(game, "xpm/player_left.xpm");
	game->textures.corner_top_left = load_image(game,
			"xpm/corner_top_left.xpm");
	game->textures.corner_top_right = load_image(game,
			"xpm/corner_top_right.xpm");
	game->textures.corner_bottom_left = load_image(game,
			"xpm/corner_bottom_left.xpm");
	game->textures.corner_bottom_right = load_image(game,
			"xpm/corner_bottom_right.xpm");
	game->textures.killer = load_image(game, "xpm/lethal_enemies_down.xpm");
}

/*
** Charge les textures de bordure du jeu.
**
** Cette fonction est responsable du chargement des textures de bordure pour le
** jeu. Elle utilise la fonction 'load_image' pour charger chaque texture depuis
** son fichier .xpm respectif.
**
** @param t_game *game - Pointeur vers la structure du jeu qui contient, entre
** autres, le contexte mlx et les champs de texture qui seront remplis par cette
** fonction.
*/
static void	load_border_textures(t_game *game)
{
	game->textures.border_top = load_image(game, "xpm/border_top.xpm");
	game->textures.border_bottom = load_image(game, "xpm/border_bottom.xpm");
	game->textures.border_left = load_image(game, "xpm/border_left.xpm");
	game->textures.border_right = load_image(game, "xpm/border_right.xpm");
}

/*
** Charge les textures diverses du jeu.
**
** Cette fonction est responsable du chargement des textures diverses telles que
** le mur, le sol, l'exit et le collectible. Pour chaque texture, elle utilise la
** fonction 'load_image' pour charger l'image correspondante à partir du fichier
** .xpm spécifié. En cas d'échec du chargement d'une texture, elle affiche un
** message d'erreur approprié.
**
** @param t_game *game - Pointeur vers la structure du jeu qui contient, entre
** autres, le contexte mlx et les champs de texture qui seront remplis par cette
** fonction.
*/
static void	load_misc_textures(t_game *game)
{
	game->textures.wall = load_image(game, "xpm/wall_texture.xpm");
	if (game->textures.wall == NULL)
		print_error(game, "Cannot load wall texture\n");
	game->textures.ground = load_image(game, "xpm/ground_texture.xpm");
	if (game->textures.ground == NULL)
		print_error(game, "Cannot load ground texture\n");
	game->textures.exit = load_image(game, "xpm/exit_close.xpm");
	if (game->textures.exit == NULL)
		print_error(game, "Cannot load exit texture\n");
	game->textures.colect = load_image(game, "xpm/collectible5.xpm");
	if (game->textures.colect == NULL)
		print_error(game, "Cannot load colect texture\n");
}

/*
** Charge toutes les textures nécessaires pour le jeu.
**
** Cette fonction est responsable du chargement de toutes les textures qui
** seront utilisées dans le jeu. Elle appelle plusieurs autres fonctions
** spécialisées dans le chargement de différents types de textures : de base,
** de bordure, diverses et les images de pommes.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant toutes les
** informations nécessaires pour le chargement des textures, y compris le
** contexte mlx et les champs de texture dans la structure du jeu.
*/
void	load_textures(t_game *game)
{
	load_base_textures(game);
	load_border_textures(game);
	load_misc_textures(game);
	load_collect_images(game);
}
