# Computational-Physics-Projects
This repository contains a collection of numerical simulation projects developed as part of the Physics B.Sc. curriculum at the **University of Milan (UniMi)**. The codebase leverages C++ Object-Oriented Programming (OOP) alongside the **CERN ROOT framework** for data visualization, statistical analysis, and fitting.

## 📌 Projects Overview

### 1. Numerical Integration & Error Analysis (`Integrali.cpp`)
* **Objective:** Evaluation of definite integrals using various quadrature methods (Midpoint, Midright) and Monte Carlo sampling.
* **Key Features:**
  * Convergence rate analysis ($O(h^2)$ fitting in log-log scale).
  * Handling mathematical singularities at integration boundaries.
  * Monte Carlo sampling and precision estimation based on target standard deviation.

### 2. Prism Spectrometer & Error Correlation (`EsperimentoPrisma.cpp`)
* **Objective:** Toy Monte Carlo simulation of a physics experiment (Prism Spectrometer) studying light refraction and dispersion.
* **Key Features:**
  * Propagation of systematic and random measurement uncertainties.
  * Multivariant statistical analysis evaluating Pearson correlation coefficients across correlated physical observables ($n_1, n_2$ refractive indices and Cauchy parameters $A, B$).

### 3. Differential Equations & Uncertainty Propagation (`RungeKutta_Oscillator.cpp`)
* **Objective:** Simulation of a damped harmonic oscillator using 4th-order Runge-Kutta (RK4).
* **Key Features:**
  * Dynamic step-size optimization based on target numerical precision ($O(h^4)$ error scaling).
  * Stochastic propagation of initial condition uncertainties ($\sigma$) using Gaussian random variables.

---

## 🛠️ Requirements & Compilation

* **Language:** C++11 or higher
* **Libraries:** CERN ROOT Framework (v6.x or higher)

### Build and Run Example
```bash
g++ -o main main.cpp $(root-config --cflags --libs)
./main
