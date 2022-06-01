#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <omp.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/copy.h>
#include <cstring>
using namespace std;

struct tipo_salto{

    int salto;
};


struct seq{

    string sub_a;
    string sub_b;
    int score;

};



int main(){

    int N, M;
    cin >> N;
    cin >> M;

    vector<char> a;
    vector<char> b;
 
    vector<vector<char>> subseq_a;
    vector<vector<char>> subseq_b;
 
  
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
        string s="-";
        vector<char> w;
        for(int j=i; j<N; j++){

            s+=a[j];
            w.push_back(a[j]);
            
            // subseq_a.push_back(s);
        }
        subseq_a.push_back(w);
    }

    int suba_size= subseq_a.size();

    for(int i=0; i< M; i++){
        string s="-";
        vector<char> w;
        for(int j=i; j<M; j++){

            s+=b[j];
            // subseq_b.push_back(s);
        }
        subseq_b.push_back(w);

    }

    int subb_size= subseq_b.size();

    thrust::device_vector<vector<char>> sub_a(suba_size); 
    thrust::device_vector<vector<char>> sub_b(subb_size); 
    thrust::device_vector<seq> comb(subb_size* suba_size); 


    thrust::fill(subseq_a.begin(), subseq_a.end(), sub_a.begin()); 
    thrust::fill(subseq_b.begin(), subseq_b.end(), sub_b.begin()); 





    return 0;
}

// int main()
// {
//     int N, M;
//     cin >> N;
//     cin >> M;

//     vector<char> a;
//     vector<char> b;
 
//     vector<string>subseq_a;
//     vector<string>subseq_b;

//     vector<seq> combinacoes;
//     vector<vector<int>> H(N+1, vector<int>(M+1,0));


    
  
//     a.reserve(N+1);
//     b.reserve(M+1);
//     subseq_a.reserve(N+1);
//     subseq_b.reserve(M+1);
   
  
//     for(int i=0; i<N; i++){

//         cin>> a[i];
       
//     }for(int i=0; i<M; i++){

//         cin>> b[i];
        
//     }


//     for(int i=0; i< N; i++){
//         string s="-";
//         for(int j=i; j<N; j++){

//             s+=a[j];
//             subseq_a.push_back(s);
//         }
//     }

//     int suba_size= subseq_a.size();

//     for(int i=0; i< M; i++){
//         string s="-";
//         for(int j=i; j<M; j++){

//             s+=b[j];
//             subseq_b.push_back(s);
//         }
//     }

//     int subb_size= subseq_b.size();

//     string best_a;
//     string best_b;
//     int max_Score=0;

//     // Gerar todas as combinacoes de subsequencias em um vetor structs(a,b,score) 
//     // Percorrer com parallel for  e calcular o score
//     // Varrer o vetor sem openmp pra pegar o maior score
  
//     for(int i=0; i<subb_size; i++){
//         for(int j=0; j<suba_size; j++){

//             vector<char> sa(subseq_a[j].begin(), subseq_a[j].end());
//             vector<char> sb(subseq_b[i].begin(), subseq_b[i].end());
//             seq subs;
//             subs.sub_a= sa;
//             subs.sub_b=sb;
//             subs.score=0;

//             combinacoes.push_back(subs);
           
//         }    
//     }

//     int maxScore=0;
  
//     #pragma omp parallel for  firstprivate(H)
//     for( int i=0; i< int(combinacoes.size()); i++){

//         for (int linha=1; linha < int(combinacoes[i].sub_a.size()); linha++){
        
//                 for(int coluna=1; coluna<int(combinacoes[i].sub_b.size()); coluna++){
                
//                     int score;
//                     int diagonal; //0
//                     int delecao; //1
//                     int insercao; //2
//                     score=(combinacoes[i].sub_a[linha]==combinacoes[i].sub_b[coluna])?2:-1;
//                     diagonal= H[linha-1][coluna-1]+ score;
//                     delecao=H[linha-1][coluna]-1;
//                     insercao=H[linha][coluna-1]-1;

//                     H[linha][coluna]= std::max({0, diagonal, delecao, insercao});

//                 }
            


//         }
        

//         for (int b = 0; b < int(combinacoes[i].sub_a.size()); b++) {
//             for (int n = 0; n < int(combinacoes[i].sub_b.size()); n++) {       
//                 if (H[b][n] > maxScore) {
//                     maxScore=H[b][n];
//                 }
//             }
//         }

//         combinacoes[i].score=maxScore;
//     }

//     for(int i=0; i<int(combinacoes.size()); i++){

      
//         if(combinacoes[i].score> max_Score){
//             max_Score=combinacoes[i].score;
//             // best_a="";
//             // best_b="";

//             // for(int j=0; j< int(combinacoes[i].sub_a.size()); j++){

//             //     best_a+=combinacoes[i].sub_a[j];

//             // }
//             // for(int j=0; j< int(combinacoes[i].sub_b.size()); j++){

//             //     best_b+=combinacoes[i].sub_b[j];

//             // }

            

//         }
//     }


//     cout<<best_a<< endl;
//     cout<< best_b<<endl;
//     cout<< max_Score<<endl;


    
        
    
  
 
            

// return 0;
// }