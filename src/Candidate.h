#ifndef DEF_CANDIDATE
#define DEF_CANDIDATE

#include "Interval.h"
#include <vector>
#include "Quadratic.h"
#include <list>
#include "Ordered_list_of_intervals.h"

class Candidate
{
private:
    double cost_up_to_tau;
    int tau;
    Ordered_list_of_intervals z;
    Quadratic quad;
    double pen;

public:
    /**
     * @details Instantiate a last changepoint candidate.
     * @param[in] tau_ Position of the last changepoint candidate.
     * @param[in] z_ The sorted list of intervals on which the candidate achieves the optimal cost.
     * @param[in] cost_up_to_tau_ The optimal cost up to tau_.
     * @param[in] pen_ Minus log-length (of the last segment).
     * @param[in] quad_ Least-squares on the last segment observation(s).
     */
    Candidate(
        int tau_, 
        Ordered_list_of_intervals z_, 
        double cost_up_to_tau_, 
        double pen_, 
        Quadratic quad_
    );
    
    /**
     * @returns The minimum of the cost function.
     */
    double Minimum_of_cost_function();
    
    /**
     * @details Update minus log-length (of the last segment).
     * @param[in] pen_ Value of the new penalty.
     */
    void Set_penalty(
        double pen_
    );

    /**
     * @details Look for the intervals (I) on which the cost function of the last candidate is beaten by the cost function of past candidates. Update the approximated living-set of the last candidate cost function with the complementary of the union of I.
     * @param[in] vector_of_it_candidates Vector of iterators pointing to the candidates.
     * @param[in] D Default living-set.
     */
    void Compare_to_past_candidates (
        std::vector<std::list<Candidate>::iterator> & vector_of_it_candidates, 
        Interval & D
    );

    /**
     * @details Look for the intervals (I) on which the cost function of the current candidate is beaten by the cost function of future candidates.
     * Update the current candidate's living-set by intersecting it with the intersection of I.
     * @param[in] vector_of_it_candidates Vector of iterator that points on candidates.
     * @param[in] chosen_candidates Indices of the candidates chosen for the comparison.
     */
    void Compare_to_future_candidates (
        std::vector<std::list<Candidate>::iterator> & vector_of_it_candidates, 
        std::vector<int> & chosen_candidates
    );
    
    /**
     * @details Update current candidate quad by adding to it least-squares on last observation.
     * @param[in] wt A weight.
     * @param[in] y A point.
     */
    void Add_quadratic(
        double wt, 
        double y
    );
    
    /**
     * @returns The sorted list of intervals on which the candidate achieves the optimal cost (living set)
     */
    Ordered_list_of_intervals GetZ();

    /**
     * @returns Tau of the current candidate.
     */
    int Get_tau();

};


#endif
