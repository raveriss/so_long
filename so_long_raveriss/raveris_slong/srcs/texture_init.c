/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:53:24 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 12:11:50 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Mise à jour de la texture dans le jeu.
**
** Cette fonction a pour but de détruire l'image actuelle liée à la texture et de
** la remplacer par une nouvelle image, à partir d'un fichier XPM donné en
** argument.
**
** @param t_game *game - Pointeur vers la structure de jeu contenant entre autres
** l'instance mlx et les dimensions de la carte.
**
** @param void **texture - Pointeur vers la texture à mettre à jour.
**
** @param char *filename - Nom du fichier XPM à utiliser pour générer la nouvelle
** image de texture.
**
** Après appel de cette fonction, la texture pointée est mise à jour avec la
** nouvelle image issue du fichier XPM.
*/
void	update_texture(t_game *game, void **texture, char *filename)
{
	mlx_destroy_image(game->mlx, *texture);
	*texture = mlx_xpm_file_to_image(game->mlx,
			filename, &game->map.width, &game->map.height);
}

/*
** Description : Cette fonction initialise les textures du jeu en réinitialisant
**               les pointeurs des différentes textures à NULL.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient les pointeurs des
**          textures utilisées par le jeu.
**
** Cette fonction ne renvoie pas de valeur. Elle initialise les pointeurs des
** textures du mur, du joueur, des collectibles, du sol et de l'ennemi à NULL.
**
** Remarque : Cette fonction est généralement appelée au début du programme pour
**            s'assurer que les pointeurs des textures sont initialisés à NULL
**            avant d'être utilisés par d'autres fonctions du jeu.
*/
void	initialize_game_textures(t_game *game)
{
	game->textures.wall = NULL;
	game->textures.player = NULL;
	game->textures.colect = NULL;
	game->textures.colect = NULL;
	game->textures.ground = NULL;
	game->textures.killer = NULL;
}

/*
** Description : Cette fonction initialise les textures des coins du jeu en
**               réinitialisant les pointeurs des différentes textures des
**               coins à NULL.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient les pointeurs des
**          textures des coins utilisées par le jeu.
**
** Cette fonction ne renvoie pas de valeur. Elle initialise les pointeurs des
** textures des coins supérieur gauche, supérieur droit, inférieur gauche
** et inférieur droit à NULL.
**
** Remarque : Cette fonction est généralement appelée au début du programme
**            pour s'assurer que les pointeurs des textures des coins sont
**            initialisés à NULL avant d'être utilisés par d'autres fonctions
**            du jeu.
*/
void	initialize_game_corner_textures(t_game *game)
{
	game->textures.corner_top_left = NULL;
	game->textures.corner_top_right = NULL;
	game->textures.corner_bottom_left = NULL;
	game->textures.corner_bottom_right = NULL;
}

/*
** Description : Cette fonction initialise les textures des bordures du jeu en
**               réinitialisant les pointeurs des différentes textures des
**               bordures à NULL.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient les pointeurs des
**          textures des bordures utilisées par le jeu.
**
** Cette fonction ne renvoie pas de valeur. Elle initialise les pointeurs des
** textures des bordures supérieure, inférieure, gauche et droite à NULL.
**
** Remarque : Cette fonction est généralement appelée au début du programme
**            pour s'assurer que les pointeurs des textures des bordures sont
**            initialisés à NULL avant d'être utilisés par d'autres fonctions
**            du jeu.
*/
void	initialize_game_border_textures(t_game *game)
{
	game->textures.border_top = NULL;
	game->textures.border_bottom = NULL;
	game->textures.border_left = NULL;
	game->textures.border_right = NULL;
}

/*
** Description : Cette fonction initialise la texture de la sortie du jeu en
**               réinitialisant le pointeur de la texture de sortie à NULL.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient le pointeur de la
**          texture de sortie utilisée par le jeu.
**
** Cette fonction ne renvoie pas de valeur. Elle initialise le pointeur de la
** texture de sortie à NULL.
**
** Remarque : Cette fonction est généralement appelée au début du programme pour
**            s'assurer que le pointeur de la texture de sortie est initialisé à
**            NULL avant d'être utilisé par d'autres fonctions du jeu.
*/
void	initialize_game_exit_texture(t_game *game)
{
	game->textures.exit = NULL;
}
