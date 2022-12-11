#include <stdlib.h>
#include <stdio.h>
#include <string>
#include<vector>
#include<cmath>
#include<queue>
#include<map>

using namespace std;

int main() {

    int N;
    int maxNum;
    char s[100];

    scanf("%d ", &N);
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        int slen = 0;

        scanf("%s", s);
        std::string S(s);

        slen = S.length();
        slen -= 2;

        for (int i = 0; i < slen; i++) {
            if (S.substr(i, 3) == "for") {
                cnt++;
            }
        }

        slen -= 2;
        for (int i = 0; i < slen; i++) {
            if (S.substr(i, 5) == "while") {
                cnt++;
            }
        }

        maxNum = max(maxNum, cnt);
    }

    printf("Max:%d\n", maxNum);
    
}