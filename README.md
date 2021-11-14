# Hapi

A PRNG based on a modified alternating LFSR system, with dynamic tap positions generated using input polynomials.
The generator is not enhanced with entropy validation, the client is responsible for providing it with a non-uniform seed.

Unlike traditional ASGs, the controlling LFSR decides whether the output of a third LFSR will be added to the currently working LFSRs, instead of choosing which one  will provide the output.
![hapidiagram](https://user-images.githubusercontent.com/44141324/141667159-685584f5-16a4-47b8-adea-266bf0022aae.png)
