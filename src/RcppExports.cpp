// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// MsFPOP_cpp
List MsFPOP_cpp(std::vector<double> y, double beta, double alpha, int min_segment, std::string sampling_method, int sampling_method_parameter, std::vector<double> wt);
RcppExport SEXP _MsFPOP_MsFPOP_cpp(SEXP ySEXP, SEXP betaSEXP, SEXP alphaSEXP, SEXP min_segmentSEXP, SEXP sampling_methodSEXP, SEXP sampling_method_parameterSEXP, SEXP wtSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type y(ySEXP);
    Rcpp::traits::input_parameter< double >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type min_segment(min_segmentSEXP);
    Rcpp::traits::input_parameter< std::string >::type sampling_method(sampling_methodSEXP);
    Rcpp::traits::input_parameter< int >::type sampling_method_parameter(sampling_method_parameterSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type wt(wtSEXP);
    rcpp_result_gen = Rcpp::wrap(MsFPOP_cpp(y, beta, alpha, min_segment, sampling_method, sampling_method_parameter, wt));
    return rcpp_result_gen;
END_RCPP
}
// MsPELT_cpp
List MsPELT_cpp(std::vector<double> y, double beta, double alpha, std::vector<double> wt);
RcppExport SEXP _MsFPOP_MsPELT_cpp(SEXP ySEXP, SEXP betaSEXP, SEXP alphaSEXP, SEXP wtSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type y(ySEXP);
    Rcpp::traits::input_parameter< double >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type wt(wtSEXP);
    rcpp_result_gen = Rcpp::wrap(MsPELT_cpp(y, beta, alpha, wt));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_MsFPOP_MsFPOP_cpp", (DL_FUNC) &_MsFPOP_MsFPOP_cpp, 7},
    {"_MsFPOP_MsPELT_cpp", (DL_FUNC) &_MsFPOP_MsPELT_cpp, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_MsFPOP(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
