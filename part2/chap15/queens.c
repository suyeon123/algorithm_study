#include <stdio.h>
#include <stdlib.h>

void printSolution(int columns[], int numberOfQueens);
int  isThreatened (int columns[], int newRow);
void findSolutionForQueen(int columns[], int row, int numberOfQueens, int *solutionCount);

void findSolutionForQueen(int columns[], int row, int numberOfQueens, int *solutionCount) {
    if (isThreatened(columns, row)) {
        return;
    }
    
    if (row == numberOfQueens - 1) {
        printf("Solution #%d : \n", ++(*solutionCount));
        printSolution(columns, numberOfQueens);
    } else {
        for (int i = 0; i < numberOfQueens; i++) {
            columns[row + 1] = i;
            findSolutionForQueen (columns, row + 1, numberOfQueens, solutionCount);
        }
    }
}

int isThreatened(int columns[], int newRow) {
    int currentRow = 0;
    int threatened = 0;

    while (currentRow < newRow ) { 
        if (columns[newRow] == columns[currentRow]
             || abs (columns[newRow] - columns[currentRow]) 
               == abs(newRow - currentRow)) {
            threatened = 1;
            break;
        }
       currentRow++;
    }

    return threatened;
}

void printSolution(int columns[], int numberOfQueens) {
    for (int i=0; i < numberOfQueens; i++) {
        for (int j=0; j < numberOfQueens; j++) {
            if (columns[i] == j)
                printf("Q");
            else
                printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* argv[]) 
{
    int numberOfQueens = 0; 
    int solutionCount  = 0;
    int *columns;

    if (argc < 2) {
        printf("Usage: %s <Number Of Queens>", argv[0]);
        return 1;
    }
    
    numberOfQueens = atoi(argv[1]); 
    columns = (int*)calloc(numberOfQueens, sizeof(int));
        
    for (int i = 0; i < numberOfQueens; i++) {
        columns[0] = i;
        findSolutionForQueen(columns, 0, numberOfQueens, &solutionCount);
    }    
    free (columns);

    return 0;
}