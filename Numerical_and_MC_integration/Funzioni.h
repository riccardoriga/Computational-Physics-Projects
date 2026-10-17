#include <cmath>

#pragma once


class FunzioneBase {

public:

  virtual double Eval(double x) const = 0;
  virtual ~FunzioneBase() {;};
};


class Parabola : public FunzioneBase {

public:

  Parabola()  { m_a = 0.; m_b = 0.; m_c = 1.; }  
  Parabola(double a, double b, double c)  { m_a = a; m_b = b; m_c = c; }
  ~Parabola() {;} ;
  virtual double Eval(double x) const override {return m_a*x*x+m_b*x+m_c;}
  void SetA(double a) { m_a = a; }
  double GetA() const {return m_a;} 
  void SetB(double b) { m_b = b; }
  double GetB() const {return m_b;} 
  void SetC(double c) { m_c = c; }
  double GetC() const {return m_c;} 

  double GetVertex() const { return -m_b / (2*m_a) ;} ;

private:

  double m_a, m_b, m_c;

};


class FunzioneTangente : public FunzioneBase {

public:

  FunzioneTangente()  {;}  
  ~FunzioneTangente() {;} ;
  virtual double Eval(double x) const override {return (sin(x) - (x * cos(x)));}
};

class FunzioneSeno : public FunzioneBase {

public:

  FunzioneSeno()  {;}  
  ~FunzioneSeno() {;} ;
  virtual double Eval(double x) const override {return (x * sin(x));}
};

class Funzesame1 : public FunzioneBase {
  public:

  Funzesame1() {;}
  ~Funzesame1() {;} ;
  virtual double Eval(double x) const override {return (pow(x,3)*log(sqrt(M_E+pow(x,2))));}
};

class Funzesame2 : public FunzioneBase {
  public:

  Funzesame2() {;}
  ~Funzesame2() {;} ;
  virtual double Eval(double x) const override {return 1./(sqrt(4-pow(x,2)));}
};
