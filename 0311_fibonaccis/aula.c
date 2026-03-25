#include<stdio.h>

long long int num_cr = 0;

long long int fib_rec(int n){
    num_cr++;
    if(n<=1) return n;
    return fib_rec(n-1) + fib_rec(n-2);
}

long long fib_iter(int n){
    if(n<=1) return n;

    long long int n_1 = 0;
    long long int n_2 = 1;

    long long int res = 0;
    int i=1;
    while(i<=n){
        res = n_1 + n_2;
        n_2 = n_1;
        n_1 = res;
        i++;
    }
    return res;   
}

int main(){

    int n = 50;

    printf("\nestou calculando fib, relaxa o burco aê\n");
    long long int res = fib_iter(n);
    printf("\no %dº num fib é %lld com %lld chamadas\n", n, res, num_cr);

    return 0;
}
