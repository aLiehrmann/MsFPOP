#ifndef DEF_MSIPELT
#define DEF_MSPELT

#include <vector>

class MsPELT
{
private:
    std::vector<double> y;
    int n;
    double beta;
    double alpha;
    std::vector<double> wt;
    std::vector<int> cp;
    std::vector<double> K;
    std::vector<double> css;
    std::vector<double> cs;
    std::vector<double> Q;
    std::vector<int> nb_candidates;
    
public:
    /**
     * @param[in] y A vector of observations.
     * @param[in] beta a constant used in the calculation of the penalty.
     * @param[in] alpha a constant used in the calculation of the penalty.
     * @param[in] wt A vector of weights associated to the observations.   
     */
    MsPELT(
        std::vector<double> y_, 
        double beta_, 
        double alpha_, 
        std::vector<double> wt_
    );
    
    /**
* @details Procedure for estimating the number of changepoints and their positon in the data.
     */
    void Search();

    /**
     * @returns the position of changepoints in the data.  
     */
    std::vector<int> Retreive_changepoints();
};


#endif
