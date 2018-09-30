#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct queue {
  int value;
  struct queue *next;
};
typedef struct queue queue;

struct response {
  int value;
  queue *head;
};
typedef struct response response;

//this function adds an element to the queue by creating the element with the value "newValue"
//and turning the *tail into the new element
queue *insertElement(queue *tail, int newValue) {
  queue *new;

  new = (queue *)malloc(sizeof(queue));
  new->value = newValue;
  queue x = *tail;
  new->next = &x;
  tail = new;
  return tail;
}


//this function returns the first element of the queue because its a queue
struct response removeElement(queue *tail, queue *head){
  int aux;

  queue *actual;
  actual = tail;

  //this saves the value of the first element
  aux = (int) head->value;
  while (actual->next != NULL) {
    if (actual->next->next == NULL) {
      free(head);
      head = actual;
      break;
      }
    actual = actual->next;
    }


    response res;
    res.value = aux;
    res.head = head;

    return res;
  }

bool emptyQueue(queue *tail) {
  if (tail == NULL) {
    return true;
  }
  return false;
}

void printQueue(queue *tail){
  queue *actual;
  actual = tail;
  while (actual != NULL) {
    printf("%i\n", actual->value);
    actual = actual->next;
  }

}

int main() {
    queue *head;
    queue *tail;

    queue *new;
    new = (queue *)malloc(sizeof(queue));
    new->value = 1;
    

    head = new;


    tail = insertElement(new, 2);
    printQueue(tail);
    tail = insertElement(new, 4);
    printQueue(tail);
    tail = insertElement(new, 5);
    tail = insertElement(new, 6);

    printQueue(tail);

    response res;


    res = removeElement(tail, head);
    head = res.head;
    printf("%i 4 \n", res.value);

    res = removeElement(tail, head);
    head = res.head;
    printf("%i 4 \n", res.value);

    res = removeElement(tail, head);
    head = res.head;
    printf("%i 4 \n", res.value);

    res = removeElement(tail, head);
    head = res.head;
    printf("%i 4 \n", res.value);


    return 0;
  }
