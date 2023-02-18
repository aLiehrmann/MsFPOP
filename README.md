
<!-- README.md is generated from README.Rmd. Please edit that file -->

# Ms.FPOP

<!-- badges: start -->
<!-- badges: end -->

## What is Ms.Fpop ?

The `MsFPOP` R package implements an exact segmentation algorithm that
extends functionnal pruning ideas of Rigaill (2015) and Maidstone et
al. (2017) to a least squares criterion with a multiscale penalty
described in (Verzelen et al. 2020).

The motivation for this method as well as technical details and
simulations are described in Liehrmann and Rigaill (2023). Briefly, this
penalty promotes well spread changepoints. We propose an efficient C++
implementation interfaced with R of Ms.Fpop allowing to segment a
profile of up to $10^6$ datapoints in a matter of seconds.

## How can I get Ms.FPOP ?

Make sure that `remotes` is installed by running
`install.packages("remotes")`, then type

``` r
remotes::install_github("aLiehrmann/MsFPOP")
```

## Where can I learn more?

See the [multiscale penalty section](articles/theory.html) for a gentle
introduction on the multiscale penalty. See the [calibration
tutorial](articles/calibration.html) for details on how to calibrate the
multiscale penalty. Details regarding the multiscale penalty can be
found in Verzelen et al. (2020). Details regarding functional pruning
ideas can be found in Rigaill (2015) and Maidstone et al. (2017).

## References

Verzelen, N., Fromont, M., Lerasle, M., Reynaud-Bouret, P. Optimal
Change-Point Detection and Localization (2020).
<https://arxiv.org/abs/2010.11470>.

Maidstone R, Hocking T, Rigaill G, Fearnhead P. On optimal multiple
changepoint algorithms for large data. Stat Comput 27(2), 519-533
(2017).
[doi:10.1007/s11222-016-9636-3](https://link.springer.com/article/10.1007/s11222-016-9636-3).

Rigaill G. A pruned dynamic programming algorithm to recover the best
segmentations with 1 to Kmax change-points. Journal de la Société
Française de Statistique 156(4), (2015).
<http://www.numdam.org/item/JSFS_2015__156_4_180_0/>

Liehrmann, A. and Rigaill, G. Ms.Fpop: An Exact and Fast Segmentation
Algorithm With a Multiscale Penalty (2023). [add link to preprint]().
