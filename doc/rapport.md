# Projet de Programmation C : Tower Defense

____

- [Projet de Programmation C : Tower Defense](#projet-de-programmation-c--tower-defense)
  - [Manuel Utilisateur](#manuel-utilisateur)
    - [Compilation](#compilation)
    - [Netoyage](#netoyage)
    - [Lancement du programme](#lancement-du-programme)
    - [Les paramètres](#les-paramètres)
  - [Modularisation du code](#modularisation-du-code)
    - [Bin](#bin)
    - [Doc](#doc)
    - [Include & Source](#include--source)
    - [Resources](#resources)
    - [Autres fichiers](#autres-fichiers)
  - [Déroulement du projet](#déroulement-du-projet)
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
unzip prog-chapelain_laborde.zip
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

- `make distclean`: pour supprimmer les fichiers objets.

- `make clean`: pour supprimmer les fichiers objets et l'exécutable.

### Lancement du programme

Pour lancer le programme compilé vous devez utiliser la commande suivante :

```bash
./gemcraft
```

### Les paramètres

Prototype des paramètres de la commande.

> ./gemcraft [-w **INT**x**INT**] [-f] [-d] [-h]

- `-w`, `--width` (faculatif) : Change la taille de la fenêtre. (doit être au minimum de taille 720x480)

- `-f`, `--full-screen` (facultatif) : Lance le jeu en plein écran.

- `-d`, `--difficult-mode` (facultatif) : Active le mode difficile. (passer une vague ne donne pas de mana)

- `-h`, `--help` (facultatif) : Affiche le menu d'aide.

## Modularisation du code

Nous avons séparé notre code en plusieurs dossiers et fichiers afin de rendre le code plus lisible et plus facile à maintenir. Voici l'arborescence abstraite du projet :

<!-- ```text
.
├── bin
├── doc
├── Doxyfile
├── include
│   ├── events
│   ├── graphic
│   └── tools
├── logdev
├── Makefile
├── README.md
├── resources
│   ├── font
│   ├── images
│   └── metadata.tex
└── src
    ├── events
    ├── graphic
    └── tools
 
``` NOT WORK FOR PANDOC -->
- bin
- doc
- include
  - events
  - graphic
  - tools
- logdev
- Makefile
- README.md
- resources
  - font
  - images
  - metadata.tex
- src
  - events
  - graphic
  - tools

### Bin

Contient les fichiers objets générés par la compilation du programme. Ils sont stockés dans ce dossier afin de ne pas polluer le dossier principal.\
Vous trouverez aussi dans ce dossier les fichiers de dépendances générés par le flag `-MMD` du compilateur. Ils permettent de recompiler automatiquement les fichiers qui ont été modifiés. Ce flag permet de ne pas avoir à écrire à la main les dépendances de chaque fichier.\
Vous verrez aussi que dans ce dossier, l'arboréscence des dossiers `include` et `src` est reproduite. Cela permet de garder une arborescence propre et de ne pas avoir à modifier les chemins d'accès aux fichiers objets dans le Makefile.

### Doc

Dans ce dossier, vous trouverez la documentation technique du projet ainsi que ce rapport.\
Vous pourrez aussi trouver dans le sous-dossier `html` la documentation générée par Doxygen.\
Pour que tel soit le cas, je vous invite à utiliser la commande `make doxygen`. (Vous devez avoir Doxygen d'installé sur votre machine)

### Include & Source

Dans ces deux dossiers, vous trouverez respectivement les fichiers d'en-tête et les fichiers sources du programme.\
Dans ces dossiers, vous trouverez aussi des sous-dossiers qui permettent de séparer les fichiers en fonction de leur utilité.\
Voici une description de ces sous-dossiers :

- **events** : Contient toute la gestion des événements avec un module permettant de stocker les events de la libMLV de manière plus simple. Cela permet aussi d'éviter d'avoir des fonctions de récupération d'événement en vrac dans la boucle principale. D'autre modules permettant la gestion d'interactions entre les événement joueur et le code. Enfin, nous avons un module entier dédié à la partie `DragAndDrop` permmettant de faire glisser visuellement les objets à l'aide de la souris.

- **graphic** : Possède tous ce qui est lié à l'affichage graphique. Séparé en différent modules qui gèrent une grande partie de l'affichage. L'affichage général ce situe dans le module `graphic` et il y a aussi un module `window` permettant de séparer les différentes parties de l'interface graphique pour pouvoir différencier la carte de l'inventaire sur la droite.

- **tools** : Ce dernier est utilisé pour stocker des modules utilitaires comme le `DynamicArray` qui est un tableau de stockage multi-type utilisé pour le stockage des données de la carte. Ou encore, le module `Utils` contentant des fonctions pratiques tel qu'un structure de coordonnées ou bien de directions. Le module `TimeManager` permet de gérer les usages de la structure `timespec` de `<time.h>`. Cette fonction est utilisé, entre autres choses, pour gérer les timers des vagues et des projectiles.

- Enfin, il nous reste les documents "en vrac" le dossier src. Il représente le squellette du projet comme les vagues la carte, inventaire, la gestion du mana par exemple. Tous ces modules sont utlisés par la module game stockant la boucle principale du jeu. Il y a aussi le module `main` qui est le point d'entrée du programme. Il permet de lancer le jeu et de gérer les paramètres de la ligne de commande.

### Resources

Contient les fichiers de ressources utilisés par le programme. Dans notre cas il s'agit uniquement de la police d'écriture utilisée pour le menu. Elle est stockée dans le dossier `resources/fonts`.\
Nous avons aussi adapté nos fonctions pour pouvoir utiliser des images à la place par exemple des dessins pour les tours ou les monstres. Nous avons cependant préféré ne pas les utiliser pour une question de facilité de développement.\
Vous avez aussi peut être remarqué le fichier `metadata.tex` et le dossier `images`. Ils sont utilisés dans le Makefile pour générer ce rapport au format PDF via pandoc.\

### Autres fichiers

- **Doxyfile** : Fichier de configuration de Doxygen. Il permet de générer la documentation API du projet.

- **logdev** : Fichier dump des logs de développement. Il permet de garder une trace des modifications effectuées sur le projet. Vous pouvez aussi retrouver les logs de développement sur le dépôt Git du projet.

- **Makefile** : Fichier de compilation du projet. Il permet de compiler le projet, de nettoyer les fichiers objets et l'exécutable. Il permet aussi de générer la documentation Doxygen et de générer ce rapport au format PDF via pandoc.\
Vous avez un descriptif plus haut dans le rapport sur l'utilisation de ce fichier.

## Déroulement du projet

<!-- TODO : Expliquer réélement les étapes de dév du projet -->

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
