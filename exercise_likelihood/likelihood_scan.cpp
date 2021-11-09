using namespace std;
#include <vector>

using namespace std;
#include <vector>

Double_t ext_likelihood(int s, int b, vector<Double_t> x, Double_t theta[])
{
    int N = x.size();
    Double_t y = 0;
    /*TF1 *ps = new TF1("ps", "gaus", 0, 1000);
        TF1 *pb = new TF1("pb", "1/([0]) * TMath::Exp( -x/[0] )", 0, 1000);
        ps->SetParameters(theta[0], theta[1], theta[2]);
        pb->SetParameter(0, theta[3]);
        TF1 *likelihood = new TF1("likelihood", "-2*TMath::Log([0] * ps + [1] * pb )", 0, 1000);*/
    TF1 *likelihood = new TF1("likelihood", "-2*log( [0]/sqrt(2*TMath::Pi()*[5]*[5])*
                                                TMath::Exp(-((x - [4]) * (x - [4])) / (2 *[5] *[5])) +
                                                [1] / ([2]) * TMath::Exp(-x / [2])) ", 0, 1000);
                      likelihood->SetParameters(s, b, theta[3], theta[0], theta[1], theta[2]);
    Double_t sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += likelihood->Eval(x.at(i));
    }
    y = sum - 2 * TMath::Log(TMath::Poisson(N, s + b)) + 2 * N * TMath::Log(s + b);
    return y;
}

vector<Double_t> fromfile(string filename)
{
    ifstream f(filename + ".txt");
    vector<Double_t> data;
    Double_t xs;

    while (!f.eof())
    {
        f >> xs;
        data.push_back(xs);
    }
    return data;
}

void likelihood_scan()
{
    for (int j = 1; j < 5; j++)
    {
        vector<Double_t> x_1 = fromfile(("exercise_Likelihood_" + to_string(j)).c_str());
        vector<Double_t> params = fromfile(("model_" +to_string(j)).c_str());
        


        int N = x_1.size();
        Double_t yi, y[N], tot_s[N];
        Double_t theta[3];
        
        /*theta[1] = 400;
        theta[0] = 1 / (sqrt(2 * TMath::Pi() * theta[1] * theta[1]));
        theta[2] = 70;
        theta[3] = 200;*/

        //I am considering the case b+s=N
        /*int b = 980;
        TCanvas *c = new TCanvas();
    for(int s = 19; s < N; s++)
    {
        yi = ext_likelihood(s, b, x_1, theta);
        y[s-19] = yi;
        tot_s[s-19] = s;
    }
    TGraph *g1 = new TGraph(N-19, tot_s, y);
        g1->SetTitle("Logaritmo della Likelihood al variare di S");
        g1->GetXaxis()->SetTitle("S");
        g1->GetYaxis()->SetTitle("-2*Log(L)");
        g1->SetMarkerStyle(4);
        g1->SetMarkerColor(4);
        g1->Draw("AP");*/

        //I am considering the case b+s =/= N
        TCanvas *c1 = new TCanvas();
        TGraph2D *g2 = new TGraph2D();
        //TH2D * h =new TH2D("H2", "H2", 500 , 0, 2*N , 500 ,0,2*N);
        int i = 0;
        for (int s2 = 0; s2 < N; s2 += 10)
        {
            for (int b2 = 0; b2 < N; b2 += 10)
            {
                if (s2 + b2 < 2.5 * N && s2 + b2 > 0.26 * N)
                {
                    double z_fin = ext_likelihood(s2, b2, x_1, theta);
                    g2->SetPoint(i, s2, b2, z_fin);
                    i++;
                }
                else
                {
                    g2->SetPoint(i, s2, b2, 20000);
                    i++;
                }
            }
        }
        g2->SetTitle("-2*log(L(s,b))");
        g2->GetXaxis()->SetTitle("S");
        g2->GetYaxis()->SetTitle("B");
        g2->SetMarkerStyle(22);
        g2->Draw("surf1");
    }

    /*
    This was the first test, made for try functions
    int s = (x_1.size()) / 2;
    int b = (x_1.size()) / 2;

    y = ext_likelihood(s, b, x_1, theta);
    cout << y << endl;*/
}