# Fitting and calculation of photon strength functions

This project is based on a `ROOT` [[1]](#1) script (essentially `C++`) to fit a two-component Lorentzian-type function to the Giant Dipole Electric Resonance (GDER) observed in photonuclear reactions.  The data used in this script are from <sup>28</sup>Si(&gamma;,*xn*) photonuclear absorption measurements.

This script requires `ROOT` to be installed and has been tested with various versions of ROOT-5 and ROOT-6.  To run the script, first launch a `ROOT` session:

```Bash
$ root -l
```

Then exceute the following commands in the `C++` interpreter and follow the prompts:

```root
> .L psfSiGDER.C
> reading()
```

The figure below is an example of the resulting Lorentzian fit to the GDER in <sup>28</sup>Si(&gamma;,*xn*) and the calculated photon strength functions (PSF) utilizing the parametrizations obtained from the fit.  The functional form of the fit is known as the Brink-Axel (BA) model (also referred to as the Standard Lorentzian (SLO) model):


$$
	f_{E1}(E_{\gamma}) = \frac{1}{3(\pi \hbar c)^{2}} \sum\limits_{i=1}^{N=2} \frac{\sigma_{G_{i}} E_{\gamma} \Gamma_{G_{i}}^{2}}{(E^{2}_{\gamma}-E_{G_{i}}^{2})^{2} + E_{\gamma}^{2}\Gamma_{i}^{2}},
$$

where the resonance-shape driving parameters $E_{G}$, $\Gamma_{G}$, and $\sigma_{G}$ correspond to the resonance centroid (MeV), width (MeV), and cross section (mb), respectively, and are obtained from the fitting procedure.  This strength function contains the constant $\frac{1}{3(\pi \hbar c)^{2}} = 8.68 \times 10^{-8}~\text{mb}^{-1}\text{MeV}^{-2}$, and is singularly dependent on the $\gamma$-ray energy $E_{\gamma}$.  The other models shown on the plot are the Generalized Lorentzian (GLO), Enhanced Generalized Lorentzian (EGLO), and the Kadmensky-M-F (KMF) model.  These models are widely adopted and explained in the literature, for example, refer to the articles bundled with this project for a explicit definitions of the GLO [[2]](#2), [[3]](#3), EGLO [[3]](#3), and KMF [[#3]](3) models that have been utilized in the statistical modeling of the tungsten [[2]](#2) and lanthanum [[3]](#3) isotopes in thermal neutron capture.

![PSF 28Si](Si28_PSF.png?raw=true "Different formulations of the PSF used to describe the GDER in 28Si")


## References
<a id="1">[1]</a>
ROOT: Data Analysis Framework;
https://root.cern.ch/








