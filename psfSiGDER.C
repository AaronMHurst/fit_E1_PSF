///////////////////////////////////////////////////////////////////////////////
// ROOT script to fit and calculate PSFs to photonuclear data                //
//                                                                           //
// Aaron Hurst                                                               //
// amhurst@berkeley.edu                                                      //
// September 9, 2022                                                         //
///////////////////////////////////////////////////////////////////////////////

#include <fstream>
using namespace ROOT::Math;

class MyParameters {

public:

  MyParameters(Float_t *E_K0);
  MyParameters();
  ~MyParameters();

  void setEG1();
  void setGammaG1();
  void setSigmaG1();
  void setEG2();
  void setGammaG2();
  void setSigmaG2();
  void setEK0();

  Double_t getEG1() const;
  Double_t getGammaG1() const;
  Double_t getSigmaG1() const;
  Double_t getEG2() const;
  Double_t getGammaG2() const;
  Double_t getSigmaG2() const;
  Float_t getEK0() const;
  Float_t getEK0(Float_t *E_K0);

private:
  
  Double_t EG1;
  Double_t GammaG1;
  Double_t SigmaG1;
  Double_t EG2;
  Double_t GammaG2;
  Double_t SigmaG2;
  Float_t EK0;

};

//MyParameters::MyParameters(){ EK0 = *E_K0; }

//From RIPL-3
//MyParameters::MyParameters(){ EG1 = 20.10; GammaG1 = 3.90; SigmaG1 = 10.5;  
//  EG2 = 26.50; GammaG2 = 8.70; SigmaG2 = 3.70; EK0 = 1.0; }

//Deduced fitted parametrizations to Caldwell data
//MyParameters::MyParameters(){ EG1 = 20.47; GammaG1 = 3.73; SigmaG1 = 9.43;  
//  EG2 = 27.56; GammaG2 = 7.98; SigmaG2 = 2.95; EK0 = 1.0; }

//Deduced fitted parametrizations to Goryachev data
MyParameters::MyParameters(){ EG1 = 20.24; GammaG1 = 4.03; SigmaG1 = 13.45;  
  EG2 = 27.68; GammaG2 = 6.46; SigmaG2 = 6.92; EK0 = 1.0; }

MyParameters::~MyParameters(){}

void MyParameters::setEG1(){ Double_t E_G1 = 0;
  cout << "Centroid (1)?" << endl; cin >> E_G1; EG1 = E_G1; return; }
void MyParameters::setGammaG1(){ Double_t GAMMA_G1 = 0;
  cout << "Width (1)?" << endl; cin >> GAMMA_G1; GammaG1 = GAMMA_G1; return; }
void MyParameters::setSigmaG1(){ Double_t SIGMA_G1 = 0;
  cout<<"Cross Section (1)?"<<endl; cin>>SIGMA_G1; SigmaG1 = SIGMA_G1; return; }
void MyParameters::setEG2(){ Double_t E_G2 = 0;
  cout << "Centroid (2)?" << endl; cin >> E_G2; EG2 = E_G2; return; }
void MyParameters::setGammaG2(){ Double_t GAMMA_G2 = 0;
  cout << "Width (2)?" << endl; cin >> GAMMA_G2; GammaG2 = GAMMA_G2; return; }
void MyParameters::setSigmaG2(){ Double_t SIGMA_G2 = 0;
  cout<<"Cross Section (2)?"<<endl; cin>>SIGMA_G2; SigmaG2 = SIGMA_G2; return; }
void MyParameters::setEK0(){ Float_t E_K0 = 0;
  cout << "enhancement factor k0?" << endl; cin >> E_K0; EK0 = E_K0; return; }
//void MyParameters::setEK0(Float_t *E_K0){ EK0 = *E_K0; return; }

Double_t MyParameters::getEG1() const { return EG1; }
Double_t MyParameters::getGammaG1() const { return GammaG1; }
Double_t MyParameters::getSigmaG1() const { return SigmaG1; }
Double_t MyParameters::getEG2() const { return EG2; }
Double_t MyParameters::getGammaG2() const { return GammaG2; }
Double_t MyParameters::getSigmaG2() const { return SigmaG2; }
Float_t MyParameters::getEK0() const { return EK0; }

// Prototype declarations needed for ROOT 6
Double_t EGLO(Double_t *E, Double_t *par);
Double_t EGLO_k0(Double_t *E, Double_t *par);
Double_t GLO(Double_t *E, Double_t *par);
Double_t BA(Double_t *E, Double_t *par);
Double_t KMF(Double_t *E, Double_t *par);
Double_t myFitFunction(Double_t *E, Double_t *par);


class MyConstants {

public:
  MyConstants();
  ~MyConstants();

  Double_t getSn() const;
  Double_t getAtomicMass() const;
  Double_t getASHELL() const;
  Double_t getPAIRING() const;

private:
  Double_t Sn;
  Double_t AtomicMass;
  Double_t ASHELL;
  Double_t PAIRING;
};

// Sn from AME2020; ASHELL, PAIRING from VE(2005).
MyConstants::MyConstants(){ Sn = 8.4736; AtomicMass = 29.0; ASHELL = 3.87;
  PAIRING = -0.538; }
MyConstants::~MyConstants(){}

Double_t MyConstants::getSn() const { return Sn; }
Double_t MyConstants::getAtomicMass() const { return AtomicMass; }
Double_t MyConstants::getASHELL() const { return ASHELL; }
Double_t MyConstants::getPAIRING() const { return PAIRING; }

void reading()
{
  MyParameters();
  //  ~MyParameters();
  MyParameters SetMyParas;
  //  SetMyParas.setEG();
  //  SetMyParas.setGammaG();
  //  SetMyParas.setSigmaG();

  //  Float_t E_K0 = 0;
  //  cout << "enhancement factor k0?" << endl; cin >> E_K0; 
  //  SetMyParas.setEK0(&E_K0);
  //  SetMyParas.getEK0();
  //  SetMyParas.setEK0();

  gROOT->Reset();
  gEnv->SetValue("Canvas.ShowEventStatus",1);
  gStyle->SetFrameLineWidth(3);
  gStyle->SetEndErrorSize(10);
  gStyle->SetOptFit(1);

  TCanvas *c=new TCanvas();

  gPad->SetFillColor(kWhite);

  TFrame *fr =new TFrame();
  fr->SetLineColor(kBlack);
  fr->SetLineWidth(3); 

  Bool_t UseLogScale = kFALSE;
  Bool_t ShowLegend = kFALSE;

  Int_t ScaleType = 0;
  Int_t LegendDisplay = 0;

  cout << "Plot PSF on Logarithmic or Linear scale?\n1 - Log\n2 - Lin" << endl;
  cin >> ScaleType;

  cout << "Show legend on plot?\n1 - Yes\n2 - No" << endl;
  cin >> LegendDisplay;

  switch(ScaleType)
    {
    case 1: 
      UseLogScale = kTRUE;
      break;
    case 2:
      UseLogScale = kFALSE;
      break;
    default:
      cerr << "Wrong choice for scale!\nRe-load ROOT and try again" << endl;
      exit(1);
      break;
    }

  switch(LegendDisplay)
    {
    case 1: 
      ShowLegend = kTRUE;
      break;
    case 2:
      ShowLegend = kFALSE;
      break;
    default:
      cout << "Wrong option for legend!\nDefault: Legend will not be displayed " << endl;
      ShowLegend = kFALSE;
      break;
    }

  TH1F *vframe;
  if(UseLogScale == kTRUE)
    //TH1F *vframe=c->DrawFrame(0,1E-9,25,1E-03);// Good for log scale
    vframe=c->DrawFrame(0,1E-9,35,1E-03);// Good for log scale

  else
    //TH1F *vframe=c->DrawFrame(0,-0.2E-06,25,4.0E-06);// Good for linear scale
    vframe=c->DrawFrame(0,-0.2E-06,35,4.0E-06);// Good for linear scale

  
  Int_t l=0;  
  Double_t energy[100]={0};
  Double_t cs[100]={0};
  Double_t dcs[100]={0};

  //const std::string iFile = "si28_gxn_caldwell.dat";
  const std::string iFile = "si28_gxn_goryachev.dat";

  ifstream inputfile;
  inputfile.open(iFile.c_str(), ios::in);

  if(!inputfile)
    {
      cerr << iFile << ": input file not found!" << endl;
      exit(1);
    }

  while(true)
    {
      inputfile>>energy[l]>>cs[l]>>dcs[l];

      if(inputfile.eof() || inputfile.fail()) break;

      l++;
    }
  cout<<"Number of lines read: "<<l<<endl;

  inputfile.close();

  Double_t f_E1[100] = {0};
  Double_t df_E1[100] = {0};

  const Double_t constant = 8.68e-08;

  Int_t i=0;

  for(i=0; i<l; i++)
    {
      f_E1[i] = constant * cs[i]/energy[i];
      df_E1[i] = (constant/energy[i])*dcs[i];

      //cout<<cs[i]<<"\t"<<dcs[i]<<"\t"<<f_E1[i]<<"\t"<<df_E1[i]<<endl;
    }


  //create a function with 2 parameters in the range [0,8]
  //i.e. (....,0,8,2) => Range: 0,8; number of parameters: 2
  //  TF1 *func=new TF1("fit",fitFunction,0,8,2);

  TF1 *func=new TF1("func",GLO,0,35,11);
  TF1 *func2=new TF1("func2",EGLO,0,35,13);
  TF1 *func3=new TF1("func3",EGLO_k0,0,35,13);//k0 from A-dependent model
  TF1 *func4=new TF1("func4",BA,0,35,7);
  TF1 *func5=new TF1("func5",KMF,0,35,11);

  TF1 *func6=new TF1("myBA",myFitFunction,0,35,6);


  Double_t E1 = 0.0, W1 = 0.0, C1 = 0.0;
  Double_t E2 = 0.0, W2 = 0.0, C2 = 0.0;

  Bool_t UserParas = kFALSE;
  Int_t ParasChoice = 0;

  cout << "Initial parametrization for free-fitting procedure?\n1 - (RIPL-3): \n[E1 = 20.10 MeV, W1 = 3.90 MeV, C1 = 10.5 mb]\n[E2 = 26.50 MeV, W2 = 8.70 MeV, C2 = 3.70 mb]\n2 - User-defined parametrization for Lorentzian: \n[E1, W1, C1],[E2, W2, C2]" << endl;

  cin >> ParasChoice;

  switch(ParasChoice)
    {
    case 1:
      UserParas = kFALSE;
      break;
    case 2:
      UserParas = kTRUE;
      break;
    default:
      cout << "Specified options not selected\nDefault to initial RIPL-3 parametrization for ROOT fit to Lorentzian"<<endl;
      UserParas = kFALSE;
      break;
    }

  if(UserParas == kFALSE){
      E1 = 20.10; W1 = 3.90; C1 = 10.5;
      E2 = 26.50; W2 = 8.70; C2 = 3.70;
    }
  else{
    cout << "Initial value E1 (centroid)? [MeV]" << endl; cin >> E1;
    cout << "Initial value W1 (width)? [MeV]" << endl; cin >> W1;
    cout << "Initial value C1 (cross section)? [mb]" << endl; cin >> C1;
    cout << "Initial value E2 (centroid)? [MeV]" << endl; cin >> E2;
    cout << "Initial value W2 (width)? [MeV]" << endl; cin >> W2;
    cout << "Initial value C2 (cross section)? [mb]" << endl; cin >> C2;
  }

  func6->SetParNames("E_{1}","#Gamma_{1}","#sigma_{1}","E_{2}","#Gamma_{2}","#sigma_{2}");
  func6->SetParameters(E1,W1,C1,E2,W2,C2);

  Double_t X_min = 0.0, X_max = 0.0;

  Bool_t UserFitRange = kFALSE;
  Int_t UserFitChoice = 0;

  cout << "Range of fit?\n1 - Default: x(min) = 17.0 MeV; x(max) = 35.0 MeV \n2 - User-defined x(min) and x(max)" << endl;

  cin >> UserFitChoice;

  switch(UserFitChoice)
    {
    case 1: UserFitRange = kFALSE; break;
    case 2: UserFitRange = kTRUE; break;
    default: 
      cout << "Incorrect specification for fitting range!\nDefault range will be used" << endl;
      UserFitRange = kFALSE;
      break;
    }

  if(UserFitRange == kFALSE){
    X_min = 17.0; X_max = 35.0; }
  else{
    cout << "Enter x(min): " << endl; cin >> X_min;
    cout << "Enter x(max): " << endl; cin >> X_max;
  }

  //SetLineColor: 1(black); 2(red); 3(green); 4(blue); 5(yellow); 6(magenta)

  func->SetLineStyle(1);
  func->SetLineColor(6);

  func2->SetLineStyle(2);
  func2->SetLineColor(4);

  func3->SetLineStyle(3);
  func3->SetLineColor(4);

  func4->SetLineStyle(5);
  func4->SetLineColor(kGreen+2);

  func5->SetLineStyle(5);
  func5->SetLineColor(1);

  func6->SetLineStyle(1);
  func6->SetLineWidth(3);
  func6->SetLineColor(kOrange+7);

  //Building graphs 
  TGraphErrors *gr=new TGraphErrors(i,energy,f_E1,NULL,df_E1);

  gr->SetMarkerColor(kBlack);
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(0.7);
  gr->SetLineWidth(1);
  gr->SetLineColor(kBlack);
  gr->Draw("P");
  //gr->Fit("myBA");
  gr->Fit("myBA","","",X_min,X_max);//define fitting range manually

  func->Draw("same");
  func2->Draw("same");
  func3->Draw("same");
  func4->Draw("same");
  func5->Draw("same");

  vframe->GetXaxis()->SetTitle("E_{#gamma} [MeV]");
  vframe->GetYaxis()->SetTitle("f_{E1} [MeV^{-3}] ");
  vframe->GetXaxis()->CenterTitle();
  vframe->GetYaxis()->CenterTitle();
  vframe->GetXaxis()->SetTitleSize(0.05);
  vframe->GetYaxis()->SetTitleSize(0.05);
  vframe->GetXaxis()->SetLabelSize(0.05);
  vframe->GetYaxis()->SetLabelSize(0.05);
  vframe->GetXaxis()->SetTitleOffset(1.2);
  vframe->GetYaxis()->SetTitleOffset(1.2);
  vframe->GetYaxis()->SetDecimals(1);

  gPad->SetGridx();
  gPad->SetGridy();

  //EGLO label
  const char* begin_label_EGLO = "EGLO (k_{0}=";
  Float_t k_0 = SetMyParas.getEK0();
  char full_label_EGLO[40];

  sprintf(full_label_EGLO,"%s%.2f)",begin_label_EGLO,k_0);
  //  cout<<full_label<<endl;

  const char* label_EGLO = full_label_EGLO;

  //Fit-range label
  //const char* begin_label_MyFit = "Fit to (#gamma,abs) data: ";
  const char* begin_label_MyFit = "Fit to (#gamma,xn) data: ";  
  Float_t min_MyFit = X_min;
  const char* between = " - ";
  Float_t max_MyFit = X_max;
  //const char* end_label_MyFit = " MeV (#gamma,n)";
  const char* end_label_MyFit = " MeV";  
  char full_label_MyFit[64];

  sprintf(full_label_MyFit,"%s%.2f%s%.2f%s",begin_label_MyFit,min_MyFit,between,max_MyFit,end_label_MyFit);

  const char* label_MyFit = full_label_MyFit;
  //  cout<<label_MyFit<<endl;

  TLegend *legend = new TLegend(0.20,0.45,0.90,0.75);
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->AddEntry(func,"GLO","l");  
  legend->AddEntry(func2,full_label_EGLO,"l");
  legend->AddEntry(func3,"EGLO (k_{0} from A-model)","l");  
  legend->AddEntry(func4,"BA (SLO)","l");  
  legend->AddEntry(func5,"KMF","l");
  legend->AddEntry(func6,full_label_MyFit,"l");
  legend->SetFillColor(kWhite);
  if(ShowLegend == kTRUE)
    legend->Draw();

  if(UseLogScale == kTRUE)
    gPad->SetLogy();

  delete fr;

  c->Update();
  gROOT->Time(0);
}

Double_t EGLO(Double_t *E, Double_t *par)
{
  MyConstants();
  MyConstants GetMyConsts;
  
  par[0] = 8.68e-08;
  par[1] = GetMyConsts.getPAIRING();
  par[2] = TMath::Pi();
  par[3] = GetMyConsts.getASHELL();
  par[4] = 0.7;

  MyParameters();
  MyParameters SetMyParas;

  //RIPL-3 parameters: 1st resonance
  par[5] = SetMyParas.getEG1();
  par[6] = SetMyParas.getGammaG1();
  par[7] = SetMyParas.getSigmaG1();

  //RIPL-3 parameters: 2nd resonance
  par[8] = SetMyParas.getEG2();
  par[9] = SetMyParas.getGammaG2();
  par[10] = SetMyParas.getSigmaG2();

  //Define enhancement factor k0 using explicit definition or class
  par[11] = SetMyParas.getEK0();

  par[12] = 4.5;

  Double_t constant = par[0];
  Double_t Delta = par[1];
  Double_t PI = par[2];
  Double_t a = par[3]; 
  Double_t Fk = par[4];

  Double_t EG1 = par[5];
  Double_t GammaG1 = par[6];
  Double_t SigmaG1 = par[7];

  Double_t EG2 = par[8];
  Double_t GammaG2 = par[9];
  Double_t SigmaG2 = par[10];

  Double_t k0 = par[11];
  Double_t E0 = par[12];


  Double_t eFactor_res1 = 0;
  eFactor_res1 = k0 + ((1-k0)*(E[0]-E0)/(EG1-E0));

  Double_t eFactor_res2 = 0;
  eFactor_res2 = k0 + ((1-k0)*(E[0]-E0)/(EG2-E0));

  Double_t Theta = 0;
  Double_t Ex = 0;
  Ex = (GetMyConsts.getSn() - E[0]) - Delta;
  if(Ex > 0) Theta = sqrt(Ex/a);
  else Theta = 0;

  //~MyConstants();
  //~MyParameters();

  //First resonance

  Double_t fWidth1 = 0;
  fWidth1 = (GammaG1/pow(EG1,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  fWidth1 = fWidth1*eFactor_res1;

  Double_t res1_part1 = 0;
  Double_t res1_part2 = 0;

  res1_part1 = (Fk*4*pow(PI,2.0)*pow(Theta,2.0)*GammaG1)/pow(EG1,5.0);

  res1_part2 = (E[0]*fWidth1)/(pow((pow(E[0],2.0)-pow(EG1,2.0)),2.0)
			       + (pow(E[0],2.0)*pow(fWidth1,2.0)));


  //Second resonance

  Double_t fWidth2 = 0;
  fWidth2 = (GammaG2/pow(EG2,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  fWidth2 = fWidth2*eFactor_res2;

  Double_t res2_part1 = 0;
  Double_t res2_part2 = 0;

  res2_part1 = (Fk*4*pow(PI,2.0)*pow(Theta,2.0)*GammaG2)/pow(EG2,5.0);

  res2_part2 = (E[0]*fWidth2)/(pow((pow(E[0],2.0)-pow(EG2,2.0)),2.0)
			       + (pow(E[0],2.0)*pow(fWidth2,2.0)));


  //Sum respective resonance terms

  Double_t sum_res1 = 0;

  sum_res1 = constant*SigmaG1*GammaG1*(res1_part1 + res1_part2);

  Double_t sum_res2 = 0;

  sum_res2 = constant*SigmaG2*GammaG2*(res2_part1 + res2_part2);


  //Define GLO PSF

  Double_t fE1_EGLO = 0;

  fE1_EGLO =  sum_res1 + sum_res2;

  return fE1_EGLO;
}

Double_t EGLO_k0(Double_t *E, Double_t *par)
{
  MyConstants();
  MyConstants GetMyConsts;

  par[0] = 8.68e-08;
  par[1] = GetMyConsts.getPAIRING();
  par[2] = TMath::Pi();
  par[3] = GetMyConsts.getASHELL();
  par[4] = 0.7;

  MyParameters();
  MyParameters SetMyParas;

  //RIPL-3 parameters: 1st resonance
  par[5] = SetMyParas.getEG1();
  par[6] = SetMyParas.getGammaG1();
  par[7] = SetMyParas.getSigmaG1();

  //RIPL-3 parameters: 2nd resonance
  par[8] = SetMyParas.getEG2();
  par[9] = SetMyParas.getGammaG2();
  par[10] = SetMyParas.getSigmaG2();

  //Get Atomic Mass
  par[11] = GetMyConsts.getAtomicMass();
  par[12] = 4.5;

  Double_t constant = par[0];
  Double_t Delta = par[1];
  Double_t PI = par[2];
  Double_t a = par[3]; 
  Double_t Fk = par[4];

  Double_t EG1 = par[5];
  Double_t GammaG1 = par[6];
  Double_t SigmaG1 = par[7];

  Double_t EG2 = par[8];
  Double_t GammaG2 = par[9];
  Double_t SigmaG2 = par[10];

  Double_t A = par[11];
  Double_t E0 = par[12];

  //Calculate k0 from A-dependent model
  Double_t k0 = 0;
  k0 = 1 + ((0.09*pow((A-148),2.0)) * exp(-0.180*(A-148)));

  Double_t eFactor_res1 = 0;
  eFactor_res1 = k0 + ((1-k0)*(E[0]-E0)/(EG1-E0));

  Double_t eFactor_res2 = 0;
  eFactor_res2 = k0 + ((1-k0)*(E[0]-E0)/(EG2-E0));

  Double_t Theta = 0;
  Double_t Ex = 0;
  Ex = (GetMyConsts.getSn() - E[0]) - Delta;
  if(Ex > 0) Theta = sqrt(Ex/a);
  else Theta = 0;

  //~MyConstants();
  //~MyParameters();

  //First resonance

  Double_t fWidth1 = 0;
  fWidth1 = (GammaG1/pow(EG1,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  fWidth1 = fWidth1*eFactor_res1;

  Double_t res1_part1 = 0;
  Double_t res1_part2 = 0;

  res1_part1 = (Fk*4*pow(PI,2.0)*pow(Theta,2.0)*GammaG1)/pow(EG1,5.0);

  res1_part2 = (E[0]*fWidth1)/(pow((pow(E[0],2.0)-pow(EG1,2.0)),2.0)
			       + (pow(E[0],2.0)*pow(fWidth1,2.0)));


  //Second resonance

  Double_t fWidth2 = 0;
  fWidth2 = (GammaG2/pow(EG2,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  fWidth2 = fWidth2*eFactor_res2;

  Double_t res2_part1 = 0;
  Double_t res2_part2 = 0;

  res2_part1 = (Fk*4*pow(PI,2.0)*pow(Theta,2.0)*GammaG2)/pow(EG2,5.0);

  res2_part2 = (E[0]*fWidth2)/(pow((pow(E[0],2.0)-pow(EG2,2.0)),2.0)
			       + (pow(E[0],2.0)*pow(fWidth2,2.0)));


  //Sum respective resonance terms

  Double_t sum_res1 = 0;

  sum_res1 = constant*SigmaG1*GammaG1*(res1_part1 + res1_part2);

  Double_t sum_res2 = 0;

  sum_res2 = constant*SigmaG2*GammaG2*(res2_part1 + res2_part2);


  //Define GLO PSF

  Double_t fE1_EGLO = 0;

  fE1_EGLO =  sum_res1 + sum_res2;

  return fE1_EGLO;
}


Double_t GLO(Double_t *E, Double_t *par)
{
  MyConstants();
  MyConstants GetMyConsts;

  par[0] = 8.68e-08;
  par[1] = GetMyConsts.getPAIRING();
  par[2] = TMath::Pi();
  par[3] = GetMyConsts.getASHELL();
  par[4] = 0.7;

  MyParameters();
  MyParameters SetMyParas;

  //RIPL-3 parameters: 1st resonance
  par[5] = SetMyParas.getEG1();
  par[6] = SetMyParas.getGammaG1();
  par[7] = SetMyParas.getSigmaG1();

  //RIPL-3 parameters: 2nd resonance
  par[8] = SetMyParas.getEG2();
  par[9] = SetMyParas.getGammaG2();
  par[10] = SetMyParas.getSigmaG2();

  Double_t constant = par[0];
  Double_t Delta = par[1];
  Double_t PI = par[2];
  Double_t a = par[3]; 
  Double_t Fk = par[4];

  Double_t EG1 = par[5];
  Double_t GammaG1 = par[6];
  Double_t SigmaG1 = par[7];

  Double_t EG2 = par[8];
  Double_t GammaG2 = par[9];
  Double_t SigmaG2 = par[10];

  Double_t Theta = 0;
  Double_t Ex = 0;
  Ex = (GetMyConsts.getSn() - E[0]) - Delta;
  if(Ex > 0) Theta = sqrt(Ex/a);
  else Theta = 0;

  //~MyConstants();
  //~MyParameters();

  //First resonance

  Double_t fWidth1 = 0;
  fWidth1 = (GammaG1/pow(EG1,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  Double_t res1_part1 = 0;
  Double_t res1_part2 = 0;

  res1_part1 = (Fk*4*pow(PI,2.0)*pow(Theta,2.0)*GammaG1)/pow(EG1,5.0);

  res1_part2 = (E[0]*fWidth1)/(pow((pow(E[0],2.0)-pow(EG1,2.0)),2.0)
			       + (pow(E[0],2.0)*pow(fWidth1,2.0)));


  //Second resonance

  Double_t fWidth2 = 0;
  fWidth2 = (GammaG2/pow(EG2,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  Double_t res2_part1 = 0;
  Double_t res2_part2 = 0;

  res2_part1 = (Fk*4*pow(PI,2.0)*pow(Theta,2.0)*GammaG2)/pow(EG2,5.0);

  res2_part2 = (E[0]*fWidth2)/(pow((pow(E[0],2.0)-pow(EG2,2.0)),2.0)
			       + (pow(E[0],2.0)*pow(fWidth2,2.0)));


  //Sum respective resonance terms

  Double_t sum_res1 = 0;

  sum_res1 = constant*SigmaG1*GammaG1*(res1_part1 + res1_part2);

  Double_t sum_res2 = 0;

  sum_res2 = constant*SigmaG2*GammaG2*(res2_part1 + res2_part2);


  //Define GLO PSF

  Double_t fE1_GLO = 0;

  fE1_GLO =  sum_res1 + sum_res2;

  return fE1_GLO;
}


Double_t BA(Double_t *E, Double_t *par)
{
  par[0] = 8.68e-08;

  MyParameters();
  MyParameters SetMyParas;

  //RIPL-3 parameters: 1st resonance
  par[1] = SetMyParas.getEG1();
  par[2] = SetMyParas.getGammaG1();
  par[3] = SetMyParas.getSigmaG1();

  //RIPL-3 parameters: 2nd resonance
  par[4] = SetMyParas.getEG2();
  par[5] = SetMyParas.getGammaG2();
  par[6] = SetMyParas.getSigmaG2();

  Double_t constant = par[0];

  Double_t EG1 = par[1];
  Double_t GammaG1 = par[2];
  Double_t SigmaG1 = par[3];

  Double_t EG2 = par[4];
  Double_t GammaG2 = par[5];
  Double_t SigmaG2 = par[6];

  //~MyParameters();

  //First resonance

  Double_t res1 = 0;
  Double_t nominator1 = 0;
  Double_t denominator1 = 0;

  nominator1 = SigmaG1*E[0]*pow(GammaG1,2.0);

  denominator1 = pow((pow(E[0],2.0) - pow(EG1,2.0)),2.0)
    + (pow(E[0],2.0)*pow(GammaG1,2.0));

  res1 = nominator1/denominator1;

  //Second resonance

  Double_t res2 = 0;
  Double_t nominator2 = 0;
  Double_t denominator2 = 0;

  nominator2 = SigmaG2*E[0]*pow(GammaG2,2.0);

  denominator2 = pow((pow(E[0],2.0) - pow(EG2,2.0)),2.0)
    + (pow(E[0],2.0)*pow(GammaG2,2.0));

  res2 = nominator2/denominator2;


  //Define BA PSF (aka SLO)

  Double_t fE1_BA = 0;

  fE1_BA =  constant*(res1 + res2);

  return fE1_BA;
}

Double_t KMF(Double_t *E, Double_t *par)
{
  MyConstants();
  MyConstants GetMyConsts;

  par[0] = 8.68e-08;
  par[1] = 0.7;
  par[2] = TMath::Pi();
  par[3] = GetMyConsts.getPAIRING();
  par[4] = GetMyConsts.getASHELL();

  MyParameters();
  MyParameters SetMyParas;

  //RIPL-3 parameters: 1st resonance
  par[5] = SetMyParas.getEG1();
  par[6] = SetMyParas.getGammaG1();
  par[7] = SetMyParas.getSigmaG1();

  //RIPL-3 parameters: 2nd resonance
  par[8] = SetMyParas.getEG2();
  par[9] = SetMyParas.getGammaG2();
  par[10] = SetMyParas.getSigmaG2();

  Double_t constant = par[0];
  Double_t Fk = par[1];
  Double_t PI = par[2];
  Double_t Delta = par[3];
  Double_t a = par[4];

  Double_t EG1 = par[5];
  Double_t GammaG1 = par[6];
  Double_t SigmaG1 = par[7];

  Double_t EG2 = par[8];
  Double_t GammaG2 = par[9];
  Double_t SigmaG2 = par[10];

  Double_t Theta = 0;
  Double_t Ex = 0;
  Ex = (GetMyConsts.getSn() - E[0]) - Delta;
  if(Ex > 0) Theta = sqrt(Ex/a);
  else Theta = 0;

  //~MyConstants();
  //~MyParameters();

  //First resonance

  Double_t res1 = 0;
  Double_t nominator1 = 0;
  Double_t denominator1 = 0;

  Double_t fWidth1 = 0;
  fWidth1 = (GammaG1/pow(EG1,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  nominator1 = SigmaG1*GammaG1*EG1*fWidth1;

  denominator1 = pow((pow(E[0],2.0) - pow(EG1,2.0)),2.0);

  res1 = nominator1/denominator1;

  //Second resonance

  Double_t res2 = 0;
  Double_t nominator2 = 0;
  Double_t denominator2 = 0;

  Double_t fWidth2 = 0;
  fWidth2 = (GammaG2/pow(EG2,2.0))*(pow(E[0],2.0) + (4*pow(PI,2.0)*pow(Theta,2.0)) );

  nominator2 = SigmaG2*GammaG2*EG2*fWidth2;

  denominator2 = pow((pow(E[0],2.0) - pow(EG2,2.0)),2.0);

  res2 = nominator2/denominator2;

  //Define KMF PSF

  Double_t fE1_KMF = 0;

  fE1_KMF =  constant*Fk*(res1 + res2);

  return fE1_KMF;
}

Double_t myFitFunction(Double_t *E, Double_t *par)
{

  const Double_t constant = 8.68e-08;

  //par[0] => EG1
  //par[1] => GammaG1
  //par[2] => SigmaG1

  //par[3] => EG2
  //par[4] => GammaG2
  //par[5] => SigmaG2

  //First resonance

  Double_t res1 = 0;
  Double_t nominator1 = 0;
  Double_t denominator1 = 0;

  nominator1 = par[2]*E[0]*pow(par[1],2.0);

  denominator1 = pow((pow(E[0],2.0) - pow(par[0],2.0)),2.0)
    + (pow(E[0],2.0)*pow(par[1],2.0));

  res1 = nominator1/denominator1;

  //Second resonance

  Double_t res2 = 0;
  Double_t nominator2 = 0;
  Double_t denominator2 = 0;

  nominator2 = par[5]*E[0]*pow(par[4],2.0);

  denominator2 = pow((pow(E[0],2.0) - pow(par[3],2.0)),2.0)
    + (pow(E[0],2.0)*pow(par[4],2.0));

  res2 = nominator2/denominator2;


  //Define BA PSF (aka SLO)

  Double_t my_fE1_BA = 0;

  my_fE1_BA =  constant*(res1 + res2);

  return my_fE1_BA;
}
