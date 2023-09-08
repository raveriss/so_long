/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_counter_display_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:55:36 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:37 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Description : Cette fonction remplit une chaîne de caractères avec la
**               représentation en chiffres d'un entier donné.
**
** Paramètres :
** - str : La chaîne de caractères à remplir.
** - n : L'entier dont on souhaite obtenir la représentation en chiffres.
** - index : L'indice à partir duquel commencer à remplir la chaîne de
**           caractères.
**
** Cette fonction prend en paramètre une chaîne de caractères 'str', un entier
** 'n' et un indice 'index'. Elle remplit la chaîne 'str' avec la
** représentation en chiffres de l'entier 'n', en commençant à partir de
** l'indice 'index'. La fonction traite différents cas pour gérer les entiers
** nuls, négatifs et spéciaux. Si 'n' est égal à 0, la fonction place
** simplement le caractère '0' à l'indice 'index' dans la chaîne 'str'. Si 'n'
** est égal à -2147483648 (la valeur minimale pour un entier sur la plupart
** des systèmes), la fonction place le chiffre '8' à l'indice 'index' et
** décrémente 'index' d'une unité. Ensuite, elle divise 'n' par 10 pour
** éliminer le dernier chiffre. Si 'n' est négatif, la fonction place le
** caractère '-' au début de la chaîne 'str' et effectue une inversion de
** signe sur 'n'. Enfin, la fonction effectue une boucle tant que 'index' est
** supérieur ou égal à 0 et 'n' est différent de 0. À chaque itération, elle
** place le chiffre correspondant à l'unité de 'n' dans la chaîne 'str' à
** l'indice 'index', puis divise 'n' par 10 pour éliminer ce chiffre et
** décrémente 'index' d'une unité. Une fois que tous les chiffres de 'n' ont
** été placés dans 'str', la fonction se termine.
**
** Remarque : Cette fonction est utile lorsque vous souhaitez convertir un
**            entier en sa représentation en chaîne de caractères pour
**            l'affichage ou la manipulation ultérieure de cette valeur.
*/
static void	fill_str(char *str, int n, int index)
{
	if (n == 0)
	{
		str[index] = '0';
		return ;
	}
	if (n == -2147483648)
	{
		str[index--] = '8';
		n /= 10;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (index >= 0 && n != 0)
	{
		str[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
}

/*
** Description : Cette fonction compte le nombre de chiffres dans un entier
** donné.
**
** Paramètre :
** - n : L'entier dont on souhaite compter le nombre de chiffres.
**
** Renvoie : Le nombre de chiffres dans l'entier (int).
**
** Cette fonction prend un entier en paramètre et compte le nombre de chiffres
** présents dans cet entier. Elle initialise une variable 'digits' à 0 pour
** stocker le compte. Si l'entier est égal à 0, la fonction renvoie 1, car 0
** est considéré comme ayant un seul chiffre. Si l'entier est négatif, la
** variable 'digits' est incrémentée de 1 pour prendre en compte le signe
** négatif. Ensuite, la fonction effectue une boucle tant que l'entier n'est
** pas égal à 0. À chaque itération, elle divise l'entier par 10 pour éliminer
** le dernier chiffre et incrémente la variable 'digits' de 1. Une fois que
** l'entier a été entièrement parcouru, la fonction renvoie la valeur finale
** de 'digits', qui représente le nombre de chiffres dans l'entier.
**
** Remarque : Cette fonction peut être utile dans diverses situations où vous
**            devez manipuler ou analyser le nombre de chiffres dans un
**            entier, par exemple lors de la conversion d'un entier en chaîne
**            de caractères.
*/
static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/*
** Description : Cette fonction convertit un entier en sa représentation en
**               chaîne de caractères (string).
**
** Paramètres :
** - game : Un pointeur vers la structure de jeu (t_game) contenant les
**          informations du jeu.
** - n : L'entier à convertir en chaîne de caractères.
**
** Retour : Un pointeur vers la chaîne de caractères représentant l'entier, ou
**          NULL en cas d'échec d'allocation mémoire.
**
** Cette fonction prend en paramètre un pointeur vers la structure de jeu
** 'game' et un entier 'n'. Elle détermine le nombre de chiffres dans l'entier
** 'n' en utilisant la fonction 'count_digits'. Ensuite, elle alloue
** dynamiquement de la mémoire pour une chaîne de caractères 'str' de taille
** équivalente au nombre de chiffres plus un pour le caractère de fin de
** chaîne '\0'. Si l'allocation échoue, la fonction renvoie NULL. Sinon, elle
** initialise le dernier caractère de 'str' à '\0' et utilise la fonction
** 'fill_str' pour remplir le reste de la chaîne 'str' avec la représentation
** en chiffres de l'entier 'n'. Enfin, elle met à jour le pointeur
** 'game->player.itoa_result' avec 'str' et renvoie 'str'.
**
** Remarque : Cette fonction est utile lorsque vous souhaitez convertir un
**            entier en sa représentation en chaîne de caractères pour
**            l'affichage ou la manipulation ultérieure de cette valeur.
*/
char	*ft_itoa(t_game *game, int n)
{
	char	*str;
	int		digits;

	digits = count_digits(n);
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str)
	{
		free(str);
		print_error(game, "itoa alloc error\n");
		close_window(game);
	}
	str[digits] = '\0';
	fill_str(str, n, digits - 1);
	game->player.itoa_result = str;
	return (str);
}

/*
** Description : Cette fonction dessine le nombre de mouvements effectués
**               à l'écran du jeu.
**
** Paramètre :
** - game : Un pointeur vers la structure de jeu (t_game) contenant les
**          informations du jeu.
**
** Cette fonction prend en paramètre un pointeur vers la structure de jeu
** 'game'. Elle utilise la fonction 'ft_itoa' pour convertir le nombre de
** mouvements 'game->player.moves_count' en une chaîne de caractères
** représentant ce nombre. Ensuite, elle utilise la fonction 'mlx_string_put'
** pour afficher le texte "Move :" à la position (game->map.width - 50, 27)
** avec une couleur blanche (0xFFFFFF). Elle affiche également la chaîne de
** caractères 'moves_string' à la position (game->map.width - 7, 28) avec la
** même couleur. Enfin, elle libère la mémoire allouée pour 'moves_string' à
** l'aide de 'free' et met à jour 'moves_string' à NULL.
**
** Remarque : Cette fonction est utile pour afficher le nombre de mouvements
**            effectués par le joueur à l'écran du jeu.
*/
void	draw_moves_count(t_game *game)
{
	char	*moves_string;

	moves_string = ft_itoa(game, game->player.moves_count);
	if (moves_string == NULL)
	{
		free(moves_string);
		print_error(game, "allocerror\n");
	}
	mlx_string_put(game->mlx, game->win1, game->map.width - 50, 27,
		0xFFFFFF, "Move :");
	mlx_string_put(game->mlx, game->win1, game->map.width - 7, 28, 0xFFFFFF,
		moves_string);
	free(moves_string);
	moves_string = NULL;
}
