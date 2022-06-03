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


struct subs{

    int idx_seq;
    int tam_seq;
};


struct calc_b
{
    thrust::device_ptr<subs> index_seqb;
    thrust::device_ptr<char> sequencias_b;
    thrust::device_ptr<char> a;
    
    calc_b(thrust::device_ptr<subs> index_seqb_,  thrust::device_ptr<char> sequencias_b_,thrust::device_ptr<char> a_ ): 
    index_seqb(index_seqb_), sequencias_b(sequencias_b_), a(a_) {};

    __host__ __device__
    int operator()(const int& x) {

        return 2;
    }
};

struct meu_functor
{

    
    thrust::device_ptr<subs> index_seqa;
    thrust::device_ptr<subs> index_seqb;
    thrust::device_ptr<char> sequencias_a;
    thrust::device_ptr<char> sequencias_b;
    int size_b;


    meu_functor(thrust::device_ptr<subs> index_seqa_,thrust::device_ptr<subs> index_seqb_, thrust::device_ptr<char> sequencias_a_, thrust::device_ptr<char> sequencias_b_, int size_b_): 
    index_seqa(index_seqa_),index_seqb(index_seqb_), sequencias_a(sequencias_a_) ,sequencias_b(sequencias_b_), size_b(size_b_) {};
    __host__ __device__
    int operator()(const int& x) {

        thrust::device_ptr<char> a;
        subs seqa_info= index_seqa[x];

        int w=0;
        for(int i = seqa_info.idx_seq; i< (seqa_info.idx_seq+ seqa_info.tam_seq); i++){

            a[w]=sequencias_a[i];
            w++;

        }

        for(int i = 0; i< size_b; i++){

            thrust::device_ptr<char> b;
            subs seqa_info= index_seqb[i];

            for(int k = seqb_info.idx_seq; k< (seqb_info.idx_seq+ seqb_info.tam_seq); k++){

                sequencias_b[i];
                

            }

        }


        

        // thrust::counting_iterator<int> c0(0);
        // thrust::counting_iterator<int> c1(size_b);
        // thrust::device_ptr<int> scores;

    
        // thrust::transform(thrust::device, c0, c1, scores, calc_b(index_seqb, a, sequencias_b));



        return 0;
        
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

    thrust::device_vector<char> sequencias_a;
    thrust::device_vector<char> sequencias_b;

    thrust::device_vector<subs> index_seqa;
    thrust::device_vector<subs> index_seqb;


    int idx=0;
    for( int i=0; i <int(subseq_a.size()); i++){

            subs seqa;

            for(int c=0; c<int(subseq_a[i].size()); c++){

                sequencias_a.push_back(subseq_a[i][c]);


            }

            seqa.idx_seq=idx;
            seqa.tam_seq=(int(subseq_a[i].size()));
            index_seqa.push_back(seqa);
            idx+=int(subseq_a[i].size());
    }

    idx=0;
    for( int i=0; i <int(subseq_b.size()); i++){

            subs seqb;

            for(int c=0; c<int(subseq_b[i].size()); c++){

                sequencias_b.push_back(subseq_b[i][c]);

            }

            seqb.idx_seq=idx;
            seqb.tam_seq=(int(subseq_b[i].size()));
            idx+=subseq_b[i].size();
            index_seqb.push_back(seqb);
    }

    // for(int h=0; h<int(index_seqa.size() ); h++){
    //     subs seq;
    //     seq=index_seqa[h];
    //     cout<<seq.idx_seq<<endl;
    // }

    thrust::counting_iterator<int> c0(1);
    thrust::counting_iterator<int> c1(int(index_seqa.size()+1));
    thrust::device_vector<int> max_scores(int(index_seqa.size()) *int(index_seqb.size()) );

    int size_b=  int(index_seqb.size());



    thrust::transform(c0, c1, max_scores.begin()+1, meu_functor( index_seqa.data(),index_seqb.data(), sequencias_a.data(), sequencias_b.data(), size_b));
    

    // for (int g=0; g< int(max_scores.size()); g++){
    //     cout<<max_scores[g]<<endl;
    // }
    // int  best_score= thrust::reduce(max_scores.begin(), max_scores.end(), 0, thrust::maximum<int>());

    // cout<<best_score<<endl;


// [T,T,G,T,G,C,G,G,C,C]
// [T,T,G,T,G,C,G,G,C,C]



    




        
    return 0;

}


