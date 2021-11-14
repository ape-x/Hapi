# Hapi

A PRNG based on a modified alternating LFSR system, with dynamic tap positions generated using input polynomials.
The generator is not enhanced with entropy validation, the client is responsible for providing it with a non-uniform seed.

Unlike traditional ASGs, the controlling LFSR decides whether the output of a third LFSR will be added to the currently working LFSRs, instead of choosing which one  will provide the output.
![hapi](https://user-images.githubusercontent.com/44141324/141665295-d60cf8bf-6c05-4599-b003-017c24126a27.png)
