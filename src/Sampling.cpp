#include "Sampling.h"
#include "Candidate.h"
#include <iterator>
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>


//- Rand_one -----------------------------------------------------------------//
std::vector<int> Sampling::Rand_one(
    int p, 
    int n, 
    int nb) {   

    return std::vector<int> {std::rand()%(n-p-1)+1+p};
}

//- Rand_without_replacement -------------------------------------------------//
std::vector<int> Sampling::Rand_without_replacement(
    int p, 
    int n, 
    int nb) {  

    int i {0};
    int s;
    std::vector<int> chosen_candidates;
    if (nb+p>= n)
    {
        for(int j {n-1}; j>p ; j--)
        {
            chosen_candidates.push_back(j);
        }
    }
    else
    {
        while (i < nb)
        {
            s = (std::rand()%(n-p-1))+1+p;
            if (find(chosen_candidates.begin(), chosen_candidates.end(), s) == chosen_candidates.end())
            {
                chosen_candidates.push_back(s);
                i+=1;
            }
        }
    }
    return chosen_candidates;
}

//- All ----------------------------------------------------------------------//
std::vector<int> Sampling::All(
    int p, 
    int n, 
    int nb) {

    std::vector<int> chosen_candidates;
    for (int i {n-1}; i>p; i--)
    {
        chosen_candidates.push_back(i);
    }
    return chosen_candidates;
}
