#include <iostream>
#include <numeric>
#include <cmath>
#include <vector> 
#include "functions.h"
#include "time.h"

bool isPrime(int n){
    int max=std::sqrt(n);
    for(int i=2;i<=max;i++){
        if((n%i)==0){
            return false;
        }
    }
    return true;
}

int gcd(int a,int b)
{
    if(b==0){
        return a;
    }
    else{
        return gcd(b,a%b);
    }
}