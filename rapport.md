# Projet de Programmation C : Tower Defense
Quentin Laborde & Nathan Chapelain
____
- [Projet de Programmation C : Tower Defense](#projet-de-programmation-c--tower-defense)
  - [Manuel Utilisateur](#manuel-utilisateur)
    - [Compilation](#compilation)
    - [Netoyage](#netoyage)
    - [Lancement du programme](#lancement-du-programme)
    - [Les paramètres](#les-paramètres)
  - [Modularisation du code](#modularisation-du-code)
  - [Avancement du projet](#avancement-du-projet)
    - [Implémentation par rapport au sujet](#implémentation-par-rapport-au-sujet)
      - [Vagues](#vagues)
      - [Projectile](#projectile)
      - [Element](#element)
      - [Makefile](#makefile)
    - [Amelioration](#amelioration)
      - [Drag and Drop](#drag-and-drop)
    - [Menu graphique](#menu-graphique)
      - [TODO](#todo)
  - [Conclusion](#conclusion)
    - [Améliorations possibles](#améliorations-possibles)
      - [Trap](#trap)
      - [wave v2](#wave-v2)
      - [element v2](#element-v2)
    - [Points positifs](#points-positifs)
    - [Points négatifs](#points-négatifs)


## Manuel Utilisateur
### Compilation
Pour lancer le projet, vous devez décompresser l'archive et compiler avec la commande `make`.

```bash
unzip xvf prog-chapelain_laborde.zip
make
```

Si vous dézipez l'archive à la main pensez à aller dans le dossier crée avant d'effectuer la commande `make`.

```bash
# dézipage à la main
cd prog-chapelain_laborde
make
```

### Netoyage

Pour nettoyer le projet une fois l'utilisation terminée vous pouvez utiliser les commandes :

-  `make distclean`: pour supprimmer les fichiers objets.

-  `make clean`: pour supprimmer les fichiers objets et l'exécutable.

### Lancement du programme

Pour lancer le programme compilé vous devez utiliser la commande suivante :

```bash
./gemcraft
```

### Les paramètres

Prototype des paramètres de la commande.

```bash
./gemcraft [-w] [-h]
```

- `-w / --width` (faculative) : Change la largeur de la fenêtre. (doit être minimum de taille #TODO )

- `-h / --help` (facultatif) : Affiche un bref menu d'aide.


## Modularisation du code

Dans notre arboraissance de fichiers nous avons 4 grosses parties :

- `events` : Contenant toute la gestion des événements avec un module permettant de stocker les events de la libMLV de manière plus simple et d'éviter d'avoir des fonction de récupération d'événement en vrac dans la boucle principale. D'autre modules permettant la gestion d'interractions entre les événement joueur et le code. Et enfin nous avons un module entier dédié à la partie DragAndDrop permmettant de faire glisser visuellement les objets.

- `graphic` : Contenant tous se qui est lié à l'affichage graphique. Séparé en différent modules qui gèrent un partie de l'affichage. Et l'affichage général se situe dans le module graphic et il y a aussi un module window permettant de séparer les différentes parties de l'interface graphique pour par exemple différancier la carte de l'inventaire sur la droite.

- `tools` : Contant des fichiers utilisé dans plusieurs modules comme le DynamicArray qui est un tableau de stockage multitype utilisé pour le stockes des données de la carte, le module Utils contentant de fonction pratique tel que structe de coordonnées ou bien de direction. Le module TimeManager est une interface permettant de gérer les fonction utilisant `timespec` afin de faire de la gestion de temps simplifié dans les autre modules.

- Le reste des documents est situé directement dans le dossier src. Il représente le squellette du projet comme les vagues la carte, inventaire, la gestion du mana par exemple. Et tout ses modules sont utlisé dans le module game stockant la boucle principale du jeu. 

## Avancement du projet

Nous avons réalisé l'ensemble des obligation demandé par le sujet mais nous allons les aborder cas par cas dans le suite.

### Implémentation par rapport au sujet
#### Vagues

Les déplacements des vagues ont été implémenté dans leurs intégralités.
Les timers sont réglés comme souhaité dans l'énnoncé.
La touche espace permet bien de déclancher la première vague et le passé à la suivante.
Cependant nous avons interpréter le sujet de la manière suivante : il ne peux pas avoir plus d'une vague en même temps. Cela est aussi pratique pour équilibré le jeu car le fait de gagner du mana en sautant les vague est vite abusé avec la qualibaration du sujet.

#### Projectile


#### Element
#### Makefile
### Amelioration
#### Drag and Drop
### Menu graphique
#### TODO

## Conclusion
### Améliorations possibles
#### Trap
#### wave v2
#### element v2
### Points positifs
### Points négatifs