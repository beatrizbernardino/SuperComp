#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <random>
using namespace std;

struct tipo_salto{

    int salto;
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
    subseq_b.reserve(M+1);
   
  
    for(int i=0; i<N; i++){

        cin>> a[i];
       
    }for(int i=0; i<M; i++){

        cin>> b[i];
        
    }


    for(int i=0; i< N; i++){
        string s="-";
        for(int j=i; j<N; j++){

            s+=a[j];
            subseq_a.push_back(s);
        }
    }

    int suba_size= subseq_a.size();

    for(int i=0; i< M; i++){
        string s="-";
        for(int j=i; j<M; j++){

            s+=b[j];
            subseq_b.push_back(s);
        }
    }

    int subb_size= subseq_b.size();

    string best_a;
    string best_b;
    int maxScore=0;

    // Gerar todas as combinacoes de subsequencias em um vetor structs(a,b,score)
    // Percorrer com parallel for  e calcular o score
    // Varrer o vetor sem openmp pra pegar o maior score
  
    for(int i=0; i<subb_size; i++){
        for(int j=0; j<suba_size; j++){
            vector<char> sa(subseq_a[j].begin(), subseq_a[j].end());
            vector<char> sb(subseq_b[i].begin(), subseq_b[i].end());
            vector<vector<tipo_salto>> salto(N+1, std::vector<tipo_salto>( M+1 ) );;


            for (int linha=1; linha < int(sa.size()); linha++){
        
                for(int coluna=1; coluna<int(sb.size()); coluna++){
                
                    int score;
                    int diagonal; //0
                    int delecao; //1
                    int insercao; //2
                    score=sa[linha]==sb[coluna]?2:-1;
                    diagonal= H[linha-1][coluna-1]+ score;
                    delecao=H[linha-1][coluna]-1;
                    insercao=H[linha][coluna-1]-1;

                    H[linha][coluna]= std::max({0, diagonal, delecao, insercao});
                    if(H[linha][coluna]==diagonal){
                
                        salto[linha][coluna].salto=0;

                    }
                    else if(H[linha][coluna]==delecao){
                        
                        salto[linha][coluna].salto= 1;

                    }
                    else if(H[linha][coluna]==insercao){
                        
                        salto[linha][coluna].salto= 2;

                    }
                }
            }

        
            for (int i = 0; i < int(sa.size()); i++) {
                for (int j = 0; j <= int(sb.size()); j++) {
                    if (H[i][j] > maxScore) {
                        best_a="";
                        best_b="";
                        maxScore = H[i][j];
                        int l=i;
                        int c=j;
    
                        // while((l!=0 || c!=0) && H[l][c]!=0){


                        //     if(salto[l][c].salto==2){

                        //         best_b+=sb[c];
                        //         best_a+='-';
                        //         c--;


                        //     }else  if(salto[l][c].salto==1){

                        //         best_a+=sa[l];
                        //         best_b+='-';
                        //         l--;

                        //     }else  if(salto[l][c].salto==0){

                        //         best_a+=sa[l];
                        //         best_b+=sb[c];
                        //         l--;
                        //         c--;


                        //     }
                        // }
                    }
                }
            }             
        }    
    }
  
    
    cout<< "MAX SCORE: " << maxScore<<endl;

    // for( int i=int(best_a.size())-1; i>=0; i--){
    //     cout<<best_a[i];
    // }

  
   
    // cout<<endl;
    // for(int i=int(best_b.size())-1; i>=0; i--){
    //     cout<<best_b[i];
    // }
  
    // cout<<endl;
 
            

return 0;
}