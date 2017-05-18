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

uint8_t vaADroite();
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

void decendreUneBille(unsigned* ptrRangeeDuDessous, size_t noCase);

/*
 * 
 */
int main() {

    // set de la seed qu isera utilisée pour le random
    srand((uint8_t) time(NULL)); 
    
    
    // Saisie des données par l'utilisateur
    unsigned nbrDeBilles = demanderSaisieUnsigned(DEMANDE_NB_BILLES,
                                                  MIN_BILLES,MAX_BILLES);
    
    unsigned nbrRangees = demanderSaisieUnsigned(DEMANDE_NB_RANGEE_CAPTEURS,
                                                MIN_RANGEES, MAX_RANGEES);
    
    
    // Simulation
        // Allocation de la memoire du tableau de pointeurs* de rangées
        unsigned **ptrTabRangee = malloc(nbrRangees * sizeof(unsigned*));/* HACK */
        
        // test que le malloc s'est bien passé
        if(!**ptrTabRangee){
            return EXIT_FAILURE;
        } else {
            
            // allocation d'un tableau par rangée (de 1 à nbrRangee)
            for(size_t i = 0; i < nbrRangees; i++){
                
                *(ptrTabRangee[i]) = (unsigned*) calloc((i+1), sizeof(unsigned));
                
                // test que le calloc s'est bien passé
                if(ptrTabRangee[i]){
                    
                    // si il plante on doit désalouer la mémoire des calloc())
                    while(i >= 0){
                        free(*ptrTabRangee[i]);
                        i--;
                    }
                    // on doit également désallouer la mémoire du malloc()
                    free(**ptrTabRangee);
                }
            }
        }
        
        
        
        
    
    // Affichage du resultat
    
    
    
    return (EXIT_SUCCESS);
}

unsigned demanderSaisieUnsigned(const char* message, unsigned min, unsigned max){
    
    return 0;
}

void decendreUneBille(unsigned* ptrRangeeDuDessous, size_t case){
    ptrRangeeDuDessous[case + vaADroite()]++;
}

uint8_t vaADroite(){
    return (uint8_t)(rand() % NB_CHOIX_POSSIBLE);
}