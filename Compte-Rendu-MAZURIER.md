# Séance du 14 Décembre 2018 (Séance #1)

Lors de cette séance, j'ai tout d'abord établi la connexion Bluetooth entre mon téléphone et l'Arduino. Pour ce faire, j'ai installé l'IDE Android Studio permettant d'écrire des applications pour Android en langage Java. Pour le code, je me suis basé sur le travail de @OmarAflak qui partage sur son GithuB le code de [son application](https://play.google.com/store/apps/details?id=me.aflak.bluetoothterminal). De base, cette application fait le lien avec un appareil Bluetooth, permet d'envoyer des chaines de caractères et d'en recevoir à l'aide d'un champ de texte (cf. les captures d'écran montrées sur le Play Store). J'ai commencé à modifier le code et ajouter des boutons afin pour obtenir ceci :

![alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/Screenshot_20181214-190624_Smart'%20House.jpg?raw=true "Screenshot de l'app")


Du côté Arduino, un delay manquant nous a fait perdre un peu de temps car les informations envoyées par le téléphone n'arrivaient pas bien à l'Arduino : 
![alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/probl%C3%A8me_delay_14-12.PNG?raw=true "Problème de delay")


Avec le code executé par l'Arduino, on peut à ce stade : allumer et eteindre le chauffage (caractérisé par une LED).
De plus, j'ai connecté la sonette à l'Arduino et lorsque l'on appuie dessus et que l'application est ouverte, un bruit de sonette est joué sur le téléphone.


# Séance du 18 Décembre 2018 (Séance #2)
