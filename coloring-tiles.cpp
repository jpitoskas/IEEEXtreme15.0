#include <iostream>

using namespace std;

int main() {
    int T;
    std::cin >> T;

    for(int t = 0; t < T; t++)
    {
        int N, M, C;
        std::cin >> N >> M >> C;

        std::vector<char> image;
        image.reserve(N * M)
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                char c;
                std::cin >> c;
                image.push_back(c);
            }
        }

        std::vector<int> f;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                f[j + i * M]
            }
        }
    }

    return 0;
}
