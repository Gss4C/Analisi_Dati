void es_01()
{
    TF1 * f1 = new TF1("f1" , "TMath::Gaus(x,[0],[1])" , 0 , 1000);
    gauss->SetParameters()
}