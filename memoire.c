#include <stdio.h>
//on definit la taille de la memoire totale à 4096 Mo
#define MEMOIRE 4096
//la memoire disponible est initialisée à la valeur de MEMOIRE
int memoireDisponible = MEMOIRE;
//on assume que le nombre de processus est fixe à 10 pour simplifier la gestion de la mémoire
int processes[10];
//fonction pour afficher le menu principal
void menu() {
    printf("\n1. Allouer de la memoire\n");
    printf("2. Liberer de la memoire\n");
    printf("3. Afficher la memoire en utilisation\n");
    printf("4. Afficher la memoire libre\n");
    printf("5. Verifier l'etat d'occupation de la memoire\n");
    printf("6. Quitter\n");
    printf("-> ");
}
//fonction pour allouer de la memoire à un processus
void allouerMemoire(int process[2]) {
    //on choisit le processus auquel on veut allouer de la memoire
    printf("Entrez le numero du processus (0-9): ");
    scanf("%d", &process[0]);
    //control de saisie pour s'assurer que le numero du processus est compris entre 0 et 9
    while (process[0] < 0 || process[0] > 9) {
        printf("Erreur: le numero du processus doit etre compris entre 0 et 9.\n");
        printf("Veuillez entrer un numero de processus valide: ");
        scanf("%d", &process[0]);
    }
    //on demande la valeur de memoire à allouer au processus choisi
    printf("Entrez la valeur a allouer: ");
    scanf("%d", &process[1]);
    //control de saisie pour s'assurer que la valeur de memoire est positive et ne depasse pas la memoire disponible
    while (process[1] > memoireDisponible || process[1] <= 0) {
        printf("Erreur: la valeur saisie est invalide.\n");
        printf("Veuillez entrer une valeur positive inferieure ou egale a %d: ", memoireDisponible);
        scanf("%d", &process[1]);
    }
    //on alloue la memoire au processus choisi et on met à jour la memoire disponible
    processes[process[0]] += process[1];
    memoireDisponible -= process[1];
    printf("%d Mo alloues au processus %d\n", process[1], process[0]);
}
//fonction pour liberer de la memoire d'un processus
void libererMemoire(int valeur, int process[2]) {
    printf("Liberation globale ou locale de memoire?\n");
    char choice;
    printf("Entrez 'g' pour globale ou 'l' pour locale: ");
    scanf(" %c", &choice);
    if (choice == 'g') {
        // liberation globale
        //on traque la memoire liberee
        int lib = 0;
        //on demande la valeur de memoire à liberer
        printf("Entrez la valeur a liberer: ");
        scanf("%d", &valeur);
        //control de saisie pour s'assurer que la valeur de memoire est positive et ne depasse pas la memoire totale moins la memoire disponible
        while (valeur <= 0 || valeur > MEMOIRE - memoireDisponible) {
            printf("Erreur: la valeur saisie est invalide.\n");
            printf("Veuillez entrer une valeur positive inferieure ou egale a %d: ", MEMOIRE - memoireDisponible);
            scanf("%d", &valeur);
        }
        //on libere 1 Mo pour chaque processus repetitivement jusqu'à ce que la valeur totale soit libérée
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
    } else if (choice == 'l') {
        // liberation locale
        //on demande le numero du processus auquel on veut liberer de la memoire
        printf("Entrez le numero du processus (0-9): ");
        scanf("%d", &process[0]);
        //on demande la valeur de memoire à liberer
        printf("Entrez la valeur a liberer: ");
        scanf("%d", &valeur);
        //control de saisie pour s'assurer que la valeur de memoire est positive et ne depasse pas la memoire utilisee par le processus
        while (valeur <= 0 || valeur > processes[process[0]]) {
            printf("Erreur: la valeur saisie est invalide.\n");
            printf("Veuillez entrer une valeur positive inferieure ou egale a %d: ", processes[process[0]]);
            scanf("%d", &valeur);
        }
        //on libere la memoire du processus
        processes[process[0]] -= valeur;
    } else {
        printf("Choix invalide.\n");
        return;
    }
    //on met à jour la memoire disponible après la liberation
    memoireDisponible += valeur;
    printf("%d Mo liberes\n", valeur);
}
//fonction pour afficher la memoire utilisee
void afficherMemoireUtilisee() {
    int memoireUtilisee = MEMOIRE - memoireDisponible;
    printf("Memoire utilisee: %d Mo\n", memoireUtilisee);
}
//fonction pour afficher la memoire disponible
void afficherMemoireDisponible() {
    printf("Memoire libre: %d Mo\n", memoireDisponible);
}
//fonction pour verifier l'etat d'occupation de la memoire
void verifierEtatOccupation() {
    //pourcentage d'occupation de la memoire
    int occupation = ((MEMOIRE - memoireDisponible) * 100) / MEMOIRE;
    if (occupation <= 70) {
        printf("Etat d'occupation: normal\n");
    } else if (occupation < 90) {
        printf("Etat d'occupation: eleve\n");
    } else {
        printf("Etat d'occupation: critique\n");
    }
    for (int i = 0; i < 10; i++) {
        //on affiche uniquement les processus qui utilisent de la memoire
        if (processes[i] > 0) {
            printf("Processus %d: %d Mo\n", i, processes[i]);
        }
    }
}

int main() {
    //valeur pour le choix de l'utilisateur dans le menu, initialisée à 0
    int choix = 0;
    //"PID" du processus et la valeur de memoire à allouer
    int process[2] = {0, 0};
    //valeur pour la memoire à liberer, initialisée à 0
    int valeur = 0;
    do {
        menu();
        scanf("%d", &choix);
        //on dirige le programme vers la fonction correspondante au choix de l'utilisateur
        switch (choix) {
            case 1:
                allouerMemoire(process);
                break;
            case 2:
                libererMemoire(valeur, process);
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
                //on quitte le programme lorsque l'utilisateur choisit l'option 6
                printf("Vous avez quitté le programme.\n");
                break;
            default:
                //on affiche un message d'erreur si l'utilisateur entre un choix invalide
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 6);
    return 0;
}