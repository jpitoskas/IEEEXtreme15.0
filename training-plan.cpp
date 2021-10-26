#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int t,M,X,Y,K;
  cin >> t;
  for (int q=0; q<t; q++){
      cin >> M >> X >> Y >> K;
      int days[100][100];
      for (int m=0; m<M; m++){
        for (int x=0; x<X; x++)
          cin >> days[m][x];
      }

      int dp[101][101][101][20];
      for (int m=0; m<=M; m++){
          for (int x=0; x<=X; x++){
              for (int y=0; y<=Y; y++){
                  for (int k=0; k<=K; k++){
                      dp[m][x][y][k] = 0;
                  }
              }
          }
      }

      for (int m=1; m<=M; m++){
          for (int x=1; x<=X; x++){
              for (int y=1; y<=x; y++){
                  for (int k=1; k<=K; k++){
                      dp[m][x][y][k] =  max(dp[m][x-1][y-1][k-1]+days[m-1][x-1], dp[m][x-1][y][k]);
                      cout << "x = " <<x <<", y = " <<y<<", k = " << k << ", res = "<<dp[m][x][y][k] <<endl;
                  }
              }
          }
      }


      cout << (dp[M][X][Y][K]);
      cout <<endl;
      cout <<endl;
      cout << dp[1][1][1][1]<<endl;
      cout << days[0][0]+dp[1][1][0][0];
      cout <<dp[1][1][0][1]<<endl;

  }



  return 0;
}
