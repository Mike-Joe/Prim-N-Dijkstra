#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define inf INFINITY
typedef struct
{
    int name;
    struct gnode * next;
    int weight;
}gnode;

typedef struct
{ int visited;
  int key;
  int parent;
  gnode * head;
}vertex;

typedef struct
{ int numv;
  int directed;
  vertex * arr;
}graph;

int main()
{//{  graph g;
//   creategraph(&g , 5 , 1);
//
//   addedge(&g , 5 , 0 , 1 );
//   addedge(&g , 10 , 0 , 2 );
//
//   addedge(&g , 3 , 1 , 2 );
//   addedge(&g , 9 , 1 , 4 );
//   addedge(&g , 2 , 1 , 3 );
//
//   addedge(&g , 2 , 2 , 1 );
//   addedge(&g , 1 , 2 , 4 );
//
//   addedge(&g , 7 , 3 , 0 );
//   addedge(&g , 6 , 3 , 4 );
//
//   addedge(&g , 4 , 4 , 3 );
//   dijkestra(&g , 0);
int n,m;
scanf("%d  %d",&n,&m);
int x[n][m];
x[0][0] = 4;
printf("%d",x[0][0]);
    return 0;
}

gnode * creategnode(int weight , int name)
{
    gnode * newgnode = (gnode *) malloc(sizeof(gnode));
    newgnode -> name = name;
    newgnode -> weight = weight;
    newgnode -> next = NULL;
    return newgnode;
}

void creategraph(graph * g , int v , int directed)
{ if (v > 0)
  {g -> numv = v;
   g -> directed = directed;
   g -> arr = (vertex *) malloc(v * sizeof(vertex));
   int i;
   for(i = 0 ; i < v ; i++)
   {
       g -> arr[i].head = NULL;
   }
  }
}

int checkpreconnected(vertex v , int dest)
{  gnode * head = v.head;
    while(head != NULL)
    { if (head -> name == dest ) return 1;
      head = head -> next;
    }
    return 0;
}

void printlist(vertex v)
{   gnode * head = v.head;
    while(head!=NULL)
    { printf(" -(%d)-> [%d]", head -> weight , head -> name);
      head = head -> next;
    }
}

void addedge(graph * g, int weight  , int src , int dest)
{  if(src < g -> numv && src >= 0 && dest < g -> numv && dest >= 0 && weight > 0 )
   {

    if( !( checkpreconnected(g -> arr[src] , dest) ) )
    {
      gnode * newgnode = creategnode(weight , dest);
      newgnode -> next = g -> arr[src].head;
      g ->arr[src].head = newgnode;

        if (g -> directed == 0 && src != dest )
       {
           gnode * newgnode = creategnode(weight , src);
           newgnode -> next = g -> arr[dest].head;
           g ->arr[dest].head = newgnode;
       }
    }
   }
}

void printgraph(graph * g)
{
    int i;
    for(i = 0 ; i < g -> numv ; i++)
    { printf("[%d]",i);
      printlist(g -> arr[i]);
      printf("\n");
    }
}

void initialize_singlesource(graph * g)
{  int i;
    for(i = 0 ; i < g -> numv ; i++)
    { g -> arr[i].key = inf;
      g -> arr[i].parent = -1;
      g -> arr[i].visited = 0;
    }
}

int checkallvisited(graph * g)
{  int i;
    for(i = 0 ; i < g -> numv ; i++)
    { if(g ->arr[i].visited == 0)
        return 0;
    }
    return 1;
}

int extractminindex(graph * g)
{ int i ;
  int minkey ;
  int minindex ;
    for(i = 0 ; i < g -> numv ; i++)
    { if ( g ->arr[i].visited == 0)
      {
        minkey = g ->arr[i].key;
        minindex = i;
        break;
      }
    }

  for(i = 0 ; i < g -> numv ; i++)
    { if ( g ->arr[i].visited == 0 && g ->arr[i].key < minkey)
      {
        minkey = g ->arr[i].key;
        minindex = i;
      }
    }

    g ->arr[minindex].visited = 1;
    return minindex;
}

void primedit(graph * g , int minindex)
{ gnode * head = g ->arr[minindex].head;
   int adjvertex , edgeweight;
    while(head!=NULL)
    {   adjvertex = head ->name;
        edgeweight = head ->weight;
        if (g ->arr[adjvertex].visited == 0 && edgeweight < g ->arr[adjvertex].key)
        {
          g ->arr[adjvertex].key = edgeweight;
          g ->arr[adjvertex].parent = minindex;
        }
        head = head ->next;
    }

}

void printprim(graph * g)
{
   graph primgraph;
   creategraph(&primgraph , g ->numv , g ->directed);
   int i;
   int totalweight=0;
    for(i = 0 ; i < g -> numv ; i++)
    { totalweight+= g ->arr[i].key ;
      if (g ->arr[i].parent != -1)
      {
          addedge(&primgraph , g ->arr[i].key , g ->arr[i].parent , i);
      }
    }
    printf("Minimum spanning tree is \n");
    printgraph(&primgraph);
    printf("total weight = %d", totalweight);
}

void prim(graph * g , int r)
{ printf("The original graph is \n");
  printgraph(g);
  int minindex;
  initialize_singlesource(g);
  g ->arr[r].key = 0;
  while ( ! (checkallvisited(g) ) )
  {   minindex = extractminindex(g);
      primedit(g , minindex);
  }
         printprim(g);
}

void relax(graph * g , int minindex)
{ gnode * head = g ->arr[minindex].head;
   int adjvertex , edgeweight;
    while(head!=NULL)
    {   adjvertex = head ->name;
        edgeweight = head ->weight;
        if (g ->arr[adjvertex].visited == 0 &&  g ->arr[minindex].key + edgeweight < g ->arr[adjvertex].key)
        {
          g ->arr[adjvertex].key =  g ->arr[minindex].key + edgeweight;
          g ->arr[adjvertex].parent = minindex;
        }
        head = head ->next;
    }

}

void print_vertexpath(graph * g , int i)
{
   if (g ->arr[i].parent == -1)
     { printf(" no path"); }

   else if (i == g ->arr[i].parent)
     { printf(" <-- [%d]",i , i);   }

  else
    {
        while (i != g ->arr[i].parent)
        { printf(" <-- [%d]", g ->arr[i].parent);
          i = g ->arr[i].parent;
        }
    }

}

void print_shortestpaths(graph * g)
{  int i;
   printf("The shortest path from each vertex is \n");
    for(i = 0 ; i < g -> numv ; i++)
    {
        printf("[%d]", i);
        print_vertexpath(g , i);
        printf("\n");
    }

}


void printdijkestra(graph * g)
{  graph dijkestragraph;
   creategraph(&dijkestragraph , g ->numv , g ->directed);
   int i;
    for(i = 0 ; i < g -> numv ; i++)
    {
      if (g ->arr[i].parent != -1 && g ->arr[i].parent != i)
      {
          addedge(&dijkestragraph , g ->arr[i].key - g ->arr[g ->arr[i].parent].key , g ->arr[i].parent , i);
      }
    }
    printf("Shortest path tree is \n");
    printgraph(&dijkestragraph);
    print_shortestpaths(g);

}

void dijkestra(graph * g , int s)
{ printf("The original graph is \n");
  printgraph(g);
  int minindex;
  initialize_singlesource(g);
  g ->arr[s].key = 0;
  g ->arr[s].parent = s;
   while ( ! (checkallvisited(g) ) )
  {   minindex = extractminindex(g);
      relax(g , minindex);
  }
         printdijkestra(g);

}
