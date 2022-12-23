# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines a etats finis logicielles
+ Section #  : 1
+ Équipe #   : 17
+ Correcteur : Dorine Dantrun

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(0.5/1.5)__ |

- Identification matérielles? -0.5
- Il manque une colonne décrivant la SORTIE de votre programme dans les différents états de vos FSM -0.5

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0.0/0.5)     |
| Noms de variables décrivent l'intention      | (/0.5)     |
| Noms de fonctions décrivent l'intention      | (/0.5)     |
| __Résultat partiel__                         | __(1.0/1.5)__ |

- pb1: Chiffre magique lignes 94, 95 -0.5

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(0.0/1.0)__ |

- Certains commentaires inutiles -0.5
- Les en-têtes de vos fonctions sont ok mais certaines d'entre-elles n'ont pas été modifiées accordement et d'autres décrivent l'intention de vos fonctions de manière erroné -0.5


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (/0.5)     |
| Indentation uniforme dans le programme       | (0.0/0.5)     |
| __Résultat partiel__                         | __(.5/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1.0/4.0)__ |

- Qu'elle est l'utilité de la librairie stdint.h? -0.5
- La déclaration de constante dans des type int n'est pas forcément nécessaire, vous utilisez de l'espace mémoire inutilement (pb1 et pb2) -0.5 
- const void  ?? 
- pb1: turnLedOff() ne fonctionne pas comme vous le décrivez -1
- pb2: Pas d'assignation direct (PORTA = (1 << PA1);) -1

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (0.0/1.5)     |
| __Résultat partiel__                         | __(1.5/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.0/0.5)     |
| __Résultat partiel__                         | __(1.5/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5.0/5.0)__ |

# Résultat

__Total des points: 12.0/20__

# Commentaires du correcteur:

Voir plus haut

- Attention au plagiat.

# Basé sur le commit suivant
```
commit ce21fb3571b3a3cf767e3e481d5b142d4c551b81
Author: Evan BLANC <evanblanc.pro@icloud.com>
Date:   Fri Sep 16 12:03:01 2022 -0400

    tp2/pb1 and pb2 -- Documenting Code
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
```
.DS_Store
tp/.DS_Store
tp/tp1/.DS_Store
tp/tp1/tp1_evan_ahmed.elf
tp/tp1/tp1_evan_ahmed.elf.map
tp/tp1/tp1_evan_ahmed.hex
tp/tp1/tp1_src.d
tp/tp1/tp1_src.o
tp/tp2/.DS_Store
```

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make: Entering directory '/home/dorine/poly/inf1900-grader/correction_tp2/17/tp/tp2/pb1'
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb1.cpp
pb1.cpp:2:1: warning: "/*" within comment [-Wcomment]
 /* Copyright (c) 2022 
 ^
pb1.cpp:3:1: warning: "/*" within comment [-Wcomment]
 /*
 ^
pb1.cpp:4:1: warning: "/*" within comment [-Wcomment]
 /* All rights reserved to use, copy, modify, and distribute
 ^
pb1.cpp:5:1: warning: "/*" within comment [-Wcomment]
 /* Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
 ^
pb1.cpp:6:1: warning: "/*" within comment [-Wcomment]
 /* INF1900
 ^
pb1.cpp:7:1: warning: "/*" within comment [-Wcomment]
 /* Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc
 ^
avr-gcc -Wl,-Map,pb1_evan_ahmed.elf.map -mmcu=atmega324pa -o pb1_evan_ahmed.elf  pb1.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb1_evan_ahmed.elf pb1_evan_ahmed.hex
make: Leaving directory '/home/dorine/poly/inf1900-grader/correction_tp2/17/tp/tp2/pb1'

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make: Entering directory '/home/dorine/poly/inf1900-grader/correction_tp2/17/tp/tp2/pb2'
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb2.cpp
pb2.cpp:2:1: warning: "/*" within comment [-Wcomment]
 /* Copyright (c) 2022 
 ^
pb2.cpp:3:1: warning: "/*" within comment [-Wcomment]
 /*
 ^
pb2.cpp:4:1: warning: "/*" within comment [-Wcomment]
 /* All rights reserved to use, copy, modify, and distribute
 ^
pb2.cpp:5:1: warning: "/*" within comment [-Wcomment]
 /* Authors: Evan BLANC 2079808 and Ahmed ZGHAL 2068299 - TEAM 17
 ^
pb2.cpp:6:1: warning: "/*" within comment [-Wcomment]
 /* INF1900
 ^
pb2.cpp:7:1: warning: "/*" within comment [-Wcomment]
 /* Polytecnhique Montréal ENGINEERING SCHOOl, Canada, Qc
 ^
avr-gcc -Wl,-Map,pb2_evan_ahmed.elf.map -mmcu=atmega324pa -o pb2_evan_ahmed.elf  pb2.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb2_evan_ahmed.elf pb2_evan_ahmed.hex
make: Leaving directory '/home/dorine/poly/inf1900-grader/correction_tp2/17/tp/tp2/pb2'

```
