/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_regularity_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:48:03 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:18:05 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Fonction : read_until_newline
** --------------------------------
** Lit un fichier jusqu'à ce qu'elle atteigne un saut de ligne.
**
** fd : Le descripteur de fichier du fichier à lire.
**
** Cette fonction lit un fichier caractère par caractère, en incrémentant un
** compteur à chaque caractère lu, jusqu'à ce qu'elle atteigne un saut de ligne
** ('\n') ou la fin du fichier. Si le descripteur de fichier est invalide
** (c'est-à-dire inférieur à 0), la fonction renvoie -1.
**
** Si la fin du fichier est atteinte avant d'avoir trouvé un saut de ligne et
** que le compteur est supérieur à 0, la fonction renvoie le compteur.
** Autrement, elle renvoie -1 si la fin du fichier est atteinte sans avoir lu
** aucun caractère, ou le compteur si un saut de ligne est trouvé.
**
** Cette fonction est utile pour lire un fichier ligne par ligne, en
** déterminant le nombre de caractères dans chaque ligne.
**
** Retourne : le nombre de caractères lus jusqu'à un saut de ligne ou la fin
** du fichier, ou -1 en cas d'erreur ou si la fin du fichier est atteinte sans
** avoir lu aucun caractère.
*/
int	read_until_newline(int fd)
{
	char	c;
	int		count;
	ssize_t	ret;

	count = 0;
	if (fd < 0)
		return (-1);
	ret = read(fd, &c, 1);
	while (ret > 0)
	{
		count++;
		if (c == '\n')
			break ;
		ret = read(fd, &c, 1);
	}
	if (ret == 0 && count > 0)
		return (count);
	if (ret == 0)
		return (-1);
	return (count);
}

/*
** Fonction : is_regular_grid
** --------------------------
** Vérifie si toutes les lignes d'un fichier ont la même longueur.
**
** path : Le chemin du fichier à vérifier.
**
** Cette fonction ouvre un fichier en lecture seule et lit le fichier ligne par
** ligne, en utilisant la fonction 'read_until_newline'. Elle compare la
** longueur de chaque ligne avec la longueur de la première ligne.
**
** Si une ligne est de longueur différente de la première ligne, la fonction
** ferme le fichier et renvoie 0, indiquant que le fichier ne forme pas une
** grille régulière. Si toutes les lignes ont la même longueur, la fonction
** ferme le fichier et renvoie 1, indiquant que le fichier forme une grille
** régulière.
**
** En cas d'erreur lors de l'ouverture du fichier ou de la lecture du fichier,
** la fonction renvoie -1. Cela peut se produire si le fichier ne peut pas être
** ouvert, ou si la fin du fichier est atteinte avant de trouver une nouvelle
** ligne lors de la lecture de la première ligne.
**
** Cette fonction est utile pour vérifier l'intégrité d'un fichier devant
** former une grille régulière, comme un fichier de carte de jeu.
**
** Retourne : 1 si toutes les lignes du fichier ont la même longueur,
** 0 si une ligne de longueur différente a été trouvée, ou -1 en cas d'erreur.
*/
int	is_regular_grid(char *path)
{
	int	fd;
	int	first_line_length;
	int	line_length;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	first_line_length = read_until_newline(fd);
	if (first_line_length < 0)
	{
		close(fd);
		return (-1);
	}
	line_length = read_until_newline(fd);
	while (line_length != -1)
	{
		if (line_length != first_line_length)
		{
			close(fd);
			return (0);
		}
		line_length = read_until_newline(fd);
	}
	close(fd);
	return (1);
}

/*
** Fonction : check_grid
**
** Description : Vérifie si la grille de la carte est régulière.
**
** Arguments :
**     - file (char *) : Chaîne de caractères représentant le fichier de la
**                        carte du jeu.
**
** Retour :
**     - (int) : 0 si la grille est régulière, sinon une valeur d'erreur
**               correspondante est renvoyée.
**
** Note : La fonction utilise la fonction "is_regular_grid" pour vérifier si
**        la grille de la carte est régulière. Si la valeur de retour de cette
**        fonction est égale à 1, cela signifie que la grille est régulière.
**        Dans ce cas, la fonction renvoie 0 pour indiquer que la grille est
**        régulière. Si la valeur de retour est égale à 0, cela signifie que la
**        grille est irrégulière, et la fonction renvoie une valeur d'erreur
**        correspondante qui est imprimée via la fonction "print_error". Si la
**        valeur de retour est différente de 0 et de 1, cela indique une erreur
**        lors de la vérification de la grille, et la fonction renvoie une
**        autre valeur d'erreur correspondante.
*/
int	check_grid(t_game *game, char *file)
{
	int	grid_status;

	grid_status = is_regular_grid(file);
	if (grid_status != 1)
	{
		if (grid_status == 0)
			return (print_error(game, ERR_IRREGULAR_GRID));
		return (print_error(game, ERR_FILE_CHECK_ERROR));
	}
	return (0);
}
