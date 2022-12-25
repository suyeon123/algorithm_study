#include <stdio.h>
 
int max(int a, int b) {
	if (b > a) {
		return b;
	} else {
		return a;
	}
}

int main() {
	int n = 0;
	int stair[301] = {0,};
	int dp[301] = {0, };

    scanf("%d ", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d ", &stair[i]);
    }
 
    dp[0] = stair[0];
    dp[1] = max(stair[0] + stair[1], stair[1]);
    dp[2] = max(stair[0] + stair[2], stair[1] + stair[2]);
 
    for (int i = 3; i < n; i++) {
        dp[i] = max(dp[i -2] + stair[i], stair[i - 1] + stair[i] + dp[i - 3]);
    }
 
    printf("res:%d\n", dp[n - 1]);
 
    return 0;
}
