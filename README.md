# Gemcraft

## Introduction

Notre projet a consisté à créer un jeu de Tower Defense en C.\
Ce jeu est entièrement inspiré du jeu flash Gemcraft, encore disponible à l'adresse suivante : <https://gameinabottle.com/gemcraft1.php>.\
Nous avons suivi un cahier des charges précis qui nous a été donné par notre enseignant de C avancé, [M. Wenjie Fang](https://igm.univ-mlv.fr/~wfang/).

Ce jeu à été réalisé en C, cela veut dire qu'il est, en théorie, compilable sur n'importe quel système d'exploitation.\
En pratique, nous n'avons testé que sur Linux, et nous ne garantissons pas que le jeu fonctionne sur d'autres systèmes d'exploitation.\
Le problème étant aussi que nous avons utilisé la bibliothèque graphique libMLV, qui n'est pas disponible sur tous les systèmes d'exploitation.\

## Lancement du jeu

### Prérequis

Pour pouvoir lancer le jeu, il faut avoir installé la bibliothèque graphique libMLV.\
Pour cela, il faut suivre les instructions données sur le site de la bibliothèque : <https://www-igm.univ-mlv.fr/~boussica/mlv/index.html>.\

### Compilation

Pour compiler le jeu, il vous suffit de lancer la commande `make` à la racine du projet.\
Cela va créer un exécutable `gemcraft` à la racine du projet.\
Vous verrez aussi un dossier `bin` qui contient les fichiers objets générés lors de la compilation.\
Vous pouvez supprimer ce dossier à l'aide de la commande `make clean`.\

### Lancement

Pour lancer le jeu, il vous suffit de lancer la commande `./gemcraft` à la racine du projet.\
Vous avez aussi tout un tas d'options disponibles que voici :

```text
Jeu de Tower Defense en C.

Usage: ./gemcraft [OPTION]...

  -w, --window=WIDTHxHEIGHT     Lance le jeu avec la taille spécifiée.
  -h, --help                    Affiche ce message d'aide et quitte.
  -f, --fullscreen              Lance le jeu en plein écran.
  -d, --difficult-mode          Lance le jeu en mode difficile.
```

## Comment jouer

### But du jeu

Le but du jeu est de survivre le plus longtemps possible.\
Pour cela, vous devez tuer les monstres qui arrivent sur le chemin en plaçant des tours sur le terrain.\
Ces tours vont tirer sur les monstres et les tuer avant qu'ils n'atteignent la sortie.\
Si un monstre atteint la sortie, vous perdez du mana en fonction de son niveau.\
Si vous n'avez plus de mana, vous perdez la partie.\

### Les gemmes

La gemme est l'élément central du jeu.\
C'est celui-ci qui vous permet de faire des dégâts aux monstres.\
Vous pouvez acheter des gemmes dans le menu à droite de l'écran.\
Vous pouvez aussi combiner des gemmes entre elles pour en créer des plus puissantes.\
Plus elles sont puissantes, plus elles coûtent cher et plus elles font de dégâts.\

### Le mana

Le mana est la ressource principale du jeu.\
C'est celui-ci qui vous permet d'acheter des gemmes, de les combiner, de placer des tours, etc.\
Attention, le mana sert aussi de point de vie.\
Si votre mana tombe est inférieur à 0, vous perdez la partie.\
Vous pouvez gagner du mana en tuant des monstres, ou en appuyant sur la touche `Espace` pour passer à la vague suivante.\
Attention, si vous passez à la vague suivante, les monstres de la vague actuelle doivent avoir fini d'apparaître comme précisé plus tôt.\

### Contrôles

Les contrôles sont plutôt simples.\
Les seuls touches du clavier que vous devez utiliser sont la touche `Q` ou `Echap` pour quitter le jeu, et la touche `Espace` pour passer à la vague suivante.\
Attention, pour passer à la vague suivante, les monstres de la vague actuelle doivent avoir fini d'apparaître.\

Pour ce qui est du reste des actions, tout ce passe à la souris.\
Vous avez un menu sur la droite de l'écran qui vous permet de placer des tours, d'acheter des gemmes, de les combiner, etc.\

### Le menu

Le menu est composé de plusieurs éléments différents.\

Tout d'abord, vous avez un boutton ressemblant à une tour, et un autre ressemblant à une gemme.\
Le boutton ressemblant à une tour vous permet de placer une tour sur le terrain si actionné.\
Celui ressemblant à une gemme permet de créer une gemme en fonction du niveau de la gemme sélectionnée.\
Vous avez ensuite un boutton de couleur bleu et contenant un `+` qui vous permet d'améliorer la réserve de mana.\

Ensuite, vous pouvez voir en dessous deux petits bouttons `<` et `>` qui vous permettent de naviguer dans l'inventaire de gemmes.\

Pour finir, tout en bas, vous avez trois cases ressemblant à ceci : **[ ] + [ ] = [ ]**.\
Si vous glissez une gemme dans la première case, et une autre dans la deuxième, vous verrez alors une gemme apparaître dans la troisième case.\
Ceci vous permet de combiner des gemmes entre elles pour en créer des plus puissantes.\

## Retours utilisateurs

Ce jeu à été fait dans le cadre d'un projet universitaire.\
Il y donc possiblement des bugs, des problèmes de gameplay, etc.\
Certains problèmes sont du au sujet du projet, comme le faite que gagner du mana en passant à la vague suivante est trop facile.\
D'autres sont du à des problèmes de conception, comme le faite que le drag and drop des gemmes ne fonctionne pas toujours correctement.\

Si vous avez des retours à nous faire, n'hésitez pas à ouvrir une issue sur le dépôt GitHub du projet.\
Vous pouvez aussi nous contactez par Discord, nos pseudos sont `quentinl03` et `nathanchpln`.\

Nous espérons que vous apprécierez ce jeu autant que nous avons apprécié le développer.\
Bonne partie !
