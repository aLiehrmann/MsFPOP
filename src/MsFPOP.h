#ifndef DEF_MSFPOP
#define DEF_MSFPOP

#include <vector>
#include "Interval.h"
#include <random>

class MsFPOP
{
private:
    std::vector<double> y;
    int n; 
    Interval d;
    double beta;
    double alpha;
    std::vector<double> wt;
    std::vector<int> cp;
    std::vector<int> (*sampling_method)(int, int, int);
    int sampling_method_parameter;

    
public:
    /**
     * @param[in] y A vector of observations.
     * @param[in] beta A constant used in the calculation of the penalty.
     * @param[in] alpha A constant used in the calculation of the penalty.
     * @param[in] sampling_method A sampling method for candidates.
     * @param[in] param_method A parameter used by the sampling method.
     * @param[in] wt A vector of weights associated to the observations.    
     */
    MsFPOP(
        std::vector<double> y_,
        double beta_,
        double alpha_, 
        std::vector<int> (*sampling_method_)(int, int, int),
        int para_method_,
        std::vector<double> wt_ = {0}
    );
    

    /**
     * @details Procedure for estimating the number of changepoints and their position in the data.
     */
    void Search();

    /**
     * @returns the position of inferred changepoints in the data. 
     */
    std::vector<int> Retreive_changepoints();
};

#endif
