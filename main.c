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

#define NB_CHOIX_POSSIBLE  2

#define MIN_BILLES 1000
#define MAX_BILLES  10000
#define DEMANDE_NB_BILLES "Entrez le nombre de billes [1000 - 10000] : "

#define MIN_RANGEES 10
#define MAX_RANGEES 30
#define DEMANDE_NB_RANGEE_CAPTEURS "Entrez le nombre de rangees de compteurs [10 - 20]"

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
    
    
    
    return (EXIT_SUCCESS);
}

unsigned demanderSaisieUnsigned(const char* message, unsigned min, 
                                unsigned max){
    
    unsigned saisie = 0;
    clear_stdin();
    
    // affichage du mesage à destination de l'utilisateur
    printf("%s\n", message);
    scanf("%u[0123456789]", &saisie);
    
    printf("Saisie = %u\n", saisie);
    
    while (saisie < min || saisie > max) {
        
        // vidange du buffer
        clear_stdin();
        
        printf("Boucle erreur\n");
        
        // il y a eu une erreur on affiche le message de redemande se saisie
        printf("%s\n", MESSAGE_ERREUR_SAISIE);
        // affichage du mesage à destination de l'utilisateur
        printf("%s\n", message);
        scanf("%u[0123456789]", &saisie);
        
    }
    printf("Next Return\n");
    return saisie;
}

void decendreUneBille(unsigned* ptrCaseGauche){
    (*(ptrCaseGauche + vaADroite()))++;
}

size_t vaADroite(){
    return (size_t)(rand() % NB_CHOIX_POSSIBLE);
}

void clear_stdin(void) {
    fseek(stdin, 0, SEEK_END);
}