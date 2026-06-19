#include <stdio.h>
#include <string.h>

void menu() {
    printf("\n1. Consulter votre solde\n");
    printf("2. Faire un depot\n");
    printf("3. Effectuer un retrait\n");
    printf("4. Consulter votre historique\n");
    printf("5. Quitter\n");
    printf("-> ");
}

void Solde(int solde) {
    printf("Votre solde s'eleve a %d\n", solde);
}

int Depot(int solde, char ligne[]) {
    int montant;
    printf("Quel montant voulez-vous deposer dans votre compte ? ");
    scanf("%d", &montant);
    solde += montant;
    printf("Depot de %d reussi. Nouveau solde : %d\n", montant, solde);
    sprintf(ligne, "Depot de %d reussi. Nouveau solde : %d\n", montant, solde);
    return solde;
}

int Retrait(int solde, char ligne[]) {
    int montant;
    printf("Quel montant voulez-vous retirer de votre compte ? ");
    scanf("%d", &montant);
    while (montant > solde) {
        printf("Le montant ne peut etre superieur au solde. Veuillez saisir un nouveau montant : ");
        scanf("%d", &montant);
    }
    solde -= montant;
    printf("Retrait de %d reussi. Nouveau solde : %d\n", montant, solde);
    sprintf(ligne, "Retrait de %d reussi. Nouveau solde : %d\n", montant, solde);
    return solde;
}

void Stat(int solde, int nd, int nr) {
    printf("Statistiques:\n");
    printf("Solde final : %d\n", solde);
    printf("Nombre de depots : %d\n", nd);
    printf("Nombre de retraits : %d\n", nr);
}

int main() {
    int solde = 0;
    int rep = 0;
    int nd = 0;
    int nr = 0;
    char histo[1024] = "";
    char ligne[256];
    do {
        menu();
        scanf("%d", &rep);
        switch (rep) {
            case 1:
                goto afficher_solde;
            case 2:
                goto depot;
            case 3:
                goto retrait;
            case 4:
                goto historique;
            case 5:
                goto quitter;
            default:
                printf("Choix invalide.\n");
                goto fin_operation;
        }
        afficher_solde:
            Solde(solde);
            goto fin_operation;
        depot:
            solde = Depot(solde, ligne);
            strncat(histo, ligne, sizeof(histo) - strlen(histo) - 1);
            nd++;
            goto fin_operation;
        retrait:
            solde = Retrait(solde, ligne);
            strncat(histo, ligne, sizeof(histo) - strlen(histo) - 1);
            nr++;
            goto fin_operation;
        historique:
            if (strlen(histo) == 0) {
                printf("Aucune operation enregistre3e.\n");
            } else {
                printf("Historique:\n");
                printf("%s", histo);
            }
            goto fin_operation;
        quitter:
            break;
        fin_operation:
            ;
    } while (rep != 5);
    Stat(solde, nd, nr);
    return 0;
}