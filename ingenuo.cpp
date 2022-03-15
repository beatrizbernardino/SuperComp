#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;


int w(char a, char b){
    if (a==b){
        return 2;
    }else {
        return -1;
    }


}

struct tipo_salto{

    string salto;
};

int main()
{
    // int max_score;
    int N, M;
    cin >> N;
    cin >> M;

    std::vector<char> a;
    std::vector<char> b;
    std::vector<char> seq_a;
    std::vector<char> seq_b;
    vector<vector<int>> H(N+1, vector<int>(M+1,0));
    vector<vector<tipo_salto>> salto(N+1, std::vector<tipo_salto>( M+1 ) );;
    salto.reserve(N*M);
    a.reserve(N+1);
    b.reserve(M+1);
    seq_a.reserve(N+1);
    seq_b.reserve(M+1);

    a[0]='-';
    b[0]='-';
    // max_score=0;


    // M= coluna
    // N= linha

    
    for(int i=1; i<=N; i++){

        cin>> a[i];
    }for(int i=1; i<=M; i++){

        cin>> b[i];
    }

    for (int linha=1; linha <= N; linha++){
        
        for(int coluna=1; coluna<=M; coluna++){
         
            int score;
            int diagonal;
            int delecao;
            int insercao;
            score=w(a[linha],b[coluna]);
            diagonal= H[linha-1][coluna-1]+ score;
            delecao=H[linha-1][coluna]-1;
            insercao=H[linha][coluna-1]-1;

            H[linha][coluna]= std::max({0, diagonal, delecao, insercao});
           
            if(H[linha][coluna]==diagonal){
                
                

                salto[linha][coluna].salto="diagonal";

            }
            else if(H[linha][coluna]==delecao){
                
                salto[linha][coluna].salto= "delecao";

            }
            else if(H[linha][coluna]==insercao){
                
                salto[linha][coluna].salto= "insercao";

            }
        }

       
         
    }

    int maxlinha = std::max_element(H.begin(),H.end()) - H.begin();
    int maxcoluna= std::max_element(H[maxlinha].begin(),H[maxlinha].end()) - H[maxlinha].begin();
   
    // max_score=H[maxlinha][maxcoluna]; 


    int i=maxlinha;
    int j=maxcoluna;
    int ordem=0;
    while(i!=0 && j!=0 && H[i][j]!=0){

        if(salto[i][j].salto=="insercao"){

            seq_b[ordem]=b[j];
            seq_a[ordem]='_';
            j--;


        }else  if(salto[i][j].salto=="delecao"){

            seq_a[ordem]=a[i];
            seq_b[ordem]='_';
            i--;

        }else  if(salto[i][j].salto=="diagonal"){

            seq_a[ordem]=a[i];
            seq_b[ordem]=b[j];
            i--;
            j--;


        }
       
        ordem++;
        
    }





    
    // for (int linha=0; linha <= N; linha++){
        
    //     for(int coluna=0; coluna<=M; coluna++){

            
    //         cout<< H[linha][coluna] << " ";
    //     };
    //     cout<<endl;
        
    // };

    std::reverse(seq_b.begin(), seq_b.end());
    std::reverse(seq_a.begin(), seq_a.end());
    for(int i=M; i>=0; i--){
        cout<<seq_b[i];
    }
   
    cout<<endl;
    for(int i=N; i>=0; i--){
        cout<<seq_a[i];
    }
    cout<<endl;

    


   return 0;
}