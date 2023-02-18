#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <list> 
#include "MsPELT.h"

//- Constructor --------------------------------------------------------------//
MsPELT::MsPELT(
  std::vector<double> y_, 
  double beta_, 
  double alpha_,
  std::vector<double>  wt_
  ) {

  y          = y_;
  n          = y_.size();
  beta       = beta_;
  alpha      = alpha_;
  y.insert(y.begin(), 0);
  wt         = wt_;
  wt.insert(wt.begin(), 0); 
  cp         = std::vector<int> (y.size(), 0);
  
  //- cumulative sums of squares ---------------------------------------------//
  css = std::vector<double> (n, 0);
  std::transform(y_.begin(), y_.end(), css.begin(), [](double d) {return std::pow(d, 2);});
  std::partial_sum(css.begin(), css.end(), css.begin());
  css.insert(css.begin(),0);
  
  //- cumulative sums  -------------------------------------------------------//
  cs = std::vector<double> (n, 0);
  std::partial_sum(y_.begin(), y_.end(), cs.begin());
  cs.insert(cs.begin(),0);

  //- pruning safety constant ------------------------------------------------//
  K = std::vector<double> (n+1, 0);
  for (int t {1}; t<n+1; t++){
    K[t] = -beta*std::log(t+1);
  }
  
  //- optimal costs ----------------------------------------------------------//
  Q    = std::vector<double> (n+1, 0);
  Q[0] = -alpha;
}

//- dearch for changepoints --------------------------------------------------//
void MsPELT::Search() {
  std::list<int> list_of_candidates {0};
  double F;
  double last_seg_cost;
  int tau_min;
  for (int t {1}; t<y.size(); t++)
  {  
    F = std::numeric_limits<double>::max();
    //- find segmentation with minimum cost up to t --------------------------//
    for (int tau : list_of_candidates) {
      last_seg_cost = (css[t]-css[tau]) - (t-tau)*std::pow((cs[t]-cs[tau])/(t-tau),2) - beta*std::log(t-tau); 
      if (Q[tau]+last_seg_cost < F){
        tau_min = tau;
        F       = Q[tau]+last_seg_cost;
      }
    }
    cp[t] = tau_min;
    //- introduce candidate segmentation with more recent changepoint at t ---//
    Q[t]  = F + alpha;
    list_of_candidates.push_back(t);
    //- pruning --------------------------------------------------------------//
    list_of_candidates.remove_if([this, &t](int a){
      double last_seg_cost = (css[t]-css[a]) - (t-a)*std::pow((cs[t]-cs[a])/(t-a),2);  
      return (Q[a]+last_seg_cost+K[t-a])>Q[t];
    });
  }
}

//- getter for changepoints --------------------------------------------------//
std::vector<int> MsPELT::Retreive_changepoints() {
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
