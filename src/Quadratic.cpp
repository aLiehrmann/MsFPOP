#include "Quadratic.h"
#include <cmath> 
#include <array>
#include <limits> 
#include <iostream>
#include "Interval.h"

//- Constructors -------------------------------------------------------------//
Quadratic::Quadratic() {
    coef[0] = 0;
    coef[1] = 0;
    coef[2] = 0;
}

Quadratic::Quadratic(
    double a0, 
    double a1, 
    double a2) {

    coef[0] = a0;
    coef[1] = a1;
    coef[2] = a2;
}

void Quadratic::Add_coef(
    double a0, 
    double a1, 
    double a2) {

    coef[0] += a0;
    coef[1] += a1;
    coef[2] += a2;
    
}

//- Get_minimum_quadratic_form -----------------------------------------------//
double Quadratic::Minimum() {
    return coef[0]-(pow(coef[1],2)/(4*coef[2]));
}

//- Get_intervals_formed_by roots_of_quadratic_form --------------------------//
Interval Quadratic::Negative_interval() {
    double delta { pow(coef[1], 2) -4*coef[2]*coef[0] };
    double x1 {(-coef[1]-sqrt(delta))/(2*coef[2])};
    double x2 {(-coef[1]+sqrt(delta))/(2*coef[2])};
    if (delta > 0) 
    {
        if (x1 < x2)
        {
            return Interval (x1, x2);
        }
        else
        {
            return Interval (x2, x1);
        }
    }
    else
    {
        return Interval ();
    }
}

//- substract_two_quadratic_form ---------------------------------------------//
Quadratic Quadratic::operator-(Quadratic const& quadratic_to_subtract) {
    return Quadratic(coef[0]-quadratic_to_subtract.coef[0], coef[1]-quadratic_to_subtract.coef[1], coef[2]-quadratic_to_subtract.coef[2]);
}