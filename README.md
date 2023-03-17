# Fitting and calculation of photon strength functions

This project is based on a `ROOT` script (essentially `C++`) to fit a two-component Lorentzian-type function to the Giant Dipole Electric Resonance (GDER) observed in photonuclear reactions.  The data used in this script are from <sup>28</sup>Si(&gamma;,*xn*) photonuclear absorption measurements.

This script requires `ROOT` to be installed and has been tested with various versions of ROOT-5 and ROOT-6.  To run the script, first launch a `ROOT` session:

```Bash
root -l
```

Then exceute the following commands in the `C++` interpreter and follow the prompts:

```root
> .L psfSiGDER.C
> reading()
```

The figure below is an example of the resulting Lorentzian fit to the GDER in <sup>28</sup>Si(&gamma;,*xn*) and the calculated photon strength functions (PSF) utilizing the parametrizations obtained from the fit.

![PSF 28Si](Si28_PSF.pdf?raw=true "Different formulations of the PSF used to describe the GDER in <sup>28</sup>Si")




