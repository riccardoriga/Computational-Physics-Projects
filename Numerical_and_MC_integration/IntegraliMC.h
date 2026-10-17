#pragma once

#include <cmath>
#include <vector>
#include <numeric>
#include "RandomGen.h"
#include "Funzioni.h"

using namespace std;

class IntegraliMC {

public:

  IntegraliMC(unsigned int seed) : 
    m_gen(seed)
  {
    m_errore = 0;
    m_punti  = 0;
  }

  virtual double Integra( const FunzioneBase& f, double inf , double sup , unsigned int punti, double fmax ) = 0 ;

  double GetErrore() const {return m_errore;}
  unsigned int GetN() const {return m_punti;}

protected:

  RandomGen m_gen;
  double m_errore;
  unsigned int m_punti;

};

class IntegratoreMedia : public IntegraliMC {

public:

  IntegratoreMedia(unsigned int seed) : IntegraliMC(seed) { ; };

  virtual double Integra ( const FunzioneBase& f, double inf , double sup , unsigned int punti, double fmax ) {

    vector<double> v(punti);
    for (int i=0 ; i<punti ; i++) {
        v[i] = f.Eval(m_gen.Unif(inf,sup));
    }
    return (accumulate(v.begin(),v.end(),0.)*(sup-inf)/punti);
  };

};

class IntegratoreHitOrMiss : public IntegraliMC {

public:

  IntegratoreHitOrMiss(unsigned int seed) : IntegraliMC(seed) { ; };

  virtual double Integra ( const FunzioneBase& f, double inf , double sup , unsigned int punti, double fmax ) {
    int Nhit = 0;
    int Ntot = 0;
    for (int i=0 ; i<punti ; i++) {
        double a = m_gen.Unif(inf,sup);
        double b = m_gen.Unif(0,fmax);
        if (b<f.Eval(a)) Nhit++;
        Ntot++;
    }
    return (sup-inf)*fmax* (double) Nhit/Ntot;
  };

};
