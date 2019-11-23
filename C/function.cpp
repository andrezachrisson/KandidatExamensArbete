#include <iostream>
using namespace std;


int main(){
  int pt = 108; // look at this pt
  int L = 216;
  int delta = 5;
  int dist = 10;
  int Xa = L/2 + (delta-1)/2;
  int Xm = L/2 - (delta-1)/2;
  int n = (L - delta)/(dist + delta) + 1;

  int xa[n];
  int xm[n];

  for (int i = (n)/2; i < n; i++){
    xa[i] = Xa;
    xm[i] = Xm;

    Xa += delta + dist;
    Xm += delta + dist;
  }
  Xa = L/2 + delta/2;
  Xm = L/2 - delta/2;
  for (int i = (n)/2 - 1; i >= 0; i--){
    Xa -= delta + dist;
    Xm -= delta + dist;
    xa[i] = Xa;
    xm[i] = Xm;
  }
int search=0;
cout<<"n = "<<n<<endl;
for (int i =4; i<L; i+=dist+delta){
pt=i;
search = pt/(dist);

cout <<"search = "<<search<<" pt = "<<pt<<" xm[search]"<< xm[search]<<endl;
if (pt == (xa[search] - 1)){
cout <<"next to xa"<<endl;
}else if(pt == (xm[search]) + 1){
cout <<"next to xm"<<endl;
}else {
}

}

return 0;
}
