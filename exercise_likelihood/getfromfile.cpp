//Questo serve per poter acquisire i file
using namespace std;
void ex_like_1(string filename)
{
  ifstream f(filename + ".txt");
  float xs;
  TH1F *h1 = new TH1F("Histo_prova", filename.c_str(), 200, 0, 1000);
  while (!f.eof())
  {
    f >> xs;
    //cout << " xs is "<<xs<<endl;
    h1->Fill(xs);
  };
  TCanvas *c = new TCanvas();
  h1->Draw();
  c->SaveAs((filename + ".png").c_str());
}

void getfromfile()
{
  for (int i = 1; i < 5; i++)
  {
    ex_like_1(("exercise_Likelihood_" + to_string(i)).c_str());
  }
}