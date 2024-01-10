#include "Candidate.h"
#include "Quadratic.h"
#include "Interval.h"
#include <vector>
#include <array> 
#include <iostream> 
#include <list>
#include <limits>
#include <cmath>
#include "Ordered_list_of_intervals.h"

//- Constructor --------------------------------------------------------------//
Candidate::Candidate(
    int tau_, 
    Ordered_list_of_intervals z_, 
    double cost_up_to_tau_, 
    double pen_, 
    Quadratic quad_) {

    tau            = tau_;
    z              = z_;
    cost_up_to_tau = cost_up_to_tau_;
    pen            = pen_;
    quad           = quad_;
}

//- Minimum_of_cost_function -------------------------------------------------//
double Candidate::Minimum_of_cost_function() {   
    return quad.Minimum() + pen + cost_up_to_tau;
}

//- update_penalty_on_last_segment -------------------------------------------//
void Candidate::Set_penalty(double pen_) {
    pen = pen_;
}

//- add_new_point ------------------------------------------------------------//
void Candidate::Add_quadratic(
    double wt, 
    double y) {
    
    quad.Add_coef(wt*pow(y,2), -2*wt*y, wt);
}

//- Compare_to_past_candidate ------------------------------------------------//
void Candidate::Compare_to_past_candidates (
    std::vector<std::list<Candidate>::iterator> & vector_of_it_candidates, 
    Interval & D) {

    std::list<Interval> list_of_intervals;
    Interval interval;
    Quadratic new_quad;
    for (int i {0}; i<vector_of_it_candidates.size()-1; i++)
    {   
        new_quad = (*vector_of_it_candidates[i]).quad - quad;
        new_quad.Add_coef((*vector_of_it_candidates[i]).cost_up_to_tau - cost_up_to_tau,0,0);
        interval = new_quad.Negative_interval();
        if (!interval.IsEmpty_or_singleton())
        {
            list_of_intervals.push_back(interval); 
        }
    }
    Ordered_list_of_intervals list_of_merged_intervals (list_of_intervals);
    list_of_merged_intervals.Complementary_in(D); 
    z = list_of_merged_intervals;
}

//- Compare_to_future_candidate ----------------------------------------------//
void Candidate::Compare_to_future_candidates (
    std::vector<std::list<Candidate>::iterator> & vector_of_it_candidates, 
    std::vector<int> & chosen_future_candidates) {
    
    std::list<Interval> list_of_intervals;
    Interval intersection_of_intervals;
    Interval interval;
    Quadratic new_quad;
    if (pen != std::numeric_limits<double>::infinity())
    {
        for (int indexe_chosen_future_candidates: chosen_future_candidates)
        {
            new_quad = quad - (*vector_of_it_candidates[indexe_chosen_future_candidates]).quad;
            new_quad.Add_coef(pen+cost_up_to_tau-((*vector_of_it_candidates[indexe_chosen_future_candidates]).pen+(*vector_of_it_candidates[indexe_chosen_future_candidates]).cost_up_to_tau),0,0);
            interval = new_quad.Negative_interval();
            if (!interval.IsEmpty_or_singleton())
            {
                list_of_intervals.push_back(interval);
            }
            else
            {
                z = Ordered_list_of_intervals();
                break;
            }    
        }
        if (!(z.Is_empty())) 
        {
            intersection_of_intervals = Interval(list_of_intervals);
            z.Intersect_with(intersection_of_intervals);
        }
    }
}

//- Get_last_changepoint_position --------------------------------------------//
int Candidate::Get_tau() {
    return tau;
}

//- get_candidate_area_of_life -----------------------------------------------//
Ordered_list_of_intervals Candidate::GetZ() {
    return z;
}