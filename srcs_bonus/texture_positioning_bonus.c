/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_positioning_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:04:06 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:58 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Description : La fonction draw_border est utilisée pour dessiner les
**               bordures du jeu à des positions spécifiques.
**
** Paramètres :
** - game      : Pointeur vers la structure du jeu, qui contient les
**               informations de la fenêtre, de la carte et des autres données
**               du jeu.
** - i         : Index de la position sur la carte où la bordure doit être
**               dessinée.
** - position  : Enumération représentant la position de la bordure à dessiner.
**               Les valeurs possibles sont : TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT,
**               BOTTOM_RIGHT, TOP, BOTTOM, LEFT et RIGHT.
**
** Cette fonction ne renvoie pas de valeur. Elle sélectionne la texture
** appropriée en fonction de la position spécifiée et dessine cette texture à
** l'index i sur la carte du jeu, à condition qu'une texture ait été
** sélectionnée.
**
** Remarque : L'index i doit correspondre à une position valide sur la carte.
**            Si aucune texture n'est sélectionnée (c'est-à-dire si la
**            position ne correspond à aucune des valeurs attendues), la
**            fonction ne fait rien.
*/
void	draw_border(t_game *game, int i, t_position position)
{
	void	*texture;

	texture = NULL;
	if (position == TOP_LEFT)
		texture = game->textures.corner_top_left;
	else if (position == TOP_RIGHT)
		texture = game->textures.corner_top_right;
	else if (position == BOTTOM_LEFT)
		texture = game->textures.corner_bottom_left;
	else if (position == BOTTOM_RIGHT)
		texture = game->textures.corner_bottom_right;
	else if (position == TOP)
		texture = game->textures.border_top;
	else if (position == BOTTOM)
		texture = game->textures.border_bottom;
	else if (position == LEFT)
		texture = game->textures.border_left;
	else if (position == RIGHT)
		texture = game->textures.border_right;
	if (texture)
		draw_position_texture(game, i, texture);
}

/*
** Description : Cette fonction dessine une texture à une position spécifique
**               sur la fenêtre de jeu, basée sur l'index du tableau de la
**               carte. Les coordonnées x et y sont calculées à partir de
**               l'index i, de la largeur et de la hauteur de la carte.
**
** Paramètres :
** - game    : Pointeur vers la structure du jeu, qui contient les informations
**             de la fenêtre, de la carte et d'autres informations de jeu.
** - i       : Index de la position dans le tableau de la carte où la texture
**             doit être dessinée.
** - texture : Pointeur vers la texture à dessiner.
**
** Cette fonction ne renvoie pas de valeur. Elle utilise l'API minilibx pour
** dessiner la texture sur la fenêtre de jeu.
**
** Remarque : L'index i doit correspondre à une position valide sur la carte.
**            Les coordonnées x et y sont calculées en multipliant le reste et
**            le quotient de la division euclidienne de i par le nombre de
**            colonnes de la carte, respectivement par la largeur et la
**            hauteur de la carte.
*/
void	draw_position_texture(t_game *game, int i, void	*texture)
{
	int	x;
	int	y;

	x = (i % game->map.sum_columns) * game->map.width;
	y = (i / game->map.sum_columns) * game->map.height;
	mlx_put_image_to_window(game->mlx, game->win1, texture, x, y);
}

/*
** Description : Cette fonction vérifie si l'élément à l'index i dans la carte
**               du jeu correspond à un certain caractère d'élément. Si c'est
**               le cas, elle dessine la texture donnée à cette position dans
**               la fenêtre de jeu.
**
** Paramètres :
** - game    : Pointeur vers la structure du jeu, qui contient les informations
**             de la fenêtre, de la carte et d'autres informations de jeu.
** - i       : Index de la position dans le tableau de la carte où l'élément
**             doit être vérifié et où la texture peut être dessinée.
** - element : Caractère représentant l'élément à vérifier dans la carte du jeu.
** - texture : Pointeur vers la texture à dessiner si l'élément correspond.
**
** Cette fonction ne renvoie pas de valeur. Elle est généralement utilisée pour
** dessiner les éléments du jeu, comme les murs, le joueur, les collectibles,
** etc., en fonction des informations de la carte du jeu.
**
** Remarque : L'index i doit correspondre à une position valide sur la carte.
**            Si l'élément à l'index i ne correspond pas au caractère 'element',
**            la fonction ne fait rien.
*/
void	draw_element(t_game *game, int i, char element, void *texture)
{
	if (game->map.play_map[i] == element)
		draw_position_texture(game, i, texture);
}
