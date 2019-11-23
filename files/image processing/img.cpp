#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <deque>
using namespace std;

double TEMPERATURA;
int L = 216;
int delta;
int dist;

void opendata();
// void create_lines(int);
// int setParameters();

std::vector<int> data;
std::vector<int> xa;
std::vector<int> xm;

int main(){

  int nr_n = setParameters();
  create_lines(nr_n);
  opendata();


  std::vector<int> volume_hole(6, 0);
  int total_volume_cells =0;

  for (int i = 0; i < L*L; i++){
    int x = i/L;
    int search = x/(dist+delta);
    if(data[i]!=0){
      total_volume_cells ++;

      if(x >= xm[search]  && x <= xa[search]){

        volume_hole[search] = volume_hole[search] + 1;
        // cout << "x "<<x<<" search "<<search<<" volume_hole "<< volume_hole[search]<<endl;
      }else{
        cout << "x "<<x<<" search "<<search<<endl;
      }
    }
  }
  int vol_inside=0;
  for (int i =0; i <nr_n; i++){
    vol_inside += volume_hole[i];
  }


cout << " total volume = "<<total_volume_cells<<" volume inside "<< vol_inside<<endl;

for(int i = 0; i < nr_n; i++){
  cout<<"xm[i] = "<<xm[i]<<" xa[i] "<<xa[i]<<endl;
}
  return 0;
}

void opendata(){
  std::string line;
  ifstream myfile;

  myfile.open("/home/andre/Documents/files/OUTPUT/foto_final_label70.txt");

  if(myfile.is_open()){

    while(getline(myfile, line)){
      std::stringstream lineStream(line);
      int value;
      while(lineStream >> value)
        {
            data.push_back(value);
        }
    }
    myfile.close();
  }else {
    cout<<"failed to open"<<endl;
  }
}
// int setParameters(){
//   std::vector<int> v;
//   std::string line;
//   ifstream myfile;
//
//   myfile.open("/home/andre/Documents/files/INPUT/inputparam.txt");
//
//   if(myfile.is_open()){
//
//     while(getline(myfile, line)){
//       std::stringstream lineStream(line);
//       int value;
//       while(lineStream >> value){
//             v.push_back(value);
//         }
//     }
//     myfile.close();
//   }else {
//     cout<<"failed to open"<<endl;
//   }
//   dist = v[0];
//   delta =v[1];
//   TEMPERATURA = v[2];
//   int nr_n = (L-delta)/(dist+delta) + 1;
//   return nr_n;
// }
// void create_lines(int nr_n){
//   int Xa = L/2 + (delta-1)/2;
//   int Xm = L/2 - (delta-1)/2;
//
//   for (int i = (nr_n)/2; i < nr_n; i++){
//     xa.push_back(Xa);
//     xm.push_back(Xm);
//     Xa += delta + dist;
//     Xm += delta + dist;
//   }
//
//   Xa = L/2 + delta/2;
//   Xm = L/2 - delta/2;
//
//   std::vector<int>::iterator it;
//   for (int i = (nr_n)/2 - 1; i >= 0; i--){
//
//     Xa -= delta + dist;
//     Xm -= delta + dist;
//     it = xa.begin();
//     xa.insert(it, Xa);
//     it = xm.begin();
//     xm.insert(it, Xm);
//
//
//   }
// }
