---- FRANCAIS ----
Puzzy Bobble Projet:

*)Informations g�n�rales:
Ce projet a �t� �crit par CHIDA Mohamed-Omar et BATTIKH Linda en utilisant C languge,
sous le titre M�thodoligies et conecption
Le projet utilise la librairie SDL, et le SDL_tff pour montrer le texte,
Sans SDL_tff Le score ne s'affichera probablement pas et vous devrez remplacer #define TEXT par
#undef TEXT afin d'�viter les erreurs de compilation:
Le logiciel est con�u pour fonctionner avec la biblioth�que SDL_tff et sans cela en activant ou d�sactivant le TEXT

* POUR INSTALLER SDL_ttf (c'est facile) *
Pour la machine Linux, vous devez ouvrir un terminal et taper:

sudo apt-get installer libsdl-ttf2.0-dev
sudo apt-get installer libfreetype6-dev

*) Architecture de projet:
main: entr�e principale du jeu tout commence � partir de l�
GameManager: responsable et gestionnaire de tous les objets de jeu et responsable de la logique
Et le nettoyage quand la sortie se produit
Conseil: Responsable de ce qui est � l'int�rieur du tableau (comme la fl�che, l'animation et toutes les balles)
Ballon: Responsable de la gestion du d�placement de la balle et de toutes les autres funictionnalit�s de la balle
Animation: Module �crit pour g�rer toutes les animations du jeu et le rendre facile � travailler avec eux
utils: contient une fonction al�atoire et loadSprite
liste: module de liste li�e qui g�re la liste des boules li�es

PS: Board, Ball, Animation: contient la fonction pour lib�rer la m�moire et �viter les fuites de m�moire!

*) Le projet contient:
-Menu principal
-Signe du mode joueur
-Mode multijoueur
-Score montrant
-Quelques animations

*) Bugs connus:
-Aucun

*)Contr�les :
- Fl�che gauche et droite et espace pour lancer la balle
- Q et D et L pour lancer la balle pour le deuxi�me joueur
- �chapper pour revenir au menu principal pendant l'ingame.

*) Jeu compil�:
Ce paquet contient un jeu compil� (pr�t � �tre lanc�) (uniquement pour les utilisateurs de Linux)
Pour les autres plates-formes, vous devez recompiler apr�s avoir li� toutes les biblioth�ques.

Merci d'avoir lu
Auteur: CHIDA Mohamed

---- ENGLISH ----
Puzzy Bobble Projet : 

*)General Info:
This project has been written by CHIDA Mohamed-Omar and BATTIKH Linda using C languge,
under the subject M�thodoligies et conecption
The project use the library SDL, and the SDL_tff for showing the text,
Without SDL_tff The score won't probably show and you should replace #define TEXT with
#undef TEXT in order to avoid compile errors:
The software is designed to work with SDL_tff library and without it by enabling or disabling TEXT

*TO INSTALL SDL_ttf (its easy)*
for linux machine you need to open a terminal and type:
	
sudo apt-get install libsdl-ttf2.0-dev
sudo apt-get install libfreetype6-dev

*)Project Architecture:
main : main game entry all start from there
GameManager : responsible and manager of all game objects and also responsible for the logic
	And the clean up when the exit occurs
Board: Responsible for what's inside the board (like the arrow, animation and all the balls)
Ball: Responsible for managing ball movment and all other ball funictionality
Animation: Module written to manage all game animations and make it easy to work with them
utils: contain random function and loadSprite
list: linked-list module that manage linked list of balls

PS:Board, Ball,Animation: contain the function to free the memory and to avoid memory leaks!

*)The project contains:
-Main menu
-Signle player mode
-Multiplayer mode
-Score showing
-Some animations

*)Known Bugs:
-None

*)Controls : 
- left and right arrow and space to launch the ball
- Q and D and L to launch the ball for the second player
- Escape to return to main menu while ingame.

*)Compiled game:
This package contain compiled (ready to launch) game (only for linux users)
For other platforms you should re-compile after linking all the libraries.

Thanks for reading
Author: CHIDA Mohamed

