---
header-includes:
  - \usepackage{algorithmic}
---


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

## Maths du raycasting

On a notre vecteur position $\overrightarrow{pos}$
$$
\overrightarrow{pos} =
	\begin{pmatrix}
	pos_x \\
	pos_y
	\end{pmatrix}
$$

On a notre vecteur direction $\overrightarrow{dir}$

$$
\overrightarrow{dir} =
	\begin{pmatrix}
	dir_x \\
	dir_y
	\end{pmatrix}
$$

et son vecteur $\overrightarrow{plane}$ etant une rotation de $\pi/2$ de $\overrightarrow{dir}$

$$
\overrightarrow{plane} =
	\begin{pmatrix}
	plane_x \\
	plane_y
	\end{pmatrix}
	=
	\begin{pmatrix}
	- 0.66 \times dir_y \\
	0.66 \times dir_x
	\end{pmatrix}
$$

A partir de ces donnees et de la carte, nous devons faire un rendu de la scene.

Voici les grandes etapes. Pour chaque colonne de pixel:

1. Trouver le vecteur unitaire du rayon qu'on lance
2. Determiner la plus courte distance que ce rayon parcours avant de rencontrer un mur. Sauvegarder les coordonnees de l intersection.
3. Determiner l orientation du mur
4. Corriger cette distance pour le fisheye
5. Grace a la distance, determiner la hauteur d affichage du mur sur la colonne de pixel.
6. Grace aux coordonnees de l intersection. Determiner quelle colonne de la texture sera prise pour modele
7. Imprimer de haut en bas sur l image le ciel, puis le nombre de pixel correspondant a la texture, puis le sol.

### Trouver le vecteur unitaire du rayon

Pour une colonne de pixel $x \in [0, \text{ScreenWidth}[$

Definissons la fonction $ray\_deviance(x) \in [-1, 1[$

$$
ray\_deviance(x) = \frac{2 \times x}{\text{ScreenWidth}} - 1
$$

On peut calculer le vecteur $\overrightarrow{ray}$

$$
\overrightarrow{ray} = \overrightarrow{dir} + ray\_deviance(x) \times \overrightarrow{plane}
$$

Le vecteur $\overrightarrow{ray}$ n etant pas unitaire, on le divise par sa norme

$$
\overrightarrow{ray} = \frac{\overrightarrow{dir} + ray\_deviance(x) \times \overrightarrow{plane}}{||\overrightarrow{dir} + ray\_deviance(x) \times \overrightarrow{plane}||}
$$

A ce moment, on definit egalement le sens de changement sur les axes $x$ et $y$, represente par $side_x$ et $side_y$ respectivement:

$$
side_x = sign(ray_x) \\
side_y = sign(ray_y)
$$

Ainsi, $side_x$ et $side_y$ auront pour valeur $-1$ ou $1$.

(Pour une resolution 1800x900, ca met environ 70 microsecondes)



### Determiner la distance, les coordonnees d intersection et le cote intersecte

Afin d eviter de tester les murs pour chaque pixel, rendant le programme tres tres lourd a executer, et donc 

### Corriger la distance pour le fisheye


# Plan de developpement

1. Mettre en place le parsing
2. Creer un affichage de minimap, utile pour debug. Depend de (1)
3. Gerer les inputs, dont la souris, et refresh la minimap. Depend de (1, 2)
4. Gerer les collisions, systeme de porte. Depend de (1, 2, 3)
5. Mettre en place le ray casting connaissant les conditions. Depend de (1)
6. Integerer la minimap et le rendu dans la boucle d'event.
