#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef std::vector<std::vector<int> > matriz;

int main()
{
    int N, M;
    string seq_um;
    string seq_dois;
    cin >> N;
    cin >> M;

    std::vector<char> a(seq_um.begin(), seq_um.end());
    std::vector<char> b(seq_dois.begin(), seq_dois.end());
    a.reserve(N);
    b.reserve(M);
    matriz H;

    cout << N << endl;
    cout << M << endl;

    return 0;
}