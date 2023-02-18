#include "Ordered_list_of_intervals.h"
#include "Interval.h"
#include <list>
#include <iostream>

//- Constructors -------------------------------------------------------------//
Ordered_list_of_intervals::Ordered_list_of_intervals(Interval interval) {
    list_of_intervals.push_back(interval);
}

Ordered_list_of_intervals::Ordered_list_of_intervals(std::list<Interval> & list_of_intervals_to_merge) {
    if (!list_of_intervals_to_merge.empty())
    {
        list_of_intervals_to_merge.sort(Interval::Compare_begin);

        list_of_intervals.push_back(list_of_intervals_to_merge.front());

        for (auto it_interval {++list_of_intervals_to_merge.begin()}; it_interval!=list_of_intervals_to_merge.end(); ++it_interval)
        {
            if (list_of_intervals.back().Get_end() >= (*it_interval).Get_begin())
            {   
                if (list_of_intervals.back().Get_end() < (*it_interval).Get_end())
                {
                    list_of_intervals.back().Set_end((*it_interval).Get_end());
                }
            }
            else
            {
                list_of_intervals.push_back((*it_interval));
            }
        }
    }
}

Ordered_list_of_intervals::Ordered_list_of_intervals() {
    list_of_intervals = std::list<Interval> ();
}

//- Intersect_intervals_of_list_with -----------------------------------------//
void Ordered_list_of_intervals::Intersect_with(Interval & interval_to_intersect) {

    for (auto it_interval {list_of_intervals.begin()}; it_interval!= list_of_intervals.end(); ++it_interval)
    {
        (*it_interval) &= interval_to_intersect;
        if ((*it_interval).IsEmpty_or_singleton())
        {
            --it_interval;
            list_of_intervals.erase(next(it_interval,1));
        }
    }
}

//- Is_empty -----------------------------------------------------------------//
bool Ordered_list_of_intervals::Is_empty() {
    return list_of_intervals.empty();
}

//- Search_complementary_in_D ------------------------------------------------//
void Ordered_list_of_intervals::Complementary_in(Interval & d) {
    if (list_of_intervals.empty())
    {
        return list_of_intervals.push_back(d);
    }
    else
    {
        (*this).Intersect_with(d);
        std::list<Interval> list_of_complementary_intervals;
        if (list_of_intervals.front().Get_begin() > d.Get_begin())
        {
            list_of_complementary_intervals.push_back( Interval(d.Get_begin(), list_of_intervals.front().Get_begin()) );
        }
        for (auto it_interval {list_of_intervals.begin()}; it_interval != --list_of_intervals.end(); it_interval++)
        {
            list_of_complementary_intervals.push_back( Interval((*it_interval).Get_end(), (*next(it_interval,1)).Get_begin()) );
        }
        if (list_of_intervals.back().Get_end() < d.Get_end())
        {
            list_of_complementary_intervals.push_back(Interval(list_of_intervals.back().Get_end(), d.Get_end()));
        }
        list_of_intervals = list_of_complementary_intervals;
    }
}

//- Get_number_of_intervals_in_list ------------------------------------------//
int Ordered_list_of_intervals::size() {
    return list_of_intervals.size();
}

//- Get_the ordered_list_of_intervals ----------------------------------------//
std::list<Interval> Ordered_list_of_intervals::Get_list() {
    return list_of_intervals;
}
