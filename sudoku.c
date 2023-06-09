#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j,k,marca[10],p;
  //Filas
  for(i = 0 ; i < 9 ; i++){
    for(int m = 0; m < 10 ; m++){
      marca[m] = 0;
    }
    for(j = 0 ; j < 9 ; j++){
      if(n -> sudo[i][j] != 0){
        if(marca[n -> sudo[i][j]] == 1){
          return 0;
        }
      }
      marca[n -> sudo[i][j]] = 1;
    } 
  }
  //Columnas
  for(j = 0 ; j < 9 ; j++){
    for(int m = 0; m < 10 ; m++){
      marca[m] = 0;
    }
    for(i = 0 ; i < 9 ; i++){
      if(n -> sudo[i][j] != 0){
        if(marca[n -> sudo[i][j]] == 1){
          return 0;
        }
      }
      marca[n -> sudo[i][j]] = 1;
    }
  } 
  //Submatrices
  for(k = 0 ; k < 9 ; k++){
    for(int m = 0; m < 10 ; m++){
      marca[m] = 0;
    }
    for(p = 0 ; p < 9 ; p++){
      int i = 3*(k/3) + (p/3);
      int j = 3*(k%3) + (p%3);
      if(n -> sudo[i][j] != 0){ 
        if(marca[n -> sudo[i][j]] == 1){
          return 0;
        }
      }
      marca[n -> sudo[i][j]] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i,j;
  for(i = 0 ; i < 9 ; i++){
    for(j = 0 ; j < 9 ; j++){
      if(n -> sudo[i][j] == 0){
        Node* adj_n = (Node*) malloc(sizeof(Node));
        for(int num = 1 ; num <= 9 ; num++){
          adj_n = copy(n);
          adj_n -> sudo[i][j] = num;
          if(is_valid(adj_n)){
            pushBack(list, adj_n);
          }
        }
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n){
  int i,j;
  for(i = 0 ; i < 9 ; i++){
    for(j = 0 ; j < 9 ; j++){
      if(n -> sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* s = createStack();
  push(s,initial);
  Node *a;
  
  while(is_empty(s) == 0){
    a = top(s);
    pop(s);
    if(is_final(a)){
      return a;
    }
    List *adj = get_adj_nodes(a);
    Node *node = first(adj);
    while(node != NULL){
      push(s,node);
      node = next(adj);
    }
    cont++;
    free(adj);
  }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/