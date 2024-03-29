#include<stdio.h>
#include<stdlib.h>

struct node {
  int value;
  struct node* next;
};

struct node* create(int);
struct node* insert(struct node*, int);
struct node* delete(struct node*, int);

struct node* create(int v) {
  struct node* newN = malloc(sizeof(struct node));
  newN->value = v;
  newN->next = 0;
  return newN;
}

struct node* insert(struct node* head, int v) {
  struct node* newN = create(v);

  if(head == 0) {
    return newN;
  }

  struct node* prev = head;
  for(struct node* ptr = head; (ptr != 0) && (ptr->value <= newN->value); ptr = ptr->next) {
    prev = ptr;	
  }
  if(prev->value == newN->value) {
    free(newN);
    return head;
  }
  else if(prev == head) {
    if(head->value > newN->value) {
      newN->next = head;
      head = newN;
      return head;
    }
    else {
      newN->next = head->next;
      head->next = newN;
      return head;
    }
  }
  else if(prev->next == 0) {
    prev->next = newN;
    return head;
  }
  else {
    newN->next = prev->next;
    prev->next = newN;
    return head;
  }

  free(newN);
  return head;
}

struct node* delete(struct node* head, int v) {
  if(head == 0) {
    return head;
  }
  
  struct node* prev = 0;
  for(struct node* ptr = head; ptr != 0; ptr = ptr->next) {
    if(ptr->value > v) {
      return head;
    }
    
    if(ptr->value == v) {
      if(ptr == head) {
	prev = head;
	head = head->next;
	free(prev);
	return head;
      }
      prev->next = ptr->next;
      free(ptr);
      return head;
    }
    prev = ptr;
  }

  return head;
}

int main(int argc, char* argv[argc+1]) {

  FILE* instruct = fopen(argv[1], "r");

  if(instruct == 0) {
    printf("error\n");
    return EXIT_SUCCESS;
  }

  //initialize the linked list
  struct node* head = 0;
  
  char keyword[7];
  while(fscanf(instruct,"%s", keyword) != EOF) {
    if(keyword[0] == 'I') {
      int d;
      fscanf(instruct, "%d\n", &d);
      head = insert(head, d);
    }
    else if(keyword[0] == 'D') {
      int d;
      fscanf(instruct, "%d\n", &d);
      head = delete(head, d);
    }

    if(head == 0) {
      printf("EMPTY\n");
    }
    else{
      for(struct node* ptr = head; ptr != 0; ptr = ptr->next) {
	printf("%d ", ptr->value);
      }
      printf("\n");
     }
  }
  
  struct node* gcleaner = head;
  while(head != 0) {
    gcleaner = head;
    head = head->next;
    free(gcleaner);
  }
  fclose(instruct);
  return EXIT_SUCCESS;
}
