#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <random>
using namespace std;


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

    int max_score=0;
    string best_a="";
    string best_b="";


    for(int i=0; i<subb_size; i++){
        for(int j=0; j<suba_size; j++){

            int score=0;
            vector<char> sa(subseq_a[j].begin(), subseq_a[j].end());
            vector<char> sb(subseq_b[i].begin(), subseq_b[i].end());

            if(sa.size()< sb.size()){
                sb.resize(sa.size());

            }
            else if (sb.size()< sa.size()){
                sa.resize(sb.size());
            }

            for(int i=0; i<int(sa.size()); i++){
                score+= (sa[i] == sb[i] ? 2:-1);
           
            }

            if(score>=max_score ){
                
                max_score=score;
                best_a="";
                best_b="";

                for(int h=0; h<int(sa.size()); h++){
                    best_a+=sa[h];
                    best_b+=sb[h];
                }
                
            }           
            
        }
    }


    cout<< "MAX SCORE: " << max_score<<endl;
    // cout<< best_a<<endl;
    // cout<< best_b<<endl;

   

return 0;

}