#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>
#include <string>

using namespace std;




int main()
{
    default_random_engine generator;
   
    int N, M;
    cin >> N;
    cin >> M;
   
    vector<char> a;
    vector<char> b;
    vector<char> seq_a;
    vector<char> seq_b;
   
    a.reserve(N+1);
    b.reserve(M+1);
    seq_a.reserve(M+1);
    seq_b.reserve(M+1);
 
    for(int l=0; l<N; l++){

        cin>> a[l];
        
    }
    for(int l=0; l<M; l++){

        cin>> b[l];
            
    }



    for(int v=0; v<100; v++){

        int k=0;

        if(M>N){

            uniform_int_distribution<int> distribution_k(3, N);
            k = distribution_k(generator); // gera número

        }else{

            uniform_int_distribution<int> distribution_k(3, M);
            k = distribution_k(generator); 
        }

        
        
        uniform_int_distribution<int> distribution_p(2, N);
        uniform_int_distribution<int> distribution_j(0, M-k);
        uniform_int_distribution<int> distribution_i(0, N-k);


        
        int p = distribution_p(generator);
        int j = distribution_j(generator);
       
        vector<char> sb;
        vector<char> best_a;

        sb.reserve(N);
        sb[0]='-';
        best_a.reserve(k); 


        int inicio_b=1;
        int fim_b= j+k+1;

        for(int v=j; v<fim_b; v++){

            sb[inicio_b]=b[v];  
            inicio_b++;
        }
             

        int max_score=0;

        for( int l=0; l<p; l++){

            vector<char> sa;
            sa.reserve(N);
            sa[0]='-';

            vector<vector<int>> H(k+1, vector<int>(k+1,0));

            int total_score=0;
            int i=distribution_i(generator);
            int inicio_a=1;
            int fim_a=i+k+1;
           
        

            for( int g=i; g<fim_a; g++){

                sa[inicio_a]=a[g];
                inicio_a++;
            }

            for (int linha=1; linha <= k; linha++){
        
                for(int coluna=1; coluna<=k; coluna++){
                
                    int score;
                    int diagonal;
                    int delecao;
                    int insercao;
                    score= sa[linha]==sb[coluna]? 2:-1;
                    diagonal= H[linha-1][coluna-1]+ score;
                    delecao=H[linha-1][coluna]-1;
                    insercao=H[linha][coluna-1]-1;

                    H[linha][coluna]= std::max({0, diagonal, delecao, insercao});
                
                    
                }
            }
            
   
            for (int i = 0; i <= k; i++) {
                for (int j = 0; j <= k; j++) {
                    if (H[i][j] > total_score) {
                        total_score = H[i][j];
                       
                    }
                }
            }
            // cout<< total_score;

            // cout<<endl<<"-------" << endl;

          

            if (total_score>max_score){

                max_score=total_score;

                for(int o=0; o<k; o++){
                    best_a[o]=sa[o+1];
        
                }
           
            }
          
        }


        cout<<"MAXSCORE: "<<max_score<< endl<<endl;


       cout << "SEQB: ";

        for( int i=1; i<=k; i++){
            cout<<sb[i];
        }

        cout<<endl;
        cout << "SEQA: ";

        for(int i=0; i<k; i++){
            cout<<best_a[i];
        }
        cout<<endl<<endl;
        cout<<"------------";
        cout<<endl<<endl;
    }


   return 0;
}