#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "pagerank.h"

double calculate_sum_of_in_links(list* plist, double** scores, int page_index){

  page* page = NULL;
  node* current = plist->head;
  while(current != NULL){
    if(current->page->index == page_index || current == plist->tail){
      break;
    }
    current = current->next;
  }

  if(current == NULL || current->page->index != page_index){
    return 0;
  }else{
    page = current->page;
  }
  if(page == NULL || page->inlinks == NULL || page->inlinks->length == 0){
    return 0;
  }

  double sum = 0;// return value
  current = page->inlinks->head;
  while(current != NULL){
    sum += (scores[current->page->index][0] / current->page->noutlinks);
    if(current == page->inlinks->tail){
      break;
    }
    current = current->next;
  }
  return sum;
}

void pagerank(list* plist, int ncores, int npages, int nedges, double dampener) {

    /*
        to do:
        - implement this function
        - implement any other necessary functions
        - implement any other useful data structures
    */

    int num_thread = 1;
    // initialise matrix to store scores
    int length = plist->length;
    double** scores = malloc(sizeof(double*) * length);
    for(int i=0; i<length; i++){
      scores[i] = malloc(sizeof(double) * 2);
      scores[i][0] = 1.0 / length;
    }
    // initialise variable to store vector norm
    double vn = 1.0;
    // iterate until vn >= EPSILON
    #pragma omp parallel num_threads(num_thread)
    while (vn > EPSILON){
      vn = 0.0;
      #pragma omp for
      for (int i=0; i<length; i++){
        double re = calculate_sum_of_in_links(plist, scores, i);
        scores[i][1] = ((1 - dampener) / length) + dampener * (re);
        vn += (scores[i][1] - scores[i][0]) * (scores[i][1] - scores[i][0]);
        scores[i][0] = scores[i][1];
      }
      vn = sqrt(vn);
    }
    // output results and free malloced memory
    node* current = plist->head;
    while(current != NULL){
      printf("%s %.4lf\n", current->page->name, scores[current->page->index][0]);
      if(current == plist->tail){
        break;
      }
      current = current->next;
    }
    for(int i=0; i<length; i++){
      free(scores[i]);
    }
    free(scores);
}

/*
######################################
### DO NOT MODIFY BELOW THIS POINT ###
######################################
*/

int main(void) {

    /*
    ######################################################
    ### DO NOT MODIFY THE MAIN FUNCTION OR HEADER FILE ###
    ######################################################
    */

    list* plist = NULL;

    double dampener;
    int ncores, npages, nedges;

    /* read the input then populate settings and the list of pages */
    read_input(&plist, &ncores, &npages, &nedges, &dampener);

    /* run pagerank and output the results */
    pagerank(plist, ncores, npages, nedges, dampener);

    /* clean up the memory used by the list of pages */
    page_list_destroy(plist);

    return 0;
}
