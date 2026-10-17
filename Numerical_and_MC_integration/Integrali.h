#pragma once

#include "Funzioni.h"
#include <algorithm>
#include <iostream>

using namespace std;                                                        

// base class

class Integral {

 public:

  Integral (double a, double b) {
    checkInterval (a,b);
    m_nstep = 0;
    m_h = 0 ;
    m_sum = 0 ;
    m_integral = 0 ;
  } ;

  virtual double Integra(unsigned int nstep, const FunzioneBase &) = 0 ;
  virtual double Integra(double prec, const FunzioneBase & ) = 0 ;


  double GetA() {return m_a;};

  double GetB() {return m_b;};

 protected:

  void checkInterval( double a, double b ) {
    m_a = min(a,b);
    m_b = max(a,b);
    if ( a > b ) m_sign = -1;
    else m_sign = 1;
  }

  unsigned int m_nstep;
  double m_a, m_b;
  double m_sum, m_integral, m_h;
  int m_sign;

};

// derived class

class Midpoint : public Integral {

 public:

  Midpoint (double a, double b) : Integral(a,b) { ; } ;

  double Integra(unsigned int nstep, const FunzioneBase &f) override {

    if ( nstep <= 0 ) { cout << "Error, number of steps is negative or zero" << endl; exit(-1) ; } ;

    m_nstep = nstep;
    m_h = (m_b-m_a)/m_nstep;

    m_sum = 0.;
    for (unsigned int i=0; i<m_nstep; i++ ) {
      m_sum += f.Eval( m_a  + (i+0.5)*m_h );
    }
    m_integral = m_sign*m_sum*m_h;
    return m_integral;
  };

  double Integra (double prec, const FunzioneBase &f) override {return 0;};

};

class Midright : public Integral {

 public:

  Midright (double a, double b) : Integral(a,b) { ; } ;

  double Integra(unsigned int nstep, const FunzioneBase &f) override {

    if ( nstep <= 0 ) { cout << "Error, number of steps is negative or zero" << endl; exit(-1) ; } ;

    m_nstep = nstep;
    m_h = (m_b-m_a)/m_nstep;

    m_sum = 0.;
    for (unsigned int i=1; i<=m_nstep; i++ ) {
      m_sum += f.Eval( m_a  + (i)*m_h );
    }
    m_integral = m_sign*m_sum*m_h;
    return m_integral;
  };

  double Integra (double prec, const FunzioneBase &f) override {return 0;};

};


class Simpson : public Integral {
 public:

 Simpson (double a , double b) : Integral(a,b) { ; } ;

 double Integra(unsigned int nstep, const FunzioneBase &f) override {
  if ( nstep <= 0 ) { cout << "Error, number of steps is negative or zero" << endl; exit(-1) ; } ;

    m_nstep = (nstep/2) * 2;
    m_h = (m_b-m_a)/m_nstep;

    m_sum = 0.;
    for (unsigned int i=0; i<=m_nstep; i++ ) {
      double t = 0;
      if (i == 0 || i == m_nstep) {
        t = 1./3.;} else if ((i%2) == 1) {
        t = 4./3.;} else if ((i%2) == 0) {t = 2./3. ;}
      m_sum += t * f.Eval( m_a  + i*m_h );
    }
    m_integral = m_sign*m_sum*m_h;
    return m_integral;
 }

 double Integra (double prec, const FunzioneBase &f) override {return 0;};

};



class Trapezi : public Integral {
 public:
 
 Trapezi (double a , double b) : Integral(a,b) { ; } ;

 double Integra(unsigned int nstep, const FunzioneBase &f) {
  if ( nstep <= 0 ) { cout << "Error, number of steps is negative or zero" << endl; exit(-1) ; } ;

    m_nstep = (nstep/2) * 2;
    m_h = (m_b-m_a)/m_nstep;

    m_sum = 0.;
    for (unsigned int i=0; i<=m_nstep; i++ ) {
      double t = 0;
      if (i == 0 || i == m_nstep) {
        t = 1./2.;} else {t = 1 ;}
      m_sum += t * f.Eval( m_a  + i*m_h );
    }
    m_integral = m_sign*m_sum*m_h;
    return m_integral;
 }


 double Integra(double prec, const FunzioneBase &f ) override {
    if ( prec <= 0 ) { cout << "Error, precision is negative or zero" << endl; exit(-1) ; } ;
    m_nstep = 2;
    m_sum = 0.;
    double integrale = m_sign * (m_b - m_a) * (f.Eval(m_b) + f.Eval(m_a))/2.;

    for (unsigned int i = 0; ; i++ ) {
      m_sum = (f.Eval(m_b) + f.Eval(m_a))/2. ;
      for (int j = 1 ; j < m_nstep ; j++) {
        m_h = (m_b-m_a)/m_nstep;
        m_sum += f.Eval( m_a  + j*m_h );
      }
      m_integral = m_sign*m_sum*m_h;
      if (fabs (integrale - m_integral) < prec) break;
      integrale = m_integral;
      m_nstep *= 2;
    }
    return m_integral;
    }
};