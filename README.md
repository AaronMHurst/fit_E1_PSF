# Fitting and calculation of photon strength functions

This project is based on a `ROOT` [[1]](#1) script (essentially `C++`) to fit a two-component Lorentzian-type function to the Giant Dipole Electric Resonance (GDER) observed in photonuclear reactions.  The data used in this script are from <sup>28</sup>Si(&gamma;,*xn*) photonuclear absorption measurements [[2]](#2), [[3]](#3).

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

where the resonance-shape driving parameters $E_{G}$, $\Gamma_{G}$, and $\sigma_{G}$ correspond to the resonance centroid (MeV), width (MeV), and cross section (mb), respectively, and are obtained from the fitting procedure.  This strength function contains the constant $\frac{1}{3(\pi \hbar c)^{2}} = 8.68 \times 10^{-8}~\text{mb}^{-1}\text{MeV}^{-2}$, and is singularly dependent on the $\gamma$-ray energy $E_{\gamma}$.  The other models shown on the plot are the Generalized Lorentzian (GLO), Enhanced Generalized Lorentzian (EGLO), and the Kadmenski-Markushev-Furman (KMF) model.  These models are widely adopted and explained in the literature, for example, refer to the articles bundled with this project for explicit definitions of the GLO [[4]](#4), [[5]](#5), EGLO [[4]](#4), and KMF [[5]](#5) models that have been utilized in the statistical modeling of the tungsten [[4]](#4) and lanthanum [[5]](#5) isotopes to describe decay-scheme observables following thermal neutron capture.

![PSF 28Si](Si28_PSF.png?raw=true "Different formulations of the PSF used to describe the GDER in 28Si")

## Selecting the source data

In the figure above, the data of Caldwell *et al.* [[2]](#2) are used to obtain the fit.  The appropriate filename string is declared in the `reading` function of the `psfSiGDER.C` script:

```c++
const std::string iFile = "si28_gxn_caldwell.dat";
```




## References
<a id="1">[1]</a>
ROOT: Data Analysis Framework;
https://root.cern.ch/

<a id="2">[2]</a>
J.T. Caldwell *et al*.,
*(&gamma;,n) cross sections of <sup>16</sup>O and <sup>28</sup>Si*
Phys. Lett. **6**, 213 (1963).

<a id="3">[3]</a>
B.I. Goryachev *et al*.,
*Structure of (&gamma;,n) Cross Sections in <sup>28</sup>Si, <sup>32</sup>S, and <sup>40</sup>Ca*,
Yadern. Fix.**7**, 1168 (1968);
Soviet J. Nucl. Phys. **7**, 698 (1968).

<a id="4">[4]</a>
A.M. Hurst *et al*.,
*Investigation of the tungsten isotopes via thermal neutron capture*,
Phys. Rev. C **89**, 014606 (2014);
http://dx.doi.org/10.1103/PhysRevC.89.014606

<a id="5">[5]</a>
A.M. Hurst *et al*.,
*Radiative-capture cross sections for the <sup>139</sup>La(n,&gamma;) reaction using thermal neutrons and structural properties of <sup>140</sup>La*,
Phys. Rev. C **99**, 024310 (2019);
http://dx.doi.org/10.1103/PhysRevC.99.024310

