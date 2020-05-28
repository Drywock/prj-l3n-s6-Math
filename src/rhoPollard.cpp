#include <iostream>
#include <numeric>
#include <cmath>
#include <vector> 
#include <algorithm>
#include "rhoPollard.h"
#include "functions.h"
#include "time.h"
int rhoPollard::getDivisor(int n){

    int x = std::rand()%n+1;
    int y = x;
    int g = 1;
    //fn is f(x) = x*x + random between 0 and n+1
    while(g==1)
    {
        
        x = ((x*x) + std::rand()%(n+1))%(n);    
        y = ((y*y) + std::rand()%(n+1));
        y = ((y*y) + std::rand()%(n+1))%(n);
        g = gcd(std::abs(x-y),n);
    }
    return g;
}


void rhoPollard::factorize(int n)
{
    //std::cout<<"factorization of "<<n<<" ";

    if(n == 1){
        return ;
    }

    if(isPrime(n)) 
    {
        if(!std::count(rhoPollard::factors.begin(), rhoPollard::factors.end(), n)){
            rhoPollard::factors.push_back(n);
        }
        return ;
    }
    
    int divisor;
    divisor = rhoPollard::getDivisor(n);    
    rhoPollard::factorize(divisor);
    rhoPollard::factorize(n/divisor);
}

void rhoPollard::showFactors(){

    for (int i = 0; i != rhoPollard::factors.size(); ++i)
    {
        std::cout<<rhoPollard::factors[i]<<" ";
    }
}

std::vector<int> rhoPollard::getFactors(int n){
    rhoPollard::factors.clear();
    rhoPollard::factorize(n);
    return rhoPollard::factors;
}