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
unsigned demanderSaisieUnsigned(const char* message, unsigned min, unsigned max){
    
    return 0;
}

void decendreUneBille(unsigned* ptrRangeeDuDessous, size_t case){
    ptrRangeeDuDessous[case + vaADroite()]++;
}

int8_t vaADroite(){
    
}
/*
 * 
 */
int main() {

    // Saisie des données par l'utilisateur
    unsigned nbrDeBilles = demanderSaisieUnsigned("",0,0);
    
    unsigned nbrRangee = demanderSaisieUnsigned("",0,0);
    
    // Simulation
        // Allocation de la memoire des tableaux
        unsigned **ptrTabRangee = malloc(nbrRangee * sizeof(unsigned*));
        
        for(int i = 0; i < nbrRangee; i++){
            // allocation d'un tableau par rangée (de 1 à nbrRangee)
            *(ptrTabRangee[i]) = calloc((i+1), sizeof(unsigned));
        }
        
        
        
        
    
    // Affichage du resultat
    
    
    
    return (EXIT_SUCCESS);
}

