#ifndef DEF_QUADRATIC
#define DEF_QUADRATIC

#include <array>
#include "Interval.h"

class Quadratic
{
private:
    std::array<double, 3> coef;    
public:
    
    /**
     * @details Instantiate a quadratic form whose coefficients value is zero.
     */ 
    Quadratic();
    
    /**
     * @details Instanciate the quadratic form a0 + a1*mu +a2*mu^2 .
     */
    Quadratic(
        double a0, 
        double a1, 
        double a2
    );
    
    /**
     * @details Add the coefficients a0, a1, a2 to the coefficients of the current quadratic form.
     */
    void Add_coef(
        double a0, 
        double a1, 
        double a2
    );

    /**
     *  @returns the minimum of the quadratic form.
     */
    double Minimum();

    /**
     *  @details Calculate the roots of the quadratic form.
     *  @returns the interval on which the quadratic form is negative, an empty interval otherwise.
     */
    Interval Negative_interval();

    /**
     * @returns a quadratic form whose coefficients are equal to the difference of the coeffcients of two quadratic forms.
     */
    Quadratic operator-(Quadratic const& quadratic_to_subtract);

};




#endif
