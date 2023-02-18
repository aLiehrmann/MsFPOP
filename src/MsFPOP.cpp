#include <vector>
#include <iostream>
#include "MsFPOP.h"
#include "Candidate.h"
#include <algorithm>
#include <cmath>
#include <list>
#include <limits>
#include "Sampling.h"
#include "Ordered_list_of_intervals.h"
#include "Interval.h"

//- Constructor --------------------------------------------------------------//
MsFPOP::MsFPOP(
    std::vector<double> y_,
    double beta_,
    double alpha_,
    std::vector<int> (*sampling_method_)(int, int, int),
    int sampling_method_parameter_, 
    std::vector<double>  wt_) {
        
    y     = y_;
    n     = y_.size();
    d     = Interval(*std::min_element(y_.begin(), y_.end()), *std::max_element(y_.begin(), y_.end()));
    beta  = beta_;
    alpha = alpha_;
    y.insert(y.begin(), 0);
    if (wt_.size()==1 && wt_[0] == 0)
    {
        wt = std::vector<double> (y.size(), 1);
    }
    else
    {
        wt = wt_;
        wt.insert(wt.begin(), 0); 
    }
    cp                        = std::vector<int> (y.size(), 0);
    sampling_method           = sampling_method_;
    sampling_method_parameter = sampling_method_parameter_;
}

//- changepoints_search ------------------------------------------------------//
void MsFPOP::Search() {
    std::list<Candidate> list_of_candidates {Candidate(0,  Ordered_list_of_intervals (d), 0, 0, Quadratic())};
    double F;
    int t_hat;
    double min_candidate;
    int index;
    std::vector<int> chosen_candidates;
    std::vector<std::list<Candidate>::iterator> vector_of_it_candidates;
    for (int t {1}; t<y.size(); t++)
    {   
        /*
            We initialize a vector of iterators.
            Each iterator points to a changepoint candidate in list_of_candidates.
            At this step, the last element of the vector does not point to any changepoint candidate.
        */
        std::vector<std::list<Candidate>::iterator> vector_of_it_candidates (list_of_candidates.size()+1);
        index = 0;
        for (auto it_candidate {list_of_candidates.begin()}; it_candidate != list_of_candidates.end(); ++it_candidate)
        {
            vector_of_it_candidates[index] = it_candidate;
            index+=1;
        }

        /*
            (1) The least-squares for the last segment is updated for all changepoint candidates still considered.
            
            (2) The log-length penalty for the last segment is updated for all changepoint candidates still considered.
            
            (3) we update the minimum cost of segmentation and associated changepoint candidate.
        */
        F = std::numeric_limits<double>::max();
        for (int i {0}; i<vector_of_it_candidates.size()-1; i++)
        {
            (*vector_of_it_candidates[i]).Add_quadratic(wt[t], y[t]); //(1)
            (*vector_of_it_candidates[i]).Set_penalty(-beta * std::log(t-(*vector_of_it_candidates[i]).Get_tau())); //(2)
            min_candidate = (*vector_of_it_candidates[i]).Minimum_of_cost_function(); 
            if (min_candidate < F) //(3)
            {
                F     = min_candidate;
                t_hat = (*vector_of_it_candidates[i]).Get_tau();
            }
        }

        /*
            (1) We save the position of the last changepoint candidate that minimizes the cost of segmentation up to the point t.
            
            (2) A new changepoint candidate is introduced at time step t.
            
            (3) The last element of array_of_candidates is now pointing to the recently introduced changepoint candidate.
        */
        cp[t] = t_hat; //(1)
        list_of_candidates.push_back( Candidate(t, Ordered_list_of_intervals (d), F+alpha, 0, Quadratic())); //(2)
        vector_of_it_candidates[vector_of_it_candidates.size()-1] = --list_of_candidates.end(); //(3)

 
        //- We update the the last candidate living-set. -----------------//
        (*vector_of_it_candidates.back()).Compare_to_past_candidates(vector_of_it_candidates, d);
        
        //- We update each changepoint candidate with changepoint candiates --// 
        //- introduced after it. ---------------------------------------------//
        for (auto i{0}; i<vector_of_it_candidates.size()-2; i++)
        {
            chosen_candidates = sampling_method(i, vector_of_it_candidates.size()-1, sampling_method_parameter);
            (*vector_of_it_candidates[i]).Compare_to_future_candidates(vector_of_it_candidates, chosen_candidates);
        }
        
        //- changepoint candidates whose living-set is empty are pruned. -----//
        list_of_candidates.erase(std::remove_if(list_of_candidates.begin(), list_of_candidates.end(), [](Candidate & a) {
            return a.GetZ().Is_empty();
        }), list_of_candidates.end());

     }

}

//- Retreive_changepoints ----------------------------------------------------//
std::vector<int> MsFPOP::Retreive_changepoints() {
    std::vector<int> list_of_changepoints;
    int i (y.size()-1);
    while (cp[i] != 0)
    {
        list_of_changepoints.push_back(cp[i]);
        i = cp[i];
    }
    std::reverse(list_of_changepoints.begin(), list_of_changepoints.end());
    list_of_changepoints.push_back(y.size()-1);
    return list_of_changepoints;
}
