using namespace std;
#include <vector>

//----Funzioni----//

/*float ext_likelihood( int s , int b , vector<float> x , float theta[4] )
{
    TF1 * ps = new TF1("ps" , "gaus" , 0 , 1000 );
    TF1 * pb = new TF1("pb" , "1/([3]) * exp( -x*[3] )" , 0 , 1000 );
    TF1 * poisson = new TF1("poisson" , "exp(-(s+b))/()" , 0 , 1000 );
    float a=0;
    return a;
}*/

vector<float> getfromfile(string filename)
{
    ifstream f(filename + ".txt");
    vector<float> data;
    float xs;

    while (!f.eof())
    {
        f >> xs;
        data.push_back(xs);
    }
    return data;
}

void likelihood_scan()
{
 //   vector<float> x_1 = getfromfile(("exercise_Likelihood_" + to_string(1)).c_str());
}