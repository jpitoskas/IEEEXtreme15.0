#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> first_group;
    for(int i = 0; i < N; i++)
    {
        int x, y;
        std::cin >> x >> y;
        first_group.push_back({x, y});
    }

    std::vector<std::pair<int, int>> second_group;
    for(int i = 0; i < N; i++)
    {
        int x, y;
        std::cin >> x >> y;
        second_group.push_back({x, y});
    }

    std::vector<std::pair<int, int>> third_group;
    for(int i = 0; i < N; i++)
    {
        int x, y;
        std::cin >> x >> y;
        third_group.push_back({x, y});
    }

    for(int i = 0; i < N; i++)
    {
                    int i1 = 0;
                    int i2 = 0;
                    int i3 = 0;
        for(int t1 = 0; t1 < N; t1++)
        {
            for(int t2 = 0; t2 < N; t2++)
            {
                for(int t3 = 0; t3 < N; t3++)
                {
                    int dx1 = std::abs(second_group[t2].first - first_group[t1].first);
                    int dy1 = std::abs(second_group[t2].second - first_group[t1].second);
                    int dx2 = std::abs(second_group[t2].first - third_group[t3].first);
                    int dy2 = std::abs(second_group[t2].second - third_group[t3].second);
                    if(dx1 * dy1 < dx2 * dy2)
                    {
                        i1 = t1;
                        i2 = t2;
                        i3 = rand() % N;
                    }
                    else
                    {
                        i1 = rand() % N;
                        i2 = t2;
                        i3 = t3;
                    }
                }
            }
        }
        std::cout << i1 << " " << i2 << " " << i3 << '\n';
        if(i1 + i < N) std::cout << i1 + i << " ";
        if(i2 + i < N) std::cout << i2 + i << " ";
        if(i3 + i < N) std::cout << i3 + i << '\n';
    }


}
