#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

void* heap_top(Heap* pq){
    if (pq->capac == 0 || pq->size == 0) return NULL;
    void * dato = pq->heapArray[0].data;
    return dato;
}

void heap_push(Heap* pq, void* data, int priority){
  if (pq->capac == pq->size) 
  {
     pq->capac *= 2;
     pq->capac++;
     pq->heapArray = (heapElem *) realloc (pq->heapArray, sizeof(heapElem) * pq->capac);
  }

  pq->heapArray[pq->size].data = data;
  pq->heapArray[pq->size].priority = priority;

  for (int i = pq->size; i > 0; i--)
  {
     int parent = (i - 1)/2;
     if(pq->heapArray[i].priority > pq->heapArray[parent].priority)
     {
        void * oldData = pq->heapArray[parent].data;
        pq->heapArray[parent].data = pq->heapArray[i].data;
        pq->heapArray[i].data = oldData;

        int oldPri = pq->heapArray[parent].priority;
        pq->heapArray[parent].priority = pq->heapArray[i].priority;
        pq->heapArray[i].priority = oldPri;
     }
  }
  pq->size++;
}

void heap_pop(Heap* pq){
   void * data = pq->heapArray[pq->size-1].data;
   int pri = pq->heapArray[pq->size-1].priority;

   pq->heapArray[pq->size].priority = pq->heapArray[0].priority;
   pq->heapArray[0].priority = pri;
   pq->heapArray[pq->size-1].priority = 0;

   pq->heapArray[pq->size].data = pq->heapArray[0].data;
   pq->heapArray[0].data = data;
   pq->heapArray[pq->size-1].data = NULL;

   pq->size--;
   int hijoIzq, hijoDer, hijoNuevo;

   for (int i = 0; i < pq->size; i++)
   {
      hijoIzq = (2*i) + 1;
      hijoDer = (2*i) + 2;

      if(hijoIzq > pq->size) pq->heapArray[hijoIzq].priority = 0;
      if(hijoDer > pq->size) pq->heapArray[hijoDer].priority = 0;

      if(pq->heapArray[hijoIzq].priority < pq->heapArray[hijoDer].priority)
      {
         if(pq->heapArray[i].priority < pq->heapArray[hijoDer].priority)
         {
            pq->heapArray[i].data = pq->heapArray[hijoDer].data;
            pq->heapArray[hijoDer].data = data;

            pq->heapArray[i].priority = pq->heapArray[hijoDer].priority;
            pq->heapArray[hijoDer].priority = pri;
            i = hijoDer;
         } else break;
      }
      else if (pq->heapArray[hijoDer].priority < pq->heapArray[hijoIzq].priority)
      {
         if(pq->heapArray[i].priority < pq->heapArray[hijoIzq].priority)
         {
            pq->heapArray[i].data = pq->heapArray[hijoIzq].data;
            pq->heapArray[hijoIzq].data = data;

            pq->heapArray[i].priority = pq->heapArray[hijoIzq].priority;
            pq->heapArray[hijoIzq].priority = pri;
            i = hijoDer;
         } else break;
      }
   }

}

Heap* createHeap(){
   Heap * new = (Heap *) malloc (sizeof(Heap));
   new->capac = 3;
   new->size = 0;
   new->heapArray = (heapElem *) malloc (sizeof(heapElem)*3);
   return new;
}
