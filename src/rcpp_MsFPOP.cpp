#include <Rcpp.h>
#include "MsFPOP.h"
#include "MsPELT.h"
#include <string>
#include <vector>
#include "Sampling.h"
#include <map>
using namespace Rcpp;

// [[Rcpp::export]]
List MsFPOP_cpp(
  std::vector<double> y, 
  double beta, 
  double alpha, 
  std::string sampling_method, 
  int sampling_method_parameter, 
  std::vector<double>  wt) {   

    typedef std::vector<int> (*fun)(int, int, int);
    std::map<std::string, fun> map_sampling_method;
    if (sampling_method_parameter == 1) {
      map_sampling_method["rand"] = Sampling::Rand_one;
    } else {
      map_sampling_method["rand"] = Sampling::Rand_without_replacement;
    }  
    map_sampling_method["all"] = Sampling::All;

    MsFPOP f (
      y, 
      beta, 
      alpha, 
      (*map_sampling_method[sampling_method]), 
      sampling_method_parameter,
      wt
    );
    f.Search();
    List l = List::create(
    	_["changepoints"] = f.Retreive_changepoints(),
      _["beta"] = beta,
      _["alpha"] = alpha
    );
    return l;
}


// [[Rcpp::export]]
List MsPELT_cpp(
  std::vector<double> y, 
  double beta, 
  double alpha,  
  std::vector<double> wt) {
  
  
  MsPELT f (y, beta, alpha, wt);
  f.Search();
  List l = List::create(
    _["changepoints"] = f.Retreive_changepoints(),
    _["beta"] = beta,
    _["alpha"] = alpha
  );
  return l;
}
