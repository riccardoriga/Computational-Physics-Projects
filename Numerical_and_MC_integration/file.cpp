#include <cmath>
#include <iostream>
#include "Integrali.h"
#include "Funzioni.h"
#include "IntegraliMC.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TF1.h"
#include "TH1F.h"

using namespace std;

int main () {
	unsigned int nstep = 512;
	Funzesame1 f;
	Midpoint myint(0 , sqrt(M_E));
	double I = myint.Integra(nstep,f);
	cout << "Number of steps: " << nstep << ", I= " << I << endl;
	TGraph errore;

  	TApplication app("app",0,0);

  	nstep = 2;
  	double Iv = 3./16. * pow(M_E , 2) ;
  	double err = 0 , h = 0 ;
	
  	for ( unsigned int k = 0 ; k < 10; k++ ) {
    		h = (myint.GetB()-myint.GetA())/nstep; 
    		I = myint.Integra(nstep, f); 
    		err = fabs(I-Iv);
    		cout << " Steps= "  << nstep << " Error= " <<  err << endl;
    		errore.SetPoint(k, h, err );
   		nstep *= 2;
  	}

  	TCanvas c;
	c.cd();
  	errore.SetTitle("Integral error as a function of h");
  	errore.GetXaxis()->SetTitle("h");
  	errore.GetYaxis()->SetTitle("Error");
  	errore.Draw();
	c.SetLogx();
	c.SetLogy();

	TF1 *f1 = new TF1("f1","[0]*pow(x,[1])",0.,10.);
    	errore.Fit(f1);

	cout << "For the midpoint method: k1= " << f1->GetParameter(0) << ", k2= " << f1->GetParameter(1) << endl;


	nstep = 512;

	Midright myint2(0 , sqrt(M_E));
	double I2 = myint2.Integra(nstep,f);
	cout << "Number of steps: " << nstep << ", I= " << I2 << endl;
	TGraph errore2;

  	nstep = 2;
  	
	err = 0;
	h = 0;

  	for ( unsigned int k = 0 ; k < 10; k++ ) {
    		h = (myint2.GetB()-myint2.GetA())/nstep; 
    		I2 = myint2.Integra(nstep, f); 
    		err = fabs(I2-Iv);
    		cout << " Steps= "  << nstep << " Error= " <<  err << endl;
    		errore2.SetPoint(k, h, err );
   		nstep *= 2;
  	}

  	TCanvas d;
	d.cd();
  	errore2.SetTitle("Integral error as a function of h");
  	errore2.GetXaxis()->SetTitle("h");
  	errore2.GetYaxis()->SetTitle("Error");
  	errore2.Draw();
	d.SetLogx();
	d.SetLogy();

	TF1 *f2 = new TF1("f2","[0]*pow(x,[1])",0.,10.);
    	errore2.Fit(f2);

	cout << "For the midright method: k1= " << f2->GetParameter(0) << ", k2= " << f2->GetParameter(1) << endl;

	IntegratoreMedia Intmc (1);
	TH1F histo ("Integral","Integral", 100 , 1 , 0);
	for (int i = 0 ; i<1000 ; i++) {
		histo.Fill(Intmc.Integra(f, 0 , sqrt(M_E) , 16 , 0));
	}
	cout << "Integral with MC method= " << histo.GetMean() << ", error= " << histo.GetStdDev() << endl;
	double k = 4*histo.GetStdDev();
	double prec = 0.00365426;
	cout << "Points required to achieve a precision of 0.00365426: " << pow(k,2)/pow(prec,2) << endl;

	nstep = 512;
	Funzesame2 g;
	// Using midpoint because g is not defined at x=2, an evaluation that midright would require
	TGraph errore3;
	Midpoint myint3(0.,2.);
	double Iv2 = M_PI/2;
	double I3 = myint3.Integra(nstep,g);
	cout << "Number of steps: " << nstep << ", I= " << I3 << endl;
	nstep = 2;
	err = 0;
	h = 0;
	for ( unsigned int k = 0 ; k < 10; k++ ) {
    		h = (myint3.GetB()-myint3.GetA())/nstep; 
    		I3 = myint3.Integra(nstep, g); 
    		err = fabs(I3-Iv2);
    		cout << " Steps= "  << nstep << " Error= " <<  err << endl;
    		errore3.SetPoint(k, h, err );
   		nstep *= 2;
  	}

  	TCanvas e;
	e.cd();
  	errore3.SetTitle("Integral error as a function of h");
  	errore3.GetXaxis()->SetTitle("h");
  	errore3.GetYaxis()->SetTitle("Error");
  	errore3.Draw();
	e.SetLogx();
	e.SetLogy();

	TF1 *f3 = new TF1("f3","[0]*pow(x,[1])",0.,10.);
    	errore3.Fit(f3);

	cout << "For the midpoint method: k1= " << f3->GetParameter(0) << ", k2= " << f3->GetParameter(1) << endl;

	app.Run();
}