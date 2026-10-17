#pragma once

#include "VectorOperations.h" 
#include <vector>
#include <cmath>

using namespace std;

// ===========================================================================
// Abstract base class, returns the derivative evaluated at point x
// ===========================================================================

class FunzioneVettorialeBase {

public:
  virtual vector<double> Eval(double t, const vector<double> & x) const = 0;
};

// Concrete physical case: harmonic oscillator

class OscillatoreArmonico : public FunzioneVettorialeBase {
public:
  OscillatoreArmonico(double omega0) {  m_omega0 = omega0;  } ;

  virtual vector<double> Eval(double t, const vector<double> & x) const {

  vector<double> Derivata(2);
  Derivata[0] = x[1];
  Derivata[1] = - (m_omega0 * m_omega0) * x[0];
  return Derivata;
  };

 private:
  double m_omega0;  
};

class OscillatoreArmonicoForzatoSmorzato : public FunzioneVettorialeBase {
public:
  OscillatoreArmonicoForzatoSmorzato(double omega0, double omega, double alfa) {  m_omega0 = omega0; m_omega = omega; m_alfa = alfa;  } ;

  virtual vector<double> Eval(double t, const vector<double> & x) const {

  vector<double> Derivata(2);
  Derivata[0] = x[1];
  Derivata[1] = - (m_omega0 * m_omega0) * x[0] - m_alfa * x[1] + sin(m_omega * t);
  return Derivata;
  };

 private:
  double m_omega0;  
  double m_omega;
  double m_alfa;
};

class OscillatoreArmonicoSmorzato : public FunzioneVettorialeBase {
public:
  OscillatoreArmonicoSmorzato(double omega0, double alfa) {  m_omega0 = omega0; m_alfa = alfa;  } ;

  virtual vector<double> Eval(double t, const vector<double> & x) const {

  vector<double> Derivata(2);
  Derivata[0] = x[1];
  Derivata[1] = - (m_omega0 * m_omega0) * x[0] - m_alfa * x[1];
  return Derivata;
  };

 private:
  double m_omega0;
  double m_alfa;
};

class Pendolo : public FunzioneVettorialeBase {
  public:
  Pendolo(double l) {  m_l = l;  };
  virtual vector<double> Eval(double t, const vector<double> & x) const {
    vector<double> Derivata(2);
    Derivata[0] = x[1]/m_l;
    double g = 9.8;
    Derivata[1] = -g/m_l * sin(x[0]);
    return Derivata;
  };

 private:
  double m_l;
};

// ===========================================================================
// Abstract base class for a differential equation solver
// ===========================================================================

class EquazioneDifferenzialeBase {

public:
  virtual vector<double> Passo(double t, 
                               const vector<double>& x, 
                               double h, 
                               const FunzioneVettorialeBase &f) const =0;
};

// Concrete solver: Euler method

class Eulero : public EquazioneDifferenzialeBase {

 public:

  virtual vector<double> Passo(double t, 
                               const vector<double> & x, 
                               double h, 
                               const FunzioneVettorialeBase &f) const override {
    return x+(f.Eval(t,x))*h;

  };

};

class RungeKutta : public EquazioneDifferenzialeBase {

 public:

  virtual vector<double> Passo(double t, 
                               const vector<double> & x, 
                               double h, 
                               const FunzioneVettorialeBase &f) const override {
    
    vector<double> k1 = f.Eval(t,x);
    vector<double> k2 = f.Eval(t+(h/2.) , x + k1 * (h/2.));
    vector<double> k3 = f.Eval(t+(h/2.) , x + k2 * (h/2.));
    vector<double> k4 = f.Eval(t + h , x + k3*h);
    return x+(k1 + 2.*k2 + 2.*k3 + k4) * (h/6.);
  };

};