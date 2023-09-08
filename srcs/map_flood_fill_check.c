/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:28:07 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 11:31:35 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Fonction : read_check_map
** ---------------------------------
** Lit le fichier de la carte du jeu et remplit la structure de la carte du jeu.
**
** fd : Descripteur de fichier ouvert pour lire la carte du jeu.
** game : Pointeur vers la structure t_game qui contient l'état actuel du jeu.
**
** Cette fonction lit le fichier de la carte du jeu caractère par caractère.
** Pour chaque caractère, elle effectue les actions suivantes :
**
** 1. Si le caractère est 'E' (exit), elle stocke la position actuelle dans
**    game->map.check_exit_reach.
** 2. Si le caractère n'est pas un saut de ligne ('\n'), elle l'ajoute à la
**    check_map du jeu à l'index actuel, puis elle incrémente l'index.
**
** Le processus se poursuit jusqu'à ce qu'il n'y ait plus de caractères à lire.
** Si une erreur de lecture se produit (ret < 0), la fonction imprime un message
** d'erreur et renvoie -1.
**
** Enfin, la fonction termine la check_map du jeu par '\0' et imprime la carte
** du jeu.
**
** Retourne : 0 si la lecture s'est bien passée, -1 en cas d'erreur de lecture.
*/
int	read_check_map(int fd, t_game *game)
{
	int		ret;
	char	buf[1];
	int		i;

	i = 0;
	ret = read(fd, buf, 1);
	while (ret)
	{
		if (buf[0] == 'E')
			game->map.check_exit_reach = i;
		if (buf[0] != '\n')
		{
			game->map.check_map[i] = buf[0];
			i++;
		}
		ret = read(fd, buf, 1);
	}
	if (ret < 0)
	{
		print_error(game, "Error reading file");
		return (-1);
	}
	game->map.check_map[i] = '\0';
	return (0);
}

/*
** Fonction : allocate_check_map
** ----------------------------------
** Alloue de la mémoire pour la check_map dans la structure du jeu.
**
** game : Pointeur vers la structure t_game qui contient l'état actuel du jeu.
**
** Cette fonction alloue de la mémoire pour la check_map du jeu. La taille
** allouée est le produit du nombre total de lignes et de colonnes de la carte
** du jeu, plus un caractère supplémentaire pour le caractère de fin de chaîne
** '\0'.
**
** La taille est calculée en octets en utilisant sizeof(char), ce qui correspond
** à un octet par caractère.
**
** Si l'allocation échoue (c'est-à-dire si malloc renvoie NULL), la fonction
** imprime un message d'erreur et termine le programme avec le statut 1.
** Note : dans votre contexte, il serait préférable de gérer cette erreur de
** manière plus gracieuse, en fonction de votre architecture de code.
*/
void	allocate_check_map(t_game *game)
{
	game->map.check_map = malloc(sizeof(char)
			* (game->map.sum_lines * game->map.sum_columns + 1));
	if (game->map.check_map == NULL)
	{
		print_error(game, "Memory allocation error\n");
		exit(1);
	}
}

/*
** Fonction : open_file_check
** ------------------------------
** Ouvre un fichier en lecture seule.
**
** argv : Chaîne de caractères contenant le nom du fichier à ouvrir.
**
** Cette fonction tente d'ouvrir le fichier spécifié par argv en mode lecture
** seule (O_RDONLY). Si l'ouverture du fichier échoue (c'est-à-dire si open
** renvoie une valeur négative), la fonction imprime un message d'erreur et
** renvoie -1.
**
** Si l'ouverture du fichier réussit, la fonction renvoie le descripteur de
** fichier retourné par open. Ce descripteur de fichier peut ensuite être
** utilisé pour lire le contenu du fichier.
**
** Retourne : le descripteur de fichier si l'ouverture du fichier réussit, -1 en
** cas d'échec.
*/
int	open_file_check(t_game *game, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		print_error(game, "Error opening file");
		return (-1);
	}
	return (fd);
}

/*
** Fonction : check_flood_fill
** -------------------------------
** Vérifie si le jeu peut être correctement joué.
**
** argv : Nom du fichier contenant la carte du jeu.
** game : Pointeur vers la structure t_game qui contient l'état actuel du jeu.
**
** Cette fonction effectue plusieurs étapes pour vérifier si le jeu peut être
** joué :
**
** 1. Elle tente d'ouvrir le fichier spécifié par argv. Si l'ouverture échoue,
**    elle renvoie -1.
** 2. Elle alloue de la mémoire pour la check_map du jeu.
** 3. Elle lit le fichier de la carte du jeu et remplit la check_map. Si une
**    erreur de lecture se produit, elle renvoie la valeur retournée par
**    read_check_map.
** 4. Elle valide la carte du jeu. Si la carte n'est pas valide, elle renvoie
**    la valeur retournée par validate_map.
**
** Si toutes ces étapes réussissent, la fonction renvoie 0, indiquant que le jeu
** peut être joué. Sinon, elle renvoie une valeur non nulle pour indiquer
** l'erreur.
**
** Retourne : 0 si le jeu peut être joué, une valeur non nulle sinon.
*/
int	check_flood_fill(char *argv, t_game *game)
{
	int	fd;
	int	read_status;
	int	validation_status;

	fd = open_file_check(game, argv);
	if (fd < 0)
		return (-1);
	allocate_check_map(game);
	read_status = read_check_map(fd, game);
	if (read_status != 0)
		return (read_status);
	validation_status = validate_map(game);
	if (validation_status != 0)
		return (validation_status);
	return (0);
}
