#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//might need these??
//struct node;
//struct edge;

struct node {
  char* name;
  struct edge* next;
};

struct edge {
  int weight;
  char* name;
  struct edge* next;
};

struct node** makeGraph(int graphSize) {
  struct node** graph = malloc(graphSize*sizeof(struct node*));
  return graph;
}

void freeGraph(struct node** graph, int graphSize) {
  for(int i = 0; i < graphSize; i++) {
    struct node* head = graph[i];
    struct edge* prev = 0;
    struct edge* ptr = head->next;
    while(ptr != 0) {
      prev = ptr;
      ptr = ptr->next;
      free(prev->name);
      free(prev);
    }
    free(head->name);
    free(head);
  }
  free(graph);
}

struct node* makeVert(char* name) {
  struct node* nVert = malloc(sizeof(struct node));
  nVert->name = name;
  nVert->next = 0;
  return nVert;
}

struct edge* makeEdge(char* name, int w) {
  struct edge* nEdge = malloc(sizeof(struct edge));
  nEdge->weight = w;
  nEdge->name = name;
  nEdge->next = 0;
  return nEdge;
}

/*
void printGraph(struct node** graph, int graphSize) {
  for(int i = 0; i < graphSize; i++) {
    printf("V: %s E: ", graph[i]->name);
    struct edge* eptr = graph[i]->next;
    while(eptr != 0) {
      printf("%s ", eptr->name);
      eptr = eptr->next;
    }
    printf("\n");
  }
}
*/

int main(int argc, char* argv[argc+1]) {

  FILE* file1 = fopen(argv[1], "r");
  FILE* file2 = fopen(argv[2], "r");
  
  if(file1 == 0 || file2 == 0) {
    printf("error\n");
    return EXIT_SUCCESS;
  }
  
  int graphSize;
  fscanf(file1, "%d\n", &graphSize);
  struct node** wGraph = makeGraph(graphSize);
  for(int i = 0; i < graphSize; i++) {
    char* vertieName = malloc(32*sizeof(char));
    fscanf(file1, "%s\n", vertieName);
    struct node* nVert = makeVert(vertieName);
    wGraph[i] = nVert;
  }

  
  char* vert1 = malloc(32*sizeof(char));
  char* vert2holder = malloc(32*sizeof(char));
  int weight = 0;
  while(fscanf(file1, "%s %s %d\n", vert1, vert2holder, &weight ) != EOF) {
    //node ptr to head of vert1 init
    struct node* vert1ptr = 0;

    //to make the address to pass to the edge
    char* vert2name = malloc(32*sizeof(char));
    strcpy(vert2name, vert2holder);
    struct edge* wEdge = makeEdge(vert2name, weight);
    
    for(int i = 0; i < graphSize; i++) {
      if(strcmp(vert1, wGraph[i]->name) == 0) {
	vert1ptr = wGraph[i];
	break;
      }
    }
    
    //gotta look for where to place the edge
    if(vert1ptr->next == 0) {
      vert1ptr->next = wEdge;
    }
    else if(strcmp(wEdge->name, vert1ptr->next->name) < 0) {
      wEdge->next = vert1ptr->next;
      vert1ptr->next = wEdge;
    }
    else {
      struct edge* eptr = vert1ptr->next;
      while(eptr->next != 0) {
	if(strcmp(wEdge->name, eptr->next->name) < 0) {
	  break;
	}
	eptr = eptr->next;
      }
      wEdge->next = eptr->next;
      eptr->next = wEdge;
    }
  }

  
  char operation;
  char* qVertie = malloc(32*sizeof(char));
  while(fscanf(file2, "%c %s\n", &operation, qVertie) != EOF) {

    struct node* targetHead = 0;
    for(int i = 0; i < graphSize; i++) {
      if(strcmp(qVertie, wGraph[i]->name) == 0) {
	targetHead = wGraph[i];
	break;
      }
    }
    
    if(operation == 'o') {

      int outcount = 0;
      struct edge* eptr = targetHead->next;
      while(eptr != 0) {
	outcount++;
	eptr = eptr->next;
      }
      printf("%d\n", outcount);
      
    }
    else if(operation == 'i') {

      int incount = 0;

      for(int i = 0; i < graphSize; i++) {
	struct edge* eptr = wGraph[i]->next;
	while(eptr != 0) {
	  if(strcmp(qVertie, eptr->name) == 0) {
	    incount++;
	  }
	  eptr = eptr->next;
	}
      }

      printf("%d\n", incount);
      
    }
    else if(operation == 'a') {

      struct edge* eptr = targetHead->next;
      while(eptr != 0) {
	printf("%s ", eptr->name);
	eptr = eptr->next;
      }
      printf("\n");
      
    }
  }

  free(vert1);
  free(vert2holder);
  free(qVertie);
  freeGraph(wGraph, graphSize);
  fclose(file1);
  fclose(file2);
  return EXIT_SUCCESS;
}
