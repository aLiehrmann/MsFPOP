#include "Interval.h"
#include <limits>
#include <algorithm>
#include <vector> 
#include <array>
#include <iostream>
#include <list>

//- Constructors -------------------------------------------------------------//
Interval::Interval() {   
    begin = 1;
    end   = -1;
}

Interval::Interval(
    double begin_, 
    double end_) {

    begin = begin_;
    end   = end_;
}

Interval::Interval(std::list<Interval> & list_of_intervals_to_intersect) {   
    if (list_of_intervals_to_intersect.empty())
    {
        begin = 1;
        end   = -1;
    }
    else
    {
        begin = (*std::max_element(list_of_intervals_to_intersect.begin(),list_of_intervals_to_intersect.end(), Compare_begin)).begin;
        end   = (*std::min_element(list_of_intervals_to_intersect.begin(),list_of_intervals_to_intersect.end(), Compare_end)).end;
    }
}

//- Interval_is_empty_or_singleton -------------------------------------------//
bool Interval::IsEmpty_or_singleton() {
    return begin >= end;  
}

//- Intersect_in_place -------------------------------------------------------//
void Interval::operator&=(Interval const& interval_to_intesect) {
    begin = std::max(begin, interval_to_intesect.begin);
    end   = std::min(end, interval_to_intesect.end);
}

//- Comparator ---------------------------------------------------------------//
bool Interval::Compare_begin(
    Interval const& interval1, 
    Interval const& interval2) {
    
    return interval1.begin<interval2.begin;
}

//- Comparator ---------------------------------------------------------------//
bool Interval::Compare_end(
    Interval const& interval1, 
    Interval const& interval2) {

    return interval1.end<interval2.end;
}

//- get_beginning_of_current_interval ----------------------------------------//
double Interval::Get_begin() {
    return begin;
}

//- get_end_of_current_interval ----------------------------------------------//
double Interval::Get_end() {
    return end;
}

//- set_beginning_of_current_interval ----------------------------------------//
void Interval::Set_begin(double begin_) {
    begin = begin_;
}

//- set_end_of_current_interval ----------------------------------------------//
void Interval::Set_end(double end_) {
    end = end_;
}