#' MsFPOP
#' @description MsFPOP is an exact segmentation algorithm that extends 
#' functionnal pruning ideas of Rigaill 2015 and Maidstone et al. 2017 to a 
#' least squares criterion with a multiscale penalty promoting well-spread
#' changepoints. Such a penalty has been proposed in Verzelen et al. (2020), 
#' and it achieves optimal rates for changepoint detection and changepoint
#' localization (arXiv:2010.11470).
#' @param y A vector of observations.
#' @param beta A constant used in the the penalty.
#' @param alpha A constant used in the the penalty.
#' (recommended: gamma+beta*log(length(y)))
#' @param min_segment A constraint on the minimum segment length.
#' @param sampling_method A sampling method for changepoint candidates ("rand", "all").
#' @param sampling_method_parameter A parameter used by the sampling method.
#' @param wt A vector of weights associated to the observations.
#' @return A list that includes the estimated position of the changepoints.
#' @export
MsFPOP <- function(
  y, 
  beta, 
  alpha, 
  min_segment=0,
  sampling_method="rand", 
  sampling_method_parameter=1, 
  wt) {
  
  if(missing(wt)){
    wt = rep(1,length(y));
  } else if (length(wt) != length(y)) {
    stop("Vector of observations and vector of weights have not the same size.")
  }
  
  if (beta<=0) {
    stop("Beta should be zero or a positive real number.")
  }
  
  if (alpha<=0) {
    stop("Alpha should be zero or a positive real number (recommended : gamma+beta*log(length(y)).")
  }
  
  if (!sampling_method%in%c("rand","all")) {
    stop("sampling_method should be 'rand' or 'all'")
  }
  return (MsFPOP_cpp(y, beta, alpha, min_segment, sampling_method, sampling_method_parameter, wt))
}


#' MsPELT
#' @description MsPELT is an exact segmentation algorithm that extends
#' inequality pruning idea from PELT to a least squares criterion with a
#' multiscale penalty promoting well-spread changepoints. Such a penalty 
#' has been proposed in Verzelen et al. (2020), and it achieves optimal rates
#' for changepoint detection and changepoint localization (arXiv:2010.11470).
#' @param y A vector of observations.
#' @param beta A constant used in the penalty.
#' @param alpha A constant used in the penalty.
#' (recommended: gamma+beta*log(length(y))).
#' @param wt A vector of weights associated to the observations.
#' @return A list that includes the estimated position of the changepoints.
#' @export
MsPELT <- function(
    y, 
    beta, 
    alpha,
    wt) {
  
  if(missing(wt)){
    wt = rep(1,length(y));
  } else if (length(wt) != length(y)) {
    stop("Vector of observations and vector of weights have not the same size.")
  }
  
  if (beta<0) {
    stop("Beta should be zero or a positive real number.")
  }
  
  if (alpha<0) {
    stop("Alpha should be zero or a positive real number (recommended : gamma+beta*log(length(y)).")
  }
  
  return (MsPELT_cpp(y, beta, alpha, wt))
}
