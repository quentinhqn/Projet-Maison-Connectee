# Séance du 14 Décembre 2018 (Séance #1)

Pour la première séance nous avons défini les tâches que chacun réalisera durant les prochaines séances, ainsi que le planning de notre projet.
On a donc réflechi aux composants dont on aurait besoin afin de les commander en avance. J'ai réalisé le design de notre maquette afin de placer les composants aux emplacements qui corresponderaient le plus à notre idée du projet :

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/design.jpg?raw=true "Design")

Ce design nous à aussi permis de nous mettre d'accord sur la structure et la taille de la maquette. Visualiser la maison et la dessiner nous a aussi donné de nouvelles idées comme : un thermostat, un capteur de pluie ou un capteur de mouvement exterieur pour allumer la lumière à l'arrivé de quelqu'un. Ces modifications ne sont pas encore sur le design car ce seront des ajouts supplémentaires si le reste fonctionne.


J'ai par la suite réalisé une maquette en carton (voir ci dessous) afin de dimensionner la structure totale et la taille adéquate pour les différents composants.

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/maquette1.jpg?raw=true "Maquette")


On voulait d'abord partir sur un interrupteur pour détecter l'ouverture de la porte (et des fenêtres), mais on s'est rendu compte qu'avec l'interrupteur il fallait exercer une force pour la fermer la porte, elle s'ouvrait donc toute seule si on la lachait.
On a donc pensé à un interrupteur "artisanal", c'est à dire une tige métalique placée sur la porte qui vient taper une plaque reliée à la masse quand la porte est fermée.
Le code correspondant se trouve [ici](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Projet/ouverturePorte/ouverturePorte.ino).
      
      
# Séance du 18 Décembre 2018 (Séance #2)

Au début de cette séance, j'ai réalisé des mesures sur la maquette pour placer tous les composants. J'ai placer le capteur de mouvement à différents endroits et fait des tests pour trouver là où il marchait le mieux. 

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/MiseEnPlace_Capteur.jpg?raw=true "Capteur")
      


J'ai ensuite éssayé de placer le moteur qui servira de verrou à différents endroits pour fermer convenablement la porte.
En placant la LED qui devait servire d'ampoule pour eclairer la pièce, je me suis rendu compte que les petites LED n'étaient pas assez puissante pour qu'on les voit, il faut donc des LED plus grosses.

En placant les composants que l'ont avait deja, jai remarqué qu''il manquait de place dans la maquette que j'ai ralisée, j'ai donc décidé dagrandir la pièce et donc de supprimer la seconde pièce de l'étage pour ne faire qu'une pièce par étage.

Par la suite j'ai programmé le servomoteur en liaison avec l'application pour pouvoir controler la fermeture et l'ouverture du verrou. J'ai rencontré un problème pour trouver le bon angle de fermeture car le moteur n'est pas assez précis si on lui donne l'angle auquel on veut qu'il se place. 
Il y a aussi fallu changer l'application et créer une nouvelle case dans l'application déédie au verrou.
