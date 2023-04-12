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
	f = \sigma_{G} \E_{G} \Gamma_{G},
$$

and the other models shown on the plot are the Generalized Lorentzian (GLO), Enhanced Generalized Lorentzian (EGLO), and the Kadmensky-M-F (KMF) model.  These models are also explicitly defined in the attached article describing the statistical modeling of the tungsten isotopes in thermal neutron capture.

![PSF 28Si](Si28_PSF.png?raw=true "Different formulations of the PSF used to describe the GDER in 28Si")


## References
<a id="1">[1]</a>
ROOT: Data Analysis Framework;
https://root.cern.ch/








