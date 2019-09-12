# DCMI: Scalable Acceleration of Iterative Stencil Loops (ISLs) on FPGAs

Iterative Stencil Loops (ISLs) are the key kernel within a range of compute-intensive applications. To accelerate ISLs with FPGAs, it is critical to exploit parallelism (1) among elements within the same iteration and (2) across loop iterations.  This repository contains the HLS template and impulse array generator scropt for the ISL acceleration scheme Direct Computation of Multiple Iterations (DCMI). DCMI pre-computes the effective stencil coefficients after a number of iterations at design time and leverages this to generate FPGA-based accelerators that use minimal on-chip memory and avoid redundant computation.

If you use DCMI in a scientific publication, please consider citing our TACO paper:

*Mostafa Koraei, Omid Fatemi, and Magnus Jahre. 2019. DCMI: A Scalable Strategy for Accelerating Iterative Stencil Loops on FPGAs. ACM Transactions on Architecture and Code Optimization. 16, 4, Article 36 (January 2019), 24 pages. https://doi.org/10.1145/3352813*
