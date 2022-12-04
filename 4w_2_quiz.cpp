#include <stdlib.h>
#include <stdio.h>
#include <string>
#include<vector>
#include<cmath>
#include<queue>
#include<map>

using namespace std;
struct Node {
    map<string, Node> child;
};

Node root;


void insert(Node& root, vector<string>& v, int idx)
{
    if (idx == v.size())
        return;

    if (!root.child.count(v[idx]))
        root.child[v[idx]] = Node();
    insert(root.child[v[idx]], v, idx + 1);
}

void dfs(Node& root,int dep)
{
    for (auto i : root.child)
    {
        for (int j = 0; j < dep; j++)
            printf("--");
        printf("%s\n", i.first.c_str());
        dfs(i.second, dep + 1);
    }
}



int main() {

    int N;
    char s[100];

    scanf("%d ", &N);
    for (int i = 0; i < N; i++)
    {
        int M;
        scanf("%d ", &M);
        vector<string> v(M);
        for (int i = 0; i < M; i++) {
            scanf("%s", s);
            v[i] = s;
        }
        insert(root, v, 0);
    }

    dfs(root,0);
    
}