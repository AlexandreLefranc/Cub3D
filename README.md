# Table of content

[[toc]]

# Cub3D

# Plan

- Initialiser la structure globale
- Parser et sauvegarder les informations dans la structure globale
- Verifier la validite de la map
- Initialiser la fenetre
- Initialiser les textures
- Definir les hooks
- Lancer le jeu
- Boucler en attendant les hooks

# Parser

```
Verifier le nom du fichier
Ouvrir le fichier

Pour chaque ligne non-vide:
	Split la ligne
	Regarder l'identifiant
	Verifier la validite de l'identifiant
	Verifier la validite de la valeur
	Copier la valeur la ou il faut
	Repeter jusqu'a avoir recupere toutes les infos

A partir de la premier ligne non vide:
	(1) Copier la ligne dans un tableau
	Si la prochaine ligne n'est pas vide ou EOF, aller a (1)

Verifier la map:
	Verifier les caracteres inconnus
	Verifier l'unicite de la position de depart
	Verifier que la map soit fermee
		Comment ?
			- Option facile mais moins naturel: Considerer l'espace comme un mur.
				Etendre les lignes pour qu'elles fassent toutes la meme longueur
				Remplacer les espaces pour des 1
				On retombe sur le parsing de so_long.
			- Option dure mais naturelle: Verifier la contiguite des murs exterieurs
```

# Raycasting

## Links

https://lodev.org/cgtutor/raycasting.html

## Maths

$$2+3$$

# Plan de developpement

1. Mettre en place le parsing
2. Creer un affichage de minimap, utile pour debug. Depend de (1)
3. Gerer les inputs, dont la souris, et refresh la minimap. Depend de (1, 2)
4. Gerer les collisions, systeme de porte. Depend de (1, 2, 3)
5. Mettre en place le ray casting connaissant les conditions. Depend de (1)
6. Integerer la minimap et le rendu dans la boucle d'event.
