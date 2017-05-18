/*
 -------------------------------------------------------------------------------
 Laboratoire : Laboratoire no 5
 Fichier     : main.c
 Auteur(s)   : Adrien Allemand et Kamil Amrani
 Date        : 11 Mai 2017

 But         : 

 Remarque(s) : 

 Compilateur : MinGW-g++ 5.3.0
 -------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

/* Paramètre utilisés pour l'affichage */
#define NBR_CHOIX_POSSIBLE 2
#define NBR_ETOILES 15
#define ESPACE ' '
#define SYMBOLE_GRAPH '*'
#define SEPARATEUR ' '

/* Paramètres pour la table de Galton*/
#define MIN_BILLES 1000
#define MAX_BILLES 10000
#define DEMANDE_NB_BILLES "Entrez le nombre de billes [1000 - 10000] : "
#define MIN_RANGEES 10
#define MAX_RANGEES 30
#define DEMANDE_NB_RANGEE_CAPTEURS "Entrez le nombre de rangees de compteurs [10 - 20] : "
#define MESSAGE_ERREUR_SAISIE "Saisie incorrecte. Veuillez SVP recommencer."


/* FONCTIONS */

size_t vaADroite();


/*
 * @brief           Demande à l'utilisateur d'entrer un entier non signé compris
 *                  dans une fourchette.Effectue tout les contrôles nécessaire.
 *                  Retourne la valeurs une fois saisie correctement.
 * 
 * @param message   Le message à afficher avant la saisie de l'utilisateur
 * @param min       Le minimum de la fourchette autorisee (minimum compris)
 * @param max       Le maximum de la fourchette autorisee (maximum compris
 * 
 * @return          Le nombre entier non signé, compris entre les bornes, saisit
 *                  par l'utilisateur.
 */
unsigned demanderSaisieUnsigned(const char* message, unsigned min, unsigned max);

void decendreUneBille(unsigned* ptrCaseGauche);

void clear_stdin(void);

size_t indexValeurMax(unsigned* tab,size_t t);

void afficher(unsigned** tab, size_t taille);

void galtonTable();
/*
 * 
 */
int main() {
    
    // set de la seed qu isera utilisée pour le random
    srand((uint8_t) time(NULL)); 
    
    
    // Saisie des données par l'utilisateur
    unsigned nbrDeBilles = demanderSaisieUnsigned(DEMANDE_NB_BILLES,
                                                  MIN_BILLES, MAX_BILLES);
    
    unsigned nbrRangees = demanderSaisieUnsigned(DEMANDE_NB_RANGEE_CAPTEURS,
                                                MIN_RANGEES, MAX_RANGEES);
    
    
    /* Allocation */
    // Allocation de la memoire du tableau de pointeurs* de rangées
    unsigned** ptrTabRangee = (unsigned**) malloc(nbrRangees * 
                                                  sizeof(unsigned*));       /* HACK */

    // test que le malloc plante
    if(!ptrTabRangee){
        return EXIT_FAILURE;
    }

    // allocation d'un tableau par rangée (de 1 à nbrRangee)
    for(size_t i = 0; i < nbrRangees; i++){

        ptrTabRangee[i] = (unsigned*) calloc((i+1), 
                                                sizeof(unsigned));

        // test que le calloc si le calloc plante
        if(!ptrTabRangee[i]){

            // si il plante on doit désalouer la mémoire des calloc())
            do {
                free(ptrTabRangee[i]);
                i--;
            } while(i != 0);
            
            // on doit également désallouer la mémoire du malloc()
            free(ptrTabRangee);
            return EXIT_FAILURE;
        }
    }

    // met la valeur du premier capteur à nbrDeBilles
    **ptrTabRangee = nbrDeBilles;

    /* SIMULATION */
    // boucle sur les rangées (sauf la dernière où les billes s'arrêtent)
    for(size_t i = 0; i < nbrRangees - 1; i++){
        
        // boucle sur les colonnes
        for(size_t j = 0; j <= i; j++){
            
            //boucle sur les billes d'une case
            for(unsigned k = 0; k < ptrTabRangee[i][j]; k++){
                decendreUneBille(ptrTabRangee[i + 1] + j);
            }
        }
    }
    
    // Affichage du resultat
    
    afficher(ptrTabRangee, nbrRangees);
    
    return (EXIT_SUCCESS);
}

unsigned demanderSaisieUnsigned(const char* message, unsigned min, 
                                unsigned max){
    
    unsigned estPasOk = 1;
    unsigned saisieUnsigned = 0;
    
    do {
        // vidange du buffer
        clear_stdin();
        
        
        // affichage du mesage à destination de l'utilisateur
        printf("%s", message);
        
        // ne récupert que les 9 caractères qui ne sont pas chiffres
        scanf("%u[0123456789]", &saisieUnsigned);
        
        if(saisieUnsigned < min || saisieUnsigned > max) {
            // il y a eu une erreur on affiche le message de redemande se saisie
            printf("%s\n", MESSAGE_ERREUR_SAISIE);
        } else {
            estPasOk = 0;
        }
    } while (estPasOk);
    
    return saisieUnsigned;
}

void decendreUneBille(unsigned* ptrCaseGauche){
    (*(ptrCaseGauche + vaADroite()))++;
}

size_t vaADroite(){
    return (size_t)(rand() % NBR_CHOIX_POSSIBLE);
}

void clear_stdin(void) {
    fseek(stdin, 0, SEEK_END);
}

size_t indexValeurMax(unsigned* tab,size_t taille) {
    
    // au debut max = index 0
    size_t max = 0;
    
    // cherche le max
    for(size_t i = 1; i < taille; i++) {
        if(tab[i] > tab[max]) {
            max = i;
        }
    }
    
    return max;
}


void afficher(unsigned** tab, size_t taille) {
    
    
    /* AFFICHAGE DES CAPTEURS*/
    size_t maxValueIndex = indexValeurMax(tab[taille - 1], taille);
    
    int nbrCharParCol = (int)log10(**tab) + 1;
    
    for(size_t i = 0; i < taille; i++) {
        for(size_t j = 0; j <= i; j++) {
            printf("%*u", nbrCharParCol, tab[i][j]);
            
            // séparateur entre deux colonnes
            if(j < i){
                printf("%c", SEPARATEUR);
            }
        }
        printf("\n");
    }

    /* AFFICHAGE DES ETOILES */
    // les colonnes (NBR_ETOILES)
    for(size_t i = 0; i < NBR_ETOILES; i++) {
        
        // les cases de la dernière ligne de capteurs
        for(size_t j = 0; j < taille; j++) {
            
            
            if((double)tab[taille - 1][j] / (double)tab[taille - 1][maxValueIndex] * NBR_ETOILES > i + 0.5) {
                printf("%*c",nbrCharParCol, SYMBOLE_GRAPH);
            } else {
                printf("%*c",nbrCharParCol, ESPACE);
            }
            
            // séparateur entre deux colonnes
            if(j < taille - 1){
                printf("%c", SEPARATEUR);
            }
        }
        printf("\n");
    }
}
