# Fitting and calculation of photon strength functions

This project is based on a `ROOT` script (essentially `C++`) to fit a two-component Lorentzian-type function to the Giant Dipole Electric Resonance (GDER) observed in photonuclear reactions.  The data used in this script are from <sup>28</sup>Si(&\gamma;,*xn*) photonuclear absorption measurements.

This script requires `ROOT` to be installed and has been tested with various versions of ROOT-5 and ROOT-6.  To run the script, first launch a `ROOT` session:

```Bash
root -l
```

Then run the following commands in the `C++` interpreter and follow the prompts:

```root
> .L psfSiGDER.C
> reading()
```




