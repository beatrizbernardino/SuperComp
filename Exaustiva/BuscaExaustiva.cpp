#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<fstream>
#include<random>
#include <string.h>
#include<omp.h>
using namespace std;

struct result {
    string sa;
    string sb;
    int score;
};

struct salto {
    int movimento;
};

// Function to print all sub strings
vector<string> subString(string str, int n) {
    vector<string> str_combinations; 

    // Pick starting point
    for (int len = 1; len <= n; len++) {
        string substring;

        // Pick ending point
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;           
            for (int k = i; k <= j; k++) {
                substring += str[k];
            }

            str_combinations.push_back(substring);
            substring.clear();
        }
    }

    return str_combinations;
}

int algorithmLocalAlignment(int n, int m, string a, string b,vector<vector<int>> H) {
    // Inicializando lista de movimentos
    salto path;
    path.movimento = 0;
    vector<vector<salto>> saltos(n, vector<salto>(m, path));

    // Adicionando o gap _
    a = "-" + a;
    // cout << a << endl;
    n++;

    b = "-" + b;
    // cout << b << endl;
    m++;
    
    // Matriz H a ser preenchida
    // vector<vector<int>> H(n, vector<int>(m, 0));


    // Inicializar matriz com 0s.
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            H[i][j] = 0;
        }
    }

    // cout << endl;

    int seta = 0;

    int maxValor = 0;
    int maxValor_i = 0;
    int maxValor_j = 0;
    
    // 3. Para cada 1≤i≤n e 1≤j≤m:
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            // Calculando score w
            int w;

            if(a[i] == b[j]) {
                // match
                w = 2;
            } else {
                // mismatch ou gap
                w = -1;
            }

            int diagonal, delecao, insercao;

            // 4. Calcular diagonal
            diagonal = H[i-1][j-1] + w;

            // 5. Calcular deleção
            delecao = H[i-1][j] - 1;

            // 6. Calcular inserção
            insercao = H[i][j-1] - 1;

            // cout << diagonal << " " << delecao << " " << insercao << endl;
            // 7. Calcular H[i,j]=máximo (0, diagonal, deleção, inserção)
            H[i][j] = max({0, diagonal, delecao, insercao});

            // Guardando movimento
            // diag = 3
            // cima = 2
            // esqu = 1
            // nenh = 0

            if(H[i][j] == 0) {
            //    movimentos[i-1][j-1] = 0;
               salto jump;
               jump.movimento = 0;
               saltos[i-1][j-1] = jump;
            } else if(H[i][j] == diagonal) {
                // movimentos[i-1][j-1] = 3;
                salto jump;
                jump.movimento = 3;
                saltos[i-1][j-1] = jump;
            } else if(H[i][j] == delecao) {
                // movimentos[i-1][j-1] = 2;
                salto jump;
                jump.movimento = 2;
                saltos[i-1][j-1] = jump;
            } else if(H[i][j] == insercao) {
                // movimentos[i-1][j-1] = 1;
                salto jump;
                jump.movimento = 1;
                saltos[i-1][j-1] = jump;
            }

            // 8. Retornar o máximo de H[_,_]
            if(H[i][j] > maxValor) {
                maxValor = H[i][j];
                maxValor_i = i;
                maxValor_j = j;
            }

            seta++;
        }
    }

    maxValor_i--;
    maxValor_j--;

    string alignmentSeqA, alignmentSeqB, match;

    // cout << "Movimentos:" << endl;

    while(maxValor_i >= 0 && maxValor_j >= 0) {
        if(saltos[maxValor_i][maxValor_j].movimento == 0) {
            break;
        }
        else if(saltos[maxValor_i][maxValor_j].movimento == 3) {
            maxValor_i--;
            maxValor_j--;

            alignmentSeqA += a[maxValor_i+2];
            alignmentSeqB += b[maxValor_j+2];
            match += "*";

            // cout << "diag" << endl;
        }
        else if(saltos[maxValor_i][maxValor_j].movimento == 1) {
            maxValor_j--;

            alignmentSeqA += "_";
            alignmentSeqB += b[maxValor_j+2];
            match += " ";

            // cout << "esqu" << endl;
        }
        else if(saltos[maxValor_i][maxValor_j].movimento == 2) {
            maxValor_i--;

            alignmentSeqA += a[maxValor_i+2];
            alignmentSeqB += "_";
            match += " ";

            // cout << "cima" << endl;
        }
    }

    result resultado;

    // cout << "Melhor Resultado: " << maxValor << endl;
    resultado.score = maxValor;

    for(int i = alignmentSeqA.size() - 1; i >= 0; i--) {
        // cout << alignmentSeqA[i];
        resultado.sa += alignmentSeqA[i];
    }

    // cout << endl;

    // cout << match << endl;
    
    for(int i = alignmentSeqB.size() - 1; i >= 0; i--) {
        // cout << alignmentSeqB[i];
        resultado.sb += alignmentSeqB[i];
    }

    // cout << endl;

    return resultado.score;
}

int main() {
    // Inicializando as seq. A e B e 
    // seus respectivos tamanhos
    int n, m;
    string a, b;

    cin >> n >> m;
    cin >> a >> b;

    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;

    vector<string> a_combinations = subString(a, a.size());
    vector<string> b_combinations = subString(b, b.size());

    // for(uint i = 0; i < b_combinations.size(); i++) {
    //     cout << b_combinations[i] << endl;
    // }

    result bestResult;
    bestResult.score = 0;

    vector<result> results;


    
    
    for(uint i = 0; i < a_combinations.size(); i++) {
        for(uint j = 0; j < b_combinations.size(); j++) {
            n = a_combinations[i].size();
            m = b_combinations[j].size();

            result resultado;
            resultado.sa = a_combinations[i];
            resultado.sb = b_combinations[j];
            results.push_back(resultado);
            // alignment = algorithmLocalAlignment(n, m, a_combinations[i], b_combinations[j], seed);

            // if(alignment.score > bestResult.score) {
            //     bestResult = alignment;
            // 
        }
    }
    
    #pragma omp parallel for 
    for(uint i = 0; i < results.size(); i++) {

        n = results[i].sa.size();
        m = results[i].sb.size();
        vector<vector<int>> H(n, vector<int>(m, 0));


        int scoreAlignment = algorithmLocalAlignment(n, m, results[i].sa, results[i].sb, H);

        results[i].score = scoreAlignment;
    }

    result maxResult;
    maxResult.score = 0;
    for(auto& el: results) {
        if(el.score > maxResult.score) {
            maxResult = el;
        }
    }

    cout << "Melhor Resultado: " << maxResult.score << endl;

    for(uint i = 0; i < maxResult.sa.size(); i++) {
        cout << maxResult.sa[i];
    }

    cout << endl;

    // cout << match << endl;
    
    for(uint i = 0; i < maxResult.sb.size(); i++) {
        cout << maxResult.sb[i];
    }

    cout << endl;

    return 0;
}