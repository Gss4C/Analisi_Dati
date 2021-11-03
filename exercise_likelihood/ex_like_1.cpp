//Questo serve per poter acquisire i file
using namespace std;
void ex_like_1(string filename="exercise_Likelihood_1.txt"){
  ifstream f(filename);
  float xs;
  while(!f.eof()){
    f >> xs;
    cout << " xs is "<<xs<<endl;
  };
}