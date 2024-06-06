# Bibliothèque Gestionnaire

Ce projet est une application de gestion de bibliothèque écrite en C. Il permet aux administrateurs de gérer les livres et les utilisateurs, et aux utilisateurs d'emprunter et de retourner des livres.

## Fonctionnalités

### Menu Administrateur

- **Ajouter un livre** : Permet d'ajouter un nouveau livre à la bibliothèque.
- **Ajouter un utilisateur** : Permet d'ajouter un nouvel utilisateur au système.
- **Afficher les livres** : Affiche la liste de tous les livres disponibles dans la bibliothèque.
- **Afficher les utilisateurs** : Affiche la liste de tous les utilisateurs inscrits.
- **Compter les livres** : Affiche le nombre total de livres dans la bibliothèque.

### Menu Utilisateur

- **Emprunter un livre** : Permet à un utilisateur d'emprunter un livre disponible.
- **Retourner un livre** : Permet à un utilisateur de retourner un livre emprunté.
- **Afficher les livres** : Affiche la liste de tous les livres disponibles dans la bibliothèque.
- **Afficher les emprunts** : Affiche la liste de tous les emprunts en cours.

## Compilation et Exécution

### Prérequis

- Un compilateur C (par exemple, GCC)

### Compilation

Pour compiler l'application, utilisez la commande suivante :

```sh
gcc -o gestion_bibliotheque main.c

