# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 09:20:17 by raveriss          #+#    #+#              #
#    Updated: 2023/06/01 15:32:03 by raveriss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du fichier exécutable produit par ce Makefile.
NAME = so_long

# Le compilateur C à utiliser.
CC = gcc

# Les options du compilateur C - en l'occurrence, debug (g3), activer tous
# les avertissements (Wall, Wextra) et traiter les avertissements comme des
# erreurs (Werror).
CFLAGS = -g3 -Wall -Wextra -Werror

# wildcard récupère tous les fichiers .c du dossier srcs.
# wildcard est une fonction qui cherche des fichiers correspondant à un modèle
# spécifié.
SRCS = $(wildcard srcs/*.c)

# Pareil pour les fichiers .c du dossier srcs_bonus.
BONUS_SRCS = $(wildcard srcs_bonus/*.c)

# Le répertoire où seront stockés les fichiers objet pour le projet principal.

OBJS_DIR = objs

# Le répertoire où seront stockés les fichiers objet pour la version bonus du
# projet.
BONUS_OBJS_DIR = objs_bonus

# patsubst remplace le pattern srcs/%.c par $(OBJS_DIR)/%.o pour chaque
# élément de $(SRCS).
# patsubst est une fonction qui remplace un modèle spécifié dans une liste de
# mots.
OBJS = $(patsubst srcs/%.c,$(OBJS_DIR)/%.o,$(SRCS))

# Pareil pour les fichiers .c de la version bonus.
BONUS_OBJS = $(patsubst srcs_bonus/%.c,$(BONUS_OBJS_DIR)/%.o,$(BONUS_SRCS))

# Le répertoire contenant la bibliothèque libmlx.
MLX_DIR = mlx

# addprefix ajoute le préfixe $(MLX_DIR)/ à libmlx_Linux.a.
# addprefix est une fonction qui ajoute un préfixe à une liste de mots.
MLX_LIB = $(addprefix $(MLX_DIR)/,libmlx_Linux.a)

# Les options pour lier la bibliothèque libmlx et d'autres bibliothèques
# nécessaires.
MLX = -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# L'objectif principal du Makefile est de créer l'exécutable $(NAME).
all: $(NAME)

# Pour créer l'exécutable, on a besoin de $(MLX_LIB) et des fichiers objet
# $(OBJS). On les lie avec le compilateur.
$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX) -o $(NAME)

# Pour créer chaque fichier objet, on compile le fichier .c correspondant avec
# les options du compilateur. La dépendance '| $(OBJS_DIR)' signifie que le
# répertoire $(OBJS_DIR) doit exister.
$(OBJS_DIR)/%.o: srcs/%.c | $(OBJS_DIR) Makefile
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

# Cette règle crée le répertoire $(OBJS_DIR) s'il n'existe pas déjà.
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

# Pareil pour les fichiers objet de la version bonus et le répertoire
# $(BONUS_OBJS_DIR).

$(BONUS_OBJS_DIR)/%.o: srcs_bonus/%.c | $(BONUS_OBJS_DIR) Makefile
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

# Cette règle crée le répertoire $(BONUS_OBJS_DIR) s'il n'existe pas déjà.
$(BONUS_OBJS_DIR):
	mkdir $(BONUS_OBJS_DIR)

# Cette règle compile la bibliothèque libmlx si elle n'existe pas déjà.
$(MLX_LIB):
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	make -C $(MLX_DIR)

# La règle bonus crée l'exécutable de la version bonus $(NAME)_bonus.
bonus: $(NAME)_bonus

# Pour créer l'exécutable de la version bonus, on a besoin de $(MLX_LIB) et
# des fichiers objet $(BONUS_OBJS). On les lie avec le compilateur.
$(NAME)_bonus: $(MLX_LIB) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(MLX) -o $(NAME)_bonus

# La règle clean supprime les répertoires de fichiers objet.
clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(BONUS_OBJS_DIR)

# La règle fclean supprime les fichiers exécutables en plus de ce que fait la
#  règle clean.
fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_bonus
	rm -rf $(MLX_DIR)

# La règle re exécute d'abord fclean, puis all. Cela a pour effet de nettoyer
# le projet et de le reconstruire à partir de zéro.
re: fclean all

# .PHONY indique que les règles qui suivent ne sont pas liées à des fichiers
# réels. Cela évite des conflits si un fichier portant le même nom qu'une
# règle est créé.
.PHONY: all clean fclean re bonus
