#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;

    std::cin >> N;

    std::vector<long long int> arr;

    for(int i = 0; i < N; i++)
    {
        long long int a;
        std::cin >> a;
        arr.push_back(a);
    }

    for(int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";

    }

    std::vector<int> M(N*N);
    for(int i = 0; i < N; i++)
    {
        int remaining = arr[i];
        for(int j = 0; j < N; j++)
        {
            if(M[j + i * N] % 2 == 1) remaining -= 1;
        }
    }
    std::cout << '\n';

    return 0;
}
