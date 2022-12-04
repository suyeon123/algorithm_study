#include <stdio.h>
#include <queue>

#define SIZE 100000
using namespace std;
 
bool visit[SIZE + 1];
 
int main() {
    int N = 5;
    int K = 17;
 
    queue<pair<int, int>> q;
    q.push(make_pair(0, N));
    visit[N] = true;
 
    int result = 0;
    while (1) {
        int cnt = q.front().first;
        int place = q.front().second;
 
        if (place == K) {
            result = cnt;
            break;
        }
 
        if (place - 1 >= 0 && !visit[place - 1]) {
            q.push(make_pair(cnt + 1, place - 1));
            visit[place - 1] = true;
        }
        if (place + 1 <= SIZE && !visit[place + 1]) {
            q.push(make_pair(cnt + 1, place + 1));
            visit[place + 1] = true;
        }
        if (place * 2 <= SIZE && !visit[place * 2]) {
            q.push(make_pair(cnt + 1, place * 2));
            visit[place * 2] = true;
        }
 
        q.pop();
    }
    printf("%d\n", result);
    return 0;
}
