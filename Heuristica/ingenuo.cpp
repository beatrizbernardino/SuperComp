#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include <string>

using namespace std;




struct tipo_salto{

    int salto;
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
    seq_a.reserve(M+1);
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


    // seq_a=a;
    // seq_b=b;
    
   
    

    for (int linha=1; linha <= N; linha++){
        
        for(int coluna=1; coluna<=M; coluna++){
         
            int score;
            int diagonal;
            int delecao;
            int insercao;
            score=(a[linha]==b[coluna]?2:-1);
            diagonal= H[linha-1][coluna-1]+ score;
            delecao=H[linha-1][coluna]-1;
            insercao=H[linha][coluna-1]-1;

            H[linha][coluna]= std::max({0, diagonal, delecao, insercao});
           
            if(H[linha][coluna]==diagonal){
                
                

                salto[linha][coluna].salto=0;

            }
            else if(H[linha][coluna]==delecao){
                
                salto[linha][coluna].salto=1;

            }
            else if(H[linha][coluna]==insercao){
                
                salto[linha][coluna].salto= 2;

            }
        }

       
         
    }

    int maxScore=0;
    int maxlinha = 0;
    int maxcoluna= 0;
   
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (H[i][j] > maxScore) {
                maxScore = H[i][j];
                maxlinha=i;
                maxcoluna=j;
            }
        }
    }

    


    int i=maxlinha;
    int j=maxcoluna;
    int ordem=0;

    
    while((i!=0 || j!=0) && H[i][j]!=0){


        if(salto[i][j].salto==2){

            seq_b[ordem]=b[j];
            seq_a[ordem]='-';
            j--;


        }else  if(salto[i][j].salto==1){

            seq_a[ordem]=a[i];
            seq_b[ordem]='-';
            i--;

        }else  if(salto[i][j].salto==0){

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
   
    // for(int i=0; i<=M; i++){
       
    //     cout<<seq_b[i];
      
    // }


    cout<<"MAXSCORE: "<<maxScore<<endl;

   for( int i=ordem-1; i>=0; i--){
        cout<<seq_b[i];
    }

  
   
    cout<<endl;
    for(int i=ordem-1; i>=0; i--){
        cout<<seq_a[i];
    }
  
    cout<<endl;

    


   return 0;
}