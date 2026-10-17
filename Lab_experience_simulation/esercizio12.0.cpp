#include "RandomGen.h"
#include "EsperimentoPrisma.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include <iostream>

using namespace std;

int main() {
    TApplication app("app",0,0);
    int nsimul = 10000;
    EsperimentoPrisma e(1);
    TH1F hth0 ("theta0","theta0",100,1,0);
    TH1F hth1 ("theta1","theta1",100,1,0);
    TH1F hth2 ("theta2","theta2",100,1,0);
    TH1F hdelta1 ("deltam 1","deltam 1",100,1,0);
    TH1F hdelta2 ("deltam 2","deltam 2",100,1,0);
    TH1F hn1 ("n1","n1",100,1,0);
    TH1F hn2 ("n2","n2",100,1,0);
    TH1F hA ("A","A",100,1,0);
    TH1F hB ("B","B",100,1,0);
    TH2F corrd ("Deltam Correlation","Deltam Correlation", 100 , 1 , 0 , 100 , 1 , 0);
    TH2F corrn ("Refractive Index Correlation","Refractive Index Correlation", 100 , 1 , 0 , 100 , 1 , 0);
    TH2F corrAB ("Correlation between A and B","Correlation between A and B", 100 , 1 , 0 , 100 , 1 , 0);

    double dd = 0;
    double n1n2 = 0;
    double AB = 0;


    for (int i=0;i<nsimul;i++) {
        e.Esegui();
        e.Analizza();
        dd += (e.getdm1inp()-e.getdm1mis())*(e.getdm2inp()-e.getdm2mis());
        n1n2 += (e.getn1inp()-e.getn1mis())*(e.getn2inp()-e.getn2mis());
        AB += (e.getAinp()-e.getAmis())*(e.getBinp()-e.getBmis());
        hth0.Fill(e.getth0inp()-e.getth0mis());
        hth1.Fill(e.getth1inp()-e.getth1mis());
        hth2.Fill(e.getth2inp()-e.getth2mis());
        hdelta1.Fill(e.getdm1mis()-e.getdm1inp());
        hdelta2.Fill(e.getdm2mis()-e.getdm2inp());
        hn1.Fill(e.getn1inp()-e.getn1mis());
        hn2.Fill(e.getn2inp()-e.getn2mis());
        hA.Fill(e.getAinp()-e.getAmis());
        hB.Fill(e.getBinp()-e.getBmis());
        corrd.Fill(e.getdm1inp()-e.getdm1mis() , e.getdm2inp()-e.getdm2mis());
        corrn.Fill(e.getn1inp()-e.getn1mis() , e.getn2inp()-e.getn2mis());
        corrAB.Fill(e.getAinp()-e.getAmis() , e.getBinp()-e.getBmis());
    }

    TCanvas c("c", "Canvas",1600,1000);
    c.Divide(3, 1);
    TCanvas d("d", "Canvas",1600,1000);
    d.Divide(2, 1);
    TCanvas E("e", "Canvas",1600,1000);
    E.Divide(2, 1);
    TCanvas f("f", "Canvas",1600,1000);
    f.Divide(2, 1);
    TCanvas g("g", "Canvas",1600,1000);
    TCanvas h("h", "Canvas",1600,1000);
    TCanvas i("i", "Canvas",1600,1000);


    c.cd(1);
    hth0.Draw();
    c.cd(2);
    hth1.Draw();
    c.cd(3);
    hth2.Draw();

    d.cd(1);
    hdelta1.Draw();
    d.cd(2);
    hdelta2.Draw();

    E.cd(1);
    hn1.Draw();
    E.cd(2);
    hn2.Draw();


    f.cd(1);
    hA.Draw();
    f.cd(2);
    hB.Draw();

    g.cd();
    corrd.Draw();

    h.cd();
    corrn.Draw();

    i.cd();
    corrAB.Draw();

    double correlazione1 = ((dd/nsimul)-hdelta1.GetMean()*hdelta2.GetMean())/(hdelta1.GetStdDev()*hdelta2.GetStdDev());
    cout << "Correlation between the two deltamin values is " << correlazione1 * 100 << "%" << endl; 

    double correlazione2 = ((n1n2/nsimul)-hn1.GetMean()*hn2.GetMean())/(hn1.GetStdDev()*hn2.GetStdDev());
    cout << "Correlation between the two n values is " << correlazione2 * 100 << "%" << endl; 

    double correlazione3 = ((AB/nsimul)-hA.GetMean()*hB.GetMean())/(hA.GetStdDev()*hB.GetStdDev());
    cout << "Correlation between A and B is " << correlazione3 * 100 << "%" << endl;

    app.Run();

    return 0;
}