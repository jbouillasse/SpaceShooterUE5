# Space Shooter

## À propos du projet
Ce projet est un prototype de jeu d'arcade 2D de type "Space Shooter" développé avec **Unreal Engine 5.8.2** et programmé en **C++**. 

Il a été réalisé dans le cadre du premier TP de l'Université du Québec à Chicoutimi. L'objectif pédagogique principal de ce projet était de s'initier aux flux de travail professionnels en gestion de versions en utilisant conjointement **GitHub** et **Perforce Helix Core**, tout en appliquant des concepts d'architecture logicielle de jeu vidéo (programmation orientée objet, gestion de la mémoire, et séparation C++/Blueprint).

## Fonctionnalités Principales

* **Contrôles Fluides :** Déplacement du vaisseau (haut/bas, gauche/droite) implémenté proprement en C++ via `UFloatingPawnMovement` pour garantir des performances optimales.
* **Difficulté Progressive :** Apparition dynamique d'astéroïdes depuis les bords de l'écran. Le système utilise un gestionnaire de *Timers* personnalisé en C++ qui réduit progressivement le délai d'apparition pour augmenter la difficulté au fil de la partie de manière contrôlée.
* **Système de Combat & Score :** 
  * Les astéroïdes possèdent des points de vie aléatoires (générés à l'apparition).
  * Système de combo récompensant le joueur : chaque astéroïde détruit augmente un multiplicateur de score qui retombe à zéro si le vaisseau subit des dégâts.
* **Animations 2D :** Intégration du module Paper2D d'Unreal Engine pour gérer les animations de destruction. Des acteurs `UPaperFlipbookComponent` indépendants sont générés dynamiquement à la mort des astéroïdes pour jouer des spritesheets d'explosion.
* **Retours Audio & UI :**
  * Retours sonores spatiaux et 2D via `UGameplayStatics` (Tir laser, impacts sur la carlingue, explosions, Game Over).
  * Interface complète (HUD en jeu pour les vies et le score, Menu Principal fonctionnel, Écran de Game Over avec reprise de focus).

## Stack Technique
* **Moteur de jeu :** Unreal Engine 5
* **Langage :** C++ / Blueprints (pour le paramétrage des classes et l'UI)
* **IDE :** JetBrains Rider
* **Gestion de versions :** Git (GitHub) & Perforce

## Crédits & Copyright
**© 2026 Jean-Baptiste HIE.** Tous droits réservés sur le code source C++ et l'architecture logicielle.

*Les assets visuels et sonores du décor proviennent de la plateforme OpenGameArt et pixabay, et certains assets complémentaires ont été générés par intelligence artificielle pour les besoins du prototypage.*
