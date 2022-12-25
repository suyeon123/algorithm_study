#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//갈 수 있는 주유소 정렬
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.second > b.second) return true;
    if (a.second == b.second) 
        return a.first > b.first;
    return false;
}

int main() {
    int n; // 주유소 갯수
    int l; // 거리
    int p; // 연료양
    int station[1000000] = {0 };
    int cnt = 0;

    scanf("%d ", &n);

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d  %d", &a, &b);
        station[a] = b;
    }

    scanf("%d  %d", &l, &p);

    int cur = 0;

    while (true) {
        if (cur + p >= l) {
            break;
        }

        vector<pair<int, int>> possibleStation;
        for (int i = cur + 1; i <= cur + p; ++i) {
            if (station[i] != 0)
                possibleStation.push_back(make_pair(i, station[i]));
        }

        if (possibleStation.empty()) {
            break;
        }

        sort(possibleStation.begin(), possibleStation.end(), cmp);
        
        p = p - (possibleStation[0].first - cur) + possibleStation[0].second;
        cur = possibleStation[0].first;
        cnt++;
    }

    printf("res:%d\n", cnt);

    return 0;
}