#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Livre {
    int id;
    char titre[100];
    char auteur[100];
    char genre[50];
    bool disponible;
    struct Livre *next;
} Livre;

typedef struct Utilisateur {
    int id;
    char nom[100];
    char adresse[200];
    char email[100];
    char telephone[20];
    struct Utilisateur *next;
    struct Utilisateur *prev;
} Utilisateur;

typedef struct Emprunt {
    int idLivre;
    int idUtilisateur;
    struct Emprunt *next;
} Emprunt;

typedef struct Queue {
    Emprunt *front;
    Emprunt *rear;
} Queue;

// Prototypes des fonctions
Livre* ajouterLivre(Livre* head, int id, char* titre, char* auteur, char* genre);
Livre* supprimerLivre(Livre* head, int id);
Livre* rechercherLivre(Livre* head, int id);
Utilisateur* ajouterUtilisateur(Utilisateur* head, int id, char* nom, char* adresse, char* email, char* telephone);
Utilisateur* supprimerUtilisateur(Utilisateur* head, int id);
Utilisateur* rechercherUtilisateur(Utilisateur* head, int id);
Queue* ajouterEmprunt(Queue* queue, int idLivre, int idUtilisateur);
Queue* retournerLivre(Queue* queue, int idLivre, int idUtilisateur);
void afficherLivres(Livre* head);
void afficherUtilisateurs(Utilisateur* head);
void afficherEmprunts(Queue* queue);
int compterLivres(Livre* head);

void menuAdmin(Livre** biblio, Utilisateur** users, Queue* emprunts);
void menuUtilisateur(Livre* biblio, Utilisateur* users, Queue* emprunts);

int main()
{
    Livre* biblio = NULL;
    Utilisateur* users = NULL;
    Queue* emprunts = (Queue*)malloc(sizeof(Queue));
    emprunts->front = emprunts->rear = NULL;

    int choix;
    do {
        printf("-------Menu Principal-------\n");
        printf("1. Menu Admin\n");
        printf("2. Menu Utilisateur\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                menuAdmin(&biblio, &users, emprunts);
                break;
            case 2:
                menuUtilisateur(biblio, users, emprunts);
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);

    return 0;
}

void menuAdmin(Livre** biblio, Utilisateur** users, Queue* emprunts) {
    int choix;
    do {
        printf("-------Menu Admin-------\n");
        printf("1. Ajouter un livre\n");
        printf("2. Ajouter un utilisateur\n");
        printf("3. Afficher les livres\n");
        printf("4. Afficher les utilisateurs\n");
        printf("5. Compter les livres\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                int id;
                char titre[100], auteur[100], genre[50];
                printf("ID du livre: ");
                scanf("%d", &id);
                printf("Titre: ");
                scanf(" %[^\n]", titre);  // Lire la chaîne avec des espaces
                printf("Auteur: ");
                scanf(" %[^\n]", auteur);
                printf("Genre: ");
                scanf(" %[^\n]", genre);
                *biblio = ajouterLivre(*biblio, id, titre, auteur, genre);
                break;
            }
            case 2: {
                int id;
                char nom[100], adresse[200], email[100], telephone[20];
                printf("ID de l'utilisateur: ");
                scanf("%d", &id);
                printf("Nom: ");
                scanf(" %[^\n]", nom);
                printf("Adresse: ");
                scanf(" %[^\n]", adresse);
                printf("Email: ");
                scanf(" %[^\n]", email);
                printf("Téléphone: ");
                scanf(" %[^\n]", telephone);
                *users = ajouterUtilisateur(*users, id, nom, adresse, email, telephone);
                break;
            }
            case 3:
                afficherLivres(*biblio);
                break;
            case 4:
                afficherUtilisateurs(*users);
                break;
            case 5:
                printf("Nombre des livres est : %d\n", compterLivres(*biblio));
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

void menuUtilisateur(Livre* biblio, Utilisateur* users, Queue* emprunts) {
    int choix;
    do {
        printf("-------Menu Utilisateur-------\n");
        printf("1. Emprunter un livre\n");
        printf("2. Retourner un livre\n");
        printf("3. Afficher les livres\n");
        printf("4. Afficher les emprunts\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                int idLivre, idUtilisateur;
                printf("ID du livre à emprunter: ");
                scanf("%d", &idLivre);
                printf("ID de l'utilisateur: ");
                scanf("%d", &idUtilisateur);
                Livre* livre = rechercherLivre(biblio, idLivre);
                if (livre && livre->disponible) {
                    emprunts = ajouterEmprunt(emprunts, idLivre, idUtilisateur);
                    livre->disponible = false;
                    printf("Livre emprunté avec succès.\n");
                } else {
                    printf("Livre non disponible ou non trouvé.\n");
                }
                break;
            }
            case 2: {
                int idLivre, idUtilisateur;
                printf("ID du livre à retourner: ");
                scanf("%d", &idLivre);
                printf("ID de l'utilisateur: ");
                scanf("%d", &idUtilisateur);
                emprunts = retournerLivre(emprunts, idLivre, idUtilisateur);
                Livre* livre = rechercherLivre(biblio, idLivre);
                if (livre) {
                    livre->disponible = true;
                    printf("Livre retourné avec succès.\n");
                }
                break;
            }
            case 3:
                afficherLivres(biblio);
                break;
            case 4:
                afficherEmprunts(emprunts);
                break;
            case 0:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
}

Livre* ajouterLivre(Livre* head, int id, char* titre, char* auteur, char* genre) {
    Livre* nouveauLivre = (Livre*)malloc(sizeof(Livre));
    nouveauLivre->id = id;
    strcpy(nouveauLivre->titre, titre);
    strcpy(nouveauLivre->auteur, auteur);
    strcpy(nouveauLivre->genre, genre);
    nouveauLivre->disponible = true;
    nouveauLivre->next = head;
    return nouveauLivre;
}

Livre* supprimerLivre(Livre* head, int id) {
    Livre* temp = head;
    Livre* prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        return head;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return head;

    prev->next = temp->next;
    free(temp);
    return head;
}

Livre* rechercherLivre(Livre* head, int id) {
    Livre* current = head;
    while (current != NULL) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

int compterLivres(Livre* head) {
    int count = 0;
    Livre* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

Utilisateur* ajouterUtilisateur(Utilisateur* head, int id, char* nom, char* adresse, char* email, char* telephone) {
    Utilisateur* nouvelUtilisateur = (Utilisateur*)malloc(sizeof(Utilisateur));
    nouvelUtilisateur->id = id;
    strcpy(nouvelUtilisateur->nom, nom);
    strcpy(nouvelUtilisateur->adresse, adresse);
    strcpy(nouvelUtilisateur->email, email);
    strcpy(nouvelUtilisateur->telephone, telephone);
    nouvelUtilisateur->next = head;
    if (head != NULL)
        head->prev = nouvelUtilisateur;
    nouvelUtilisateur->prev = NULL;
    return nouvelUtilisateur;
}

Utilisateur* supprimerUtilisateur(Utilisateur* head, int id) {
    Utilisateur* temp = head;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        if (head != NULL)
            head->prev = NULL;
        free(temp);
        return head;
    }

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) return head;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    if (temp->prev != NULL)
        temp->prev->next = temp->next;

    free(temp);
    return head;
}

Utilisateur* rechercherUtilisateur(Utilisateur* head, int id) {
    Utilisateur* current = head;
    while (current != NULL) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

Queue* ajouterEmprunt(Queue* queue, int idLivre, int idUtilisateur) {
    Emprunt* nouvelEmprunt = (Emprunt*)malloc(sizeof(Emprunt));
    nouvelEmprunt->idLivre = idLivre;
    nouvelEmprunt->idUtilisateur = idUtilisateur;
    nouvelEmprunt->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = nouvelEmprunt;
    } else {
        queue->rear->next = nouvelEmprunt;
        queue->rear = nouvelEmprunt;
    }

    return queue;
}

Queue* retournerLivre(Queue* queue, int idLivre, int idUtilisateur) {
    Emprunt* temp = queue->front;
    Emprunt* prev = NULL;

    while (temp != NULL) {
        if (temp->idLivre == idLivre && temp->idUtilisateur == idUtilisateur) {
            if (prev == NULL) {
                queue->front = temp->next;
            } else {
                prev->next = temp->next;
            }
            if (temp == queue->rear) {
                queue->rear = prev;
            }
            free(temp);
            return queue;
        }
        prev = temp;
        temp = temp->next;
    }

    return queue;
}

void afficherLivres(Livre* head) {
    Livre* current = head;
    while (current != NULL) {
        printf("ID: %d, Titre: %s, Auteur: %s, Genre: %s, Disponible: %d\n",
               current->id, current->titre, current->auteur, current->genre, current->disponible);
        current = current->next;
    }
}

void afficherUtilisateurs(Utilisateur* head) {
    Utilisateur* current = head;
    while (current != NULL) {
        printf("ID: %d, Nom: %s, Adresse: %s, Email: %s, Téléphone: %s\n",
               current->id, current->nom, current->adresse, current->email, current->telephone);
        current = current->next;
    }
}

void afficherEmprunts(Queue* queue) {
    Emprunt* current = queue->front;
    while (current != NULL) {
        printf("ID Livre: %d, ID Utilisateur: %d\n", current->idLivre, current->idUtilisateur);
        current = current->next;
    }
}
