#include "EquazioniDifferenziali.h"
#include "RandomGen.h"
#include <iostream>
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TF1.h"
#include "TH1F.h"

using namespace std;

int main() {
  TApplication app("app",0,0);

  RungeKutta myRunge;

  OscillatoreArmonicoSmorzato osc(1.15 , 0.01);

  double tmax = 43.;
  double h = 0.1;
  vector<double> x {1.,0.} ;
  double t = 0.; 

  int nstep = int(tmax/h+0.5);
  double xfinal = 0;
  TGraph runge1;
  for (int step=0; step<nstep; step++) {
    runge1.SetPoint(step,t,x[0]);
    x = myRunge.Passo(t,x,h,osc);
    t = t+h;
  }
  xfinal = x[0];
  t = 0.;
  x = {1.,0.};
  h = h/2;
  nstep = int(tmax/h+0.5);
  for (int step=0; step<nstep; step++) {
    x = myRunge.Passo(t,x,h,osc);
    t = t+h;
  }
  cout << "At t= " << tmax << "s, x= " << xfinal << " (step size h=0.1)" << endl;
  double err = 16./15. * fabs(xfinal-x[0]);
  cout << "Estimated error with step size h=0.1: " << err << endl;
  
  h = 0.1;
  double k = err / pow(h,4);
  double err2 = 5e-05; 
  double prec = pow(err2/k , 1./4.);
  cout << "To get error= 5e-05, required step size h= " << prec << endl;

  unsigned int nint = 10000;
  h = prec;
  nstep = int(tmax/h+0.5);
  RandomGen rand(1);

  TGraph errore;
  vector <double> v = {0.003 , 0.005 , 0.008 , 0.012 , 0.015};
  vector<TH1F> histos;
  for (int i = 0; i < 5; i++) {
    histos.emplace_back(Form("Position at t=43s with sigma= %f", v[i]), Form("Position at t=43s with sigma= %f", v[i]), 70, 1, 0);
  }

  for (int k=0 ; k<5 ; k++) {
    for (unsigned int i = 0 ; i < nint ; i++) {
      t = 0.;
      x = {1. , rand.Gauss(0.,v[k])};
      for (int step=0; step<nstep; step++) {
        x = myRunge.Passo(t,x,h,osc);
        t = t+h;
  }
      histos[k].Fill(x[0]);
  }
    errore.SetPoint(k,v[k],histos[k].GetStdDev());
  }

  cout << "Standard deviation with n= " << nint << " simulations and initial error of 3 mm is sigma= " << histos[0].GetStdDev() << endl;

  TCanvas c1;
  c1.cd();
  runge1.SetTitle("System evolution with step size h=0.1");
  runge1.GetXaxis()->SetTitle("Time [s]");
  runge1.GetYaxis()->SetTitle("Position x [m]");
  runge1.Draw("AL");

  TCanvas c2("c", "Canvas",1200,800);
   c2.Divide(3, 2);
    for (int i = 0; i < 5; i++) {
        c2.cd(i+1);
        histos[i].Draw();
    }

  TCanvas c3;
  c3.cd();
  c3.SetLogx();
  c3.SetLogy();
  c3.SetGridx();
  c3.SetGridy();
  errore.GetXaxis()->SetTitle("sigma");
  errore.GetYaxis()->SetTitle("error");
  errore.Draw("ALP");
  errore.SetTitle("Final position error as a function of sigma");
  errore.SetMarkerStyle(20);
  errore.SetMarkerSize(0.8);

  app.Run();
}