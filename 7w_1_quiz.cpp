#include <stdio.h>
#include <stdlib.h>

int s_lotto[100];
int s_exam[100];
int k = 0;

void dfs(int start, int depth) {
    if (depth == 6) {
        for (int i = 0; i < 6; i++) {
            printf("%d ", s_exam[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i < k; i++) {
        s_exam[depth] = s_lotto[i];
        dfs(i + 1, depth + 1);
    }
}

int main() {
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        scanf("%d", &s_lotto[i]);
    }

    dfs(0, 0);
    printf("\n");

    return 0;
}