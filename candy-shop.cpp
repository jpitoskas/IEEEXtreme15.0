#include <iostream>
#include <vector>



int ind(int i, int j, int K)
{
    return j + i * (K + 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, K;
    std::cin >> N >> K;
    std::vector<int> dp((N + 1) * (K + 1), 0);
    std::vector<int> A;
    std::vector<int> B;
    A.reserve(100001);
    B.reserve(100001);
    for(int i = 0; i < N; i++){
        int a, b;
        std::cin >> a >> b;
        A.push_back(a);
        B.push_back(b);
    }

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < K + 1; j++)
        {
            int sum = 0;
            for (unsigned int k = 1; k <= A[i-1]; k++) {
                long int temp = k * B[i - 1];
                if (temp< j)
                    sum = (sum + (dp[ind(i - 1, j - temp, K)])%998244353)%998244353;
                else if (temp == j)
                    sum += (1)%998244353;

            }
            dp[ind(i, j, K)] = (dp[ind(i - 1, j, K)] + sum)%998244353;
        }
    }

    std::cout << dp[ind(N, K, K)];

}
