#ifndef DEF_SAMPLING
#define DEF_SAMPLING

#include "Candidate.h"
#include <list>
#include <vector>
#include <random>

class Sampling
{
private:
public:    
    /**
     * @returns nb natural numbers randomly drawn in the interval ]0+p,n+p[ (drawing without discount) if nb<n, otherwise all natural numbers within this range. 
     */
    static std::vector<int> Rand_without_replacement(
        int p, 
        int n, 
        int nb
    );
    
    /**
     * @returns one natural number randomly drawn in the interval ]0+p,n+p[.
     * @param[in] nb not used in this method.
     */
    static std::vector<int> Rand_one(
        int p, 
        int n, 
        int nb
    );
    
    /**
     * @returns all the natural numbers of the interval ]0+p,n+p[.
     * @param[in] nb not used in this method.
     */
    static std::vector<int> All(
        int p, 
        int n, 
        int nb
    );
};
#endif
