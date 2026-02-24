#include <cmath>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    float alpha=0.012f;
    int brojac=1;
    for(; alpha<2*M_PI-0.0001; alpha=alpha+(M_PI/180))
    {
        cout<<brojac<<": ";
        cout<<cos(alpha)*2<<" ";
        cout<<sin(alpha)<<endl;
        brojac++;
    
    }
}