# Puzzle-Bobble
# ---- FRANCAIS ----

## Informations générales:
Ce projet a été écrit par CHIDA Omar et BATTIKH Linda en utilisant C languge,
sous le titre Méthodoligies et conecption
Le projet utilise la librairie SDL, et le SDL_tff pour montrer le texte,
Sans SDL_tff Le score ne s'affichera probablement pas et vous devrez remplacer `#define TEXT` par
`#undef TEXT` afin d'éviter les erreurs de compilation:
Le logiciel est conçu pour fonctionner avec la bibliothèque SDL_tff et sans cela en activant ou désactivant le TEXT

## POUR INSTALLER SDL_ttf (c'est facile) *
Pour la machine Linux, vous devez ouvrir un terminal et taper:

`sudo apt-get installer libsdl-ttf2.0-dev`</br>
`sudo apt-get installer libfreetype6-dev`

## Architecture de projet:
main: entrée principale du jeu tout commence à partir de là
GameManager: responsable et gestionnaire de tous les objets de jeu et responsable de la logique
Et le nettoyage quand la sortie se produit
Conseil: Responsable de ce qui est à l'intérieur du tableau (comme la flèche, l'animation et toutes les balles)
Ballon: Responsable de la gestion du déplacement de la balle et de toutes les autres funictionnalités de la balle
Animation: Module écrit pour gérer toutes les animations du jeu et le rendre facile à travailler avec eux
utils: contient une fonction aléatoire et loadSprite
liste: module de liste liée qui gère la liste des boules liées

**PS:** Board, Ball, Animation: contient la fonction pour libérer la mémoire et éviter les fuites de mémoire!

## Le projet contient:
-Menu principal
-Signe du mode joueur
-Mode multijoueur
-Score montrant
-Quelques animations

##  Bugs connus:
-Aucun

## Contrôles :
- Flèche gauche et droite et espace pour lancer la balle
- Q et D et L pour lancer la balle pour le deuxième joueur
- Échapper pour revenir au menu principal pendant l'ingame.

## Jeu compilé:
Ce paquet contient un jeu compilé (prêt à être lancé) (uniquement pour les utilisateurs de Linux)
Pour les autres plates-formes, vous devez recompiler après avoir lié toutes les bibliothèques.

Merci d'avoir lu
Auteur: CHIDA Omar

## Images:
![Alt text](pictures/main_menu.png?raw=true "Main Menu")
![Alt text](pictures/sp.png?raw=true "Single Player")
![Alt text](pictures/mp.png?raw=true "Multi Player")

# ---- ENGLISH ----

## General Info:
This project has been written by CHIDA Omar and BATTIKH Linda using C languge,
under the subject Méthodoligies et conecption
The project use the library SDL, and the SDL_tff for showing the text,
Without SDL_tff The score won't probably show and you should replace `#define TEXT` with
`#undef TEXT` in order to avoid compile errors:
The software is designed to work with SDL_tff library and without it by enabling or disabling TEXT

*TO INSTALL SDL_ttf (its easy)*
for linux machine you need to open a terminal and type:
	
`sudo apt-get install libsdl-ttf2.0-dev`</br>
`sudo apt-get install libfreetype6-dev`

## Project Architecture:
main : main game entry all start from there
GameManager : responsible and manager of all game objects and also responsible for the logic
	And the clean up when the exit occurs
Board: Responsible for what's inside the board (like the arrow, animation and all the balls)
Ball: Responsible for managing ball movment and all other ball funictionality
Animation: Module written to manage all game animations and make it easy to work with them
utils: contain random function and loadSprite
list: linked-list module that manage linked list of balls

**PS:** Board, Ball,Animation: contain the function to free the memory and to avoid memory leaks!

## The project contains:
-Main menu
-Signle player mode
-Multiplayer mode
-Score showing
-Some animations

## Known Bugs:
-None

## Controls : 
- left and right arrow and space to launch the ball
- Q and D and L to launch the ball for the second player
- Escape to return to main menu while ingame.

## Compiled game:
This package contain compiled (ready to launch) game (only for linux users)
For other platforms you should re-compile after linking all the libraries.

Thanks for reading
Author: CHIDA Omar

## Pictures:
![Alt text](pictures/main_menu.png?raw=true "Main Menu")
![Alt text](pictures/sp.png?raw=true "Single Player")
![Alt text](pictures/mp.png?raw=true "Multi Player")
