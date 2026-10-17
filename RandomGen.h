#pragma once

#include <cmath>
#include <cstdlib>
#include <cstdint>

class RandomGen {

public:

  RandomGen(uint32_t seed) : m_seed(seed), m_c(1013904223), m_a(1664525), m_m(double(1ULL << 32)) {};

  double Rand( ) {
    m_seed = m_a * m_seed + m_c;
    return double(m_seed) / m_m;
  };
  double Unif(double xmin, double xmax) {
    m_seed = m_a * m_seed + m_c;
    return xmin+(xmax-xmin) * double(m_seed)/m_m;
  };
  double Exp(double lambda) {
    double x = -log(1.0-Rand());
    return x/lambda;
  };
  double Gauss(double mean, double sigma) {
    double s = 1.0-Rand();
    double t = Rand();
    double x = sqrt(-2.0 * log(s))*cos(2.0*M_PI*t);
    return mean + x * sigma;
  };
  double GaussAR(double mean, double sigma ) {
    double x = Unif(mean-sigma*4. , mean+sigma*4.);
    double y = Rand();
    double z = exp(-(x-mean)*(x-mean)/(2.*sigma*sigma));
    if (y <= z) return x;
    else return GaussAR(mean , sigma);
  };

 private:

  uint32_t m_a, m_c ;
  uint32_t m_seed;
  double m_m;

};

