#include <stdio.h>
#define MEMOIRE 4096
int memoireDisponible = MEMOIRE;
int processes[10];

void menu() {
    printf("\n1. Allouer de la memoire\n");
    printf("2. Liberer de la memoire\n");
    printf("3. Afficher la memoire en utilisation\n");
    printf("4. Afficher la memoire libre\n");
    printf("5. Verifier l'etat d'occupation de la memoire\n");
    printf("6. Quitter\n");
    printf("-> ");
}

void allouerMemoire(int process[2]) {
    printf("Entrez le numero du processus (0-9): ");
    scanf("%d", &process[0]);
    while (process[0] < 0 || process[0] > 9) {
        printf("Erreur: le numero du processus doit etre compris entre 0 et 9.\n");
        printf("Veuillez entrer un numero de processus valide: ");
        scanf("%d", &process[0]);
    }
    printf("Entrez la valeur a allouer: ");
    scanf("%d", &process[1]);
    while (process[1] > memoireDisponible || process[1] <= 0) {
        printf("Erreur: la valeur saisie est invalide.\n");
        printf("Veuillez entrer une valeur positive inferieure ou egale a %d: ", memoireDisponible);
        scanf("%d", &process[1]);
    }
    processes[process[0]] += process[1];
    memoireDisponible -= process[1];
    printf("%d Mo alloues au processus %d\n", process[1], process[0]);
}

void libererMemoire(int valeur) {
    int lib = 0;
    printf("Entrez la valeur a liberer: ");
    scanf("%d", &valeur);
    while (valeur <= 0 || valeur > MEMOIRE - memoireDisponible) {
        printf("Erreur: la valeur saisie est invalide.\n");
        printf("Veuillez entrer une valeur positive inferieure ou egale a %d: ", MEMOIRE - memoireDisponible);
        scanf("%d", &valeur);
    }
    while (lib < valeur) {
        for (int i = 0; i < 10; i++) {
            if (processes[i] > 0) {
                if (lib < valeur) {
                    processes[i]--;
                    lib++;
                } else {
                    break;
                }
            }
        }
    }
    memoireDisponible += valeur;
    printf("%d Mo liberes\n", valeur);
}

void afficherMemoireUtilisee() {
    int memoireUtilisee = MEMOIRE - memoireDisponible;
    printf("Memoire utilisee: %d Mo\n", memoireUtilisee);
}

void afficherMemoireDisponible() {
    printf("Memoire libre: %d Mo\n", memoireDisponible);
}

void verifierEtatOccupation() {
    printf("Etat d'occupation de la memoire:\n");
    for (int i = 0; i < 10; i++) {
        if (processes[i] > 0) {
            printf("Processus %d: %d Mo\n", i, processes[i]);
        }
    }
}

int main() {
    int choix = 0;
    int process[2] = {0, 0};
    int valeur = 0;
    do {
        menu();
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                allouerMemoire(process);
                break;
            case 2:
                libererMemoire(valeur);
                break;
            case 3:
                afficherMemoireUtilisee();
                break;
            case 4:
                afficherMemoireDisponible();
                break;
            case 5:
                verifierEtatOccupation();
                break;
            case 6:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 6);
    return 0;
}