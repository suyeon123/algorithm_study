#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

#define MAX_WEIGHT 36267

enum VisitMode { Visited, NotVisited };
typedef int ElementType;

typedef struct tagDisjointSet
{
    struct tagDisjointSet* Parent;
    void*                  Data;
} DisjointSet;

typedef struct tagVertex
{
    ElementType       Data;
    int               Visited;
    int               Index;

    struct tagVertex* Next;
    struct tagEdge*   AdjacencyList;
} Vertex;

typedef struct tagEdge
{
    int    Weight;
    struct tagEdge* Next;
    Vertex* From;
    Vertex* Target;
} Edge;

typedef struct tagGraph
{
    Vertex* Vertices;
    int     VertexCount;
} Graph;

void Prim(Graph* G, Vertex* StartVertex, Graph* MST );
void Kruskal(Graph* G, Graph* MST );

void DS_UnionSet( DisjointSet* Set1, DisjointSet* Set2 );
DisjointSet* DS_FindSet( DisjointSet* Set );
DisjointSet* DS_MakeSet( void* NewData );
void DS_DestroySet( DisjointSet* Set );

Graph* CreateGraph();
void   DestroyGraph( Graph* G );

Vertex* CreateVertex( ElementType Data );
void    DestroyVertex( Vertex* V );

Edge*   CreateEdge( Vertex* From, Vertex* Target, int Weight );
void    DestroyEdge( Edge* E );

void   AddVertex( Graph* G, Vertex* V );
void   AddEdge( Vertex* V, Edge* E );
void   PrintGraph ( Graph* G );

void DS_UnionSet( DisjointSet* Set1, DisjointSet* Set2 )
{
    Set2 = DS_FindSet(Set2);

    Set2->Parent = Set1;
}

DisjointSet* DS_FindSet( DisjointSet* Set )
{
    while ( Set->Parent != NULL )
    {
        Set = Set->Parent;
    }

    return Set;
}

DisjointSet* DS_MakeSet( void* NewData )
{
    DisjointSet* NewNode = (DisjointSet*)malloc(sizeof(DisjointSet));
    NewNode->Data   = NewData;
    NewNode->Parent = NULL;

    return NewNode;
}

void DS_DestroySet( DisjointSet* Set )
{
    free( Set );
}


void Prim(Graph* G, Vertex* StartVertex, Graph* MST )
{
    int i = 0;

    PQNode         StartNode = { 0, StartVertex };
    PriorityQueue* PQ        = PQ_Create(10);

    Vertex*  CurrentVertex = NULL;
    Edge*    CurrentEdge   = NULL; 

    int*     Weights       = (int*) malloc( sizeof(int) * G->VertexCount );
    Vertex** MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Fringes       = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Precedences   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );

    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, NewVertex);

        Fringes[i]     = NULL;
        Precedences[i] = NULL;
        MSTVertices[i] = NewVertex;        
        Weights[i]     = MAX_WEIGHT;        
        CurrentVertex  = CurrentVertex->Next;
        i++;
    }

    PQ_Enqueue ( PQ, StartNode );

    Weights[StartVertex->Index] = 0;
    
    while( ! PQ_IsEmpty( PQ ) )
    {
        PQNode  Popped;
        
        PQ_Dequeue(PQ, &Popped);
        CurrentVertex = (Vertex*)Popped.Data;
        
        Fringes[CurrentVertex->Index] = CurrentVertex;

        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {            
            Vertex* TargetVertex = CurrentEdge->Target;

            if ( Fringes[TargetVertex->Index] == NULL &&
                 CurrentEdge->Weight < Weights[TargetVertex->Index] )
            {
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                PQ_Enqueue ( PQ, NewNode );

                Precedences[TargetVertex->Index] = CurrentEdge->From;
                Weights[TargetVertex->Index]     = CurrentEdge->Weight;                
            }
            
            CurrentEdge = CurrentEdge->Next;
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
    {
        int FromIndex, ToIndex;

        if ( Precedences[i] == NULL )
            continue;

        FromIndex = Precedences[i]->Index;
        ToIndex   = i;

        AddEdge( MSTVertices[FromIndex], 
            CreateEdge( MSTVertices[FromIndex], MSTVertices[ToIndex],   Weights[i] ) );

        AddEdge( MSTVertices[ToIndex],   
            CreateEdge( MSTVertices[ToIndex],   MSTVertices[FromIndex], Weights[i] ) );
    }

    free( Fringes );
    free( Precedences );
    free( MSTVertices );
    free( Weights );

    PQ_Destroy( PQ );
}

void Kruskal(Graph* G, Graph* MST )
{
    int           i;
    Vertex*       CurrentVertex = NULL;
    Vertex**      MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    DisjointSet** VertexSet     = 
                         (DisjointSet**)malloc( sizeof(DisjointSet*) * G->VertexCount );
    
    PriorityQueue* PQ      = PQ_Create(10);

    i = 0;    
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        Edge* CurrentEdge;

        VertexSet[i]   = DS_MakeSet( CurrentVertex );
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, MSTVertices[i] );

        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            PQ_Enqueue( PQ, NewNode );

            CurrentEdge = CurrentEdge->Next;
        }

        CurrentVertex  = CurrentVertex->Next;        
        i++;
    }

    while ( !PQ_IsEmpty( PQ ) )
    {
        Edge*  CurrentEdge;
        int    FromIndex;
        int    ToIndex;
        PQNode Popped;

        PQ_Dequeue( PQ, &Popped );
        CurrentEdge = (Edge*)Popped.Data;

        printf("%c - %c : %d\n", 
            CurrentEdge->From->Data, 
            CurrentEdge->Target->Data, 
            CurrentEdge->Weight );

        FromIndex = CurrentEdge->From->Index;
        ToIndex   = CurrentEdge->Target->Index;

        if ( DS_FindSet( VertexSet[FromIndex] ) != DS_FindSet( VertexSet[ToIndex] ) )
        {
            AddEdge( MSTVertices[FromIndex], 
                     CreateEdge( MSTVertices[FromIndex], 
                                 MSTVertices[ToIndex], 
                                 CurrentEdge->Weight ) );

            AddEdge( MSTVertices[ToIndex], 
                     CreateEdge( MSTVertices[ToIndex], 
                                 MSTVertices[FromIndex], 
                                 CurrentEdge->Weight ) );

            DS_UnionSet( VertexSet[FromIndex], VertexSet[ToIndex] );
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
        DS_DestroySet( VertexSet[i] );

    free( VertexSet );
    free( MSTVertices );
}


int main( void )
{
    
    /*  ±×·¡ÇÁ »ý¼º     */
    Graph* graph      = CreateGraph();
    Graph* PrimMST    = CreateGraph();
    Graph* KruskalMST = CreateGraph();
   
    /*  Á¤Á¡ »ý¼º */
    Vertex* A = CreateVertex( 'A' );
    Vertex* B = CreateVertex( 'B' );
    Vertex* C = CreateVertex( 'C' );
    Vertex* D = CreateVertex( 'D' );
    Vertex* E = CreateVertex( 'E' );
    Vertex* F = CreateVertex( 'F' );
    Vertex* G = CreateVertex( 'G' );
    Vertex* H = CreateVertex( 'H' );
    Vertex* I = CreateVertex( 'I' );

    /*  ±×·¡ÇÁ¿¡ Á¤Á¡À» Ãß°¡ */
    AddVertex( graph, A );
    AddVertex( graph, B );
    AddVertex( graph, C );
    AddVertex( graph, D );
    AddVertex( graph, E );
    AddVertex( graph, F );
    AddVertex( graph, G );
    AddVertex( graph, H );
    AddVertex( graph, I );

    /*  Á¤Á¡°ú Á¤Á¡À» °£¼±À¸·Î ÀÕ±â */
    AddEdge( A, CreateEdge(A, B, 35) );
    AddEdge( A, CreateEdge(A, E, 247) );
    
    AddEdge( B, CreateEdge(B, A, 35  ) );
    AddEdge( B, CreateEdge(B, C, 126 ) );
    AddEdge( B, CreateEdge(B, F, 150 ) );

    AddEdge( C, CreateEdge(C, B, 126 ) );
    AddEdge( C, CreateEdge(C, D, 117 ) );
    AddEdge( C, CreateEdge(C, F, 162 ) );
    AddEdge( C, CreateEdge(C, G, 220 ) );
    
    AddEdge( D, CreateEdge(D, C, 117 ) );

    AddEdge( E, CreateEdge(E, A, 247 ) );
    AddEdge( E, CreateEdge(E, F, 82 ) );
    AddEdge( E, CreateEdge(E, H, 98 ) );

    AddEdge( F, CreateEdge(F, B, 150 ) );
    AddEdge( F, CreateEdge(F, C, 162 ) );
    AddEdge( F, CreateEdge(F, E, 82  ) );
    AddEdge( F, CreateEdge(F, G, 154 ) );
    AddEdge( F, CreateEdge(F, H, 120 ) );

    AddEdge( G, CreateEdge(G, C, 220 ) );
    AddEdge( G, CreateEdge(G, F, 154 ) );
    AddEdge( G, CreateEdge(G, I, 106 ) );

    AddEdge( H, CreateEdge(H, E, 98  ) );
    AddEdge( H, CreateEdge(H, F, 120 ) );

    AddEdge( I, CreateEdge(I, G, 106 ) );
    
    /*  Á¤Á¡ B¸¦ ½ÃÀÛ Á¤Á¡À¸·Î ÇÏ´Â ÃÖ¼Ò ½ÅÀå Æ®¸®. */
    printf("Prim's Algorithm\n");
    Prim(graph, B, PrimMST);
    PrintGraph ( PrimMST );

    printf("Kruskal's Algorithm...\n");
    Kruskal(graph, KruskalMST);
    PrintGraph ( KruskalMST );
    
    /*  ±×·¡ÇÁ ¼Ò¸ê */
    DestroyGraph( PrimMST );
    DestroyGraph( KruskalMST );
    DestroyGraph( graph );

    return 0;
}
