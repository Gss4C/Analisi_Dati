using namespace std;
#include <vector>

Double_t ext_likelihood(int s, int b, vector<Double_t> x, Double_t theta[4])
{
    int N = x.size();
    Double_t y = 0;

    TF1 *ps = new TF1("ps", "gaus", 0, 1000);
    TF1 *pb = new TF1("pb", "[0] * exp( -x/[0] )", 0, 1000);
    TF1 *likelihood = new TF1("likelihood", "-2*log([0] * pb + [1] * ps)", 0, 1000);
    //TF1 *poisson = new TF1("poisson", "exp(-(s+b))/(TMath::Factorial(N))", 0, 1000);
    ps->SetParameters(theta[0], theta[1], theta[2]);
    pb->SetParameter(0, theta[3]);

    likelihood->SetParameters(b, s);
    Double_t sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += likelihood->Eval(x.at(i));
        //cout<<likelihood->Eval(x.at(i))<<endl;
    }

    Double_t n_fac_strl ; 
    n_fac_strl = TMath::Sqrt(2 * TMath::Pi() * N ) * pow( N/TMath::E() ,N);
    y = sum - 1200/(N *  TMath::Log(N)+0.5 * TMath::Log(2* TMath::Pi()*N));
    //y = sum + log(exp(-(s + b)) / (TMath::Factorial(N)));
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
    Double_t y;
    Double_t theta[4];
    theta[1] = 400;
    theta[0] = 1 / (sqrt(2 * TMath::Pi() * theta[1] * theta[1]));
    theta[2] = 70;
    theta[3] = 200;

    vector<Double_t> x_1 = fromfile(("exercise_Likelihood_" + to_string(1)).c_str());

    int s = (x_1.size()) / 2;
    int b = (x_1.size()) / 2;

    y = ext_likelihood(s, b, x_1, theta);
    cout << y << endl;
}