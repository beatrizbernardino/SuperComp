#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <thrust/iterator/counting_iterator.h>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <random>
using namespace std;


struct meu_functor
{
    char b;
    thrust::device_ptr<char> sa;
    thrust::device_ptr<int> calc;

   

    meu_functor(char b_, thrust::device_ptr<char> sa_,thrust::device_ptr<int> calc_ ): 
    b(b_),sa(sa_), calc(calc_){};
    __host__ __device__
    int operator()(const int& x) {

        int val = (b==sa[x-1]?2:-1);

        int diagonal= calc[x-1]+ val;
        int delecao=calc[x]-1;

        if(diagonal>delecao && diagonal>0){
            return diagonal;
        }
        else if( delecao >diagonal && delecao>0){
            return delecao;
        }else{
            return 0;

        }
    

    }
};


struct esquerda
{
    __host__ __device__
    int operator()(const int& x, const int & y) {

       if(y>=(x-1) && y>=0){
           return y;
       }else if((x-1)>y &&(x-1)>=0){
           return (x-1);
       }else{

           return 0;
       }

    }
};



int main()
{
    int N, M;
    cin >> N;
    cin >> M;

    vector<char> a;
    vector<char> b;
 
    vector<string>subseq_a;
    vector<string>subseq_b;

    a.reserve(N+1);
    b.reserve(M+1);
    subseq_a.reserve(N+1);
    subseq_b.reserve(M+1);
   
  
    for(int i=0; i<N; i++){

        cin>> a[i];
       
    }for(int i=0; i<M; i++){

        cin>> b[i];
        
    }


    for(int i=0; i< N; i++){
        string s="";
        for(int j=i; j<N; j++){

            s+=a[j];
            subseq_a.push_back(s);
        }
    }

    int suba_size= subseq_a.size();

    for(int i=0; i< M; i++){
        string s="";
        for(int j=i; j<M; j++){

            s+=b[j];
            subseq_b.push_back(s);
        }
    }

    int subb_size= subseq_b.size();
    thrust::device_vector<int> calc[2];

    thrust::counting_iterator<int> c0(1);

  
    thrust::device_vector<int> max_scores;

    #pragma omp  for collapse(2)
    for(int i=0; i<subb_size; i++){
        for(int j=0; j<suba_size; j++){


            thrust::device_vector<char> sa(subseq_a[j].begin(), subseq_a[j].end());
            thrust::device_vector<char> sb(subseq_b[i].begin(), subseq_b[i].end());
            calc[0].resize(int(sa.size())+1);
            calc[1].resize(int(sa.size())+1); 
            thrust::fill(calc[0].begin(), calc[0].end(),0);
            thrust::counting_iterator<int> c1(int(sa.size()+1));
           
            for(int n=0; n<int(sb.size()); n++ ){

                char b=sb[n];

                thrust::transform(c0, c1, calc[1].begin()+1, meu_functor( b, sa.data(), calc[0].data()));
                thrust::inclusive_scan(calc[1].begin()+1, calc[1].end(), calc[0].begin()+1, esquerda());
             
            }      
            max_scores.push_back(calc[0].back());         
        }    
    }

    // thrust::device_vector<int>::iterator best_score= thrust::max_element(max_scores.begin(), max_scores.end() );
    int  best_score= thrust::reduce(max_scores.begin(), max_scores.end(), 0, thrust::maximum<int>());
    
    cout<<best_score<<endl;
    


    return 0;
}