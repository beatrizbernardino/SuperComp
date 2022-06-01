#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <thrust/iterator/counting_iterator.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <random>
using namespace std;

struct meu_functor
{
    string * subseq_a;
    string * subseq_b;
    thrust::device_ptr<int> sa;
    thrust::device_ptr<int> sb;
    thrust::device_ptr<char> a;

    // subseq_a(subseq_a_),subseq_b(subseq_b_),
    // vector<string>subseq_a_, vector<string>subseq_b_, 

    meu_functor(string *subseq_a_, string *subseq_b_,thrust::device_ptr<int> sa_,thrust::device_ptr<int> sb_ ,thrust::device_ptr<char> a_ ): 
    subseq_a(subseq_a_),subseq_b(subseq_b_),sa(sa_), sb(sb_), a(a_){};
    __host__ __device__
    int operator()(const int& x) {
       
        // thrust::device_ptr<char> a(sa[x][0].begin(), sa[x][0].end());
        // for(int i=0; i<int(subseq_a[sa[x]].length()); i++){
        //     a[i]='a';

        // }
        // for (int i=0; i< int(subseq_b.size()); i++){
        //     string b= subseq_b[x][i];

        // }

       
        return 2;

        // return 2*2;

        // int index=sa[x];
        // string a= subseq_a[index];
        // for (int i =0; i<int(&sb.size()); i++){
        //     string b= subseq_b[i];
        //     // thrust::transform(c0, c1, calc[1].begin()+1, meu_functor(subseq_a, subseq_b, sa, sb));   
        //     // thrust::inclusive_scan(calc[1].begin()+1, calc[1].end(), calc[0].begin()+1, thrust::maximum<int>());
        // }

    }
};


// struct meu_functor
// {
//     int a;    
//     meu_functor(int a_) : a(a_) {};
//     __host__ __device__
//     double operator()(const int& x, const int& y) {
//            return a * x + y;
//     }
// };


int main()
{
    int N, M;
    cin >> N;
    cin >> M;

    vector<char> a;
    vector<char> b;
    vector<string>subseq_a;
    vector<string>subseq_b;
    vector<vector<int>> H(N+1, vector<int>(M+1,0));
    a.reserve(N+1);
    b.reserve(M+1);
    subseq_a.reserve(N+1);
    subseq_a.reserve(N+1);  

    
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


    thrust::device_vector<int> sa;
   
    thrust::device_vector<int> sb(subb_size);

    thrust::sequence( sb.begin(), sb.end(), 1);


        for(int i=0; i<suba_size; i++){

            
            for(int j=0; j<int(subb_size); j++){

                sa.push_back(i);  
  
            }
        }

        for(int i=0; i<subb_size; i++){


            sa.push_back(i);  
  
        }
        
 
        

        thrust::device_vector<int> calc[2];
        calc[0].resize(N+1);
        calc[1].resize(N+1); 
        thrust::fill(calc[0].begin(), calc[0].end(),0);

        thrust::counting_iterator<int> c0(0);
        thrust::counting_iterator<int> c1(sa.size());
        thrust::device_vector<char>char_a ;

        cout<<subseq_a[10];
  
        thrust::transform(c0, c1, calc[1].begin()+1, meu_functor( subseq_a.data(), subseq_b.data(), sa.data(), sb.data(), char_a.data()));   
     

        //  meu_functor(subseq_a, subseq_b, sa, sb)

    return 0;

}




    //             for(int i=0; i< int(sb_len.size()); i++){
                    
    //                thrust::transform(c0, c1, calc[1].begin()+1, meu_functor(d_S.data, sb[i], calc[0].data()));
    //                thrust::inclusive_scan(calc[1].begin()+1, calc[1].end(), calc[0].begin()+1, thrust::maximum<int>());


// aa
// bbb



// [a, aa]
// [b, bb, bbb]



// [0,0,0,1,1,1]
// [0,1,2]

// [a, aa, aaa]
// [b, bb]

// [a, a,aa, aa, aaa, aaa]
// [b,bb,b,bb,b,bb]
