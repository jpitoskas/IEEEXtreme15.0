#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    int testcases;
    std::cin >> testcases;

    for(int t = 0; t < testcases; t++)
    {
        int N, M;
        std::cin >> N >> M;

        std::vector<int> topics_frequency;
        for(int n = 0; n < N; n++)
        {
            topics_frequency.push_back(0);
            for(int m = 0; m < M; m++)
            {
                char special;
                std::cin >> special;

                if(special == 'y')
                    topics_frequency[n] |= 1 << (M - m - 1);
            }
        }

        // for(int n = 0; n < N; n++)
        // {
        //     std::cout << topics_frequency[n] << '\n';
        // }

        int sum = 0;
        int final = 0;
        int ka = (1 << M) - 1;
        for(int i = 0; i < N; i++)
        {
            for(int j = i + 1; j < N; j++)
            {
                int partial =  (ka - topics_frequency[i]) & (ka - topics_frequency[j]);
                if(partial == 0)
                {
                    final += N - j - 1;
                    continue;
                }
                for(int k = j + 1; k < N; k++)
                {
                    sum = partial & (ka - topics_frequency[k]);
                    if(sum == 0) final++;
                }
            }
        }
        // std::unordered_map<int, int> bit_frequency;
        // std::unordered_map<int, std::vector<std::pair<int, int>>> f;
        // for(int i = 0; i < N; i++)
        // {
        //     for(int j = i + 1; j < N; j++)
        //     {
        //         ++bit_frequency[(ka - topics_frequency[i]) & (ka - topics_frequency[j])];
        //         f[(ka - topics_frequency[i]) & (ka - topics_frequency[j])].push_back({i, j});
        //     }
        // }

        // for(auto t : bit_frequency)
        // {
        //     for(int l = 0; l < N; l++)
        //     {
        //         bool cont = false;
        //         for(auto p : f[t.first])
        //         {
        //             if(p.first == l || p.second == l)
        //             {
        //                 cont = true;
        //                 break;
        //             }
        //         }
        //         if(cont) continue;
        //         if((t.first & (ka - topics_frequency[l])) == 0)
        //             final += t.second;
        //     }
        // }
        // std::vector<int> freq(ka + 1, 0);
        // for(int i = 0; i < N; i++)
        // {
        //     for(int j = i + 1; j < N; j++)
        //         ++freq[(ka - topics_frequency[i]) & (ka - topics_frequency[j])];
        // }

        // for(int k = 0; k < N; k++)
        // {
        //     for(int j = 0; j < ka; j++)
        //     {
        //         if(((ka - topics_frequency[k]) & j) == 0)
        //         {
        //             final += freq[j];
        //         }
        //     }
        // }

        // To store values that are present
        // unordered_set<int> s;
        // for (int i = 0; i < N; i++)
        //     s.insert(ka - topics_frequency[i]);

        // // stores the count of unique triplets
        // int count = 0;

        // // traverse for all i, j pairs such that j>i
        // for (int i = 0; i < N-1; i++) {
        //     for (int j = i + 1; j < N; j++) {

        //     // xor of a[i] and a[j]
        //     int xr = (ka - topics_frequency[i]) & (ka - topics_frequency[j]);

        //     // if xr of two numbers is present,
        //     // then increase the count
        //     if (s.find(xr)  && xr != (ka - topics_frequency[i]) &&
        //                               xr != (ka - topics_frequency[j]))
        //     count++;
        // }

        std::cout << final << '\n';
    }
}
