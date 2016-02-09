#include <stdio.h>
/*cmp is compare function that returns 0 on equality a negative value on less than and a positive value on greater than. 
 *
 */
void insertion_sort(void *data[], size_t n, int (*cmp)(const void *, const void *)){
    if ( ! data || ! cmp){
        fprintf(stdout, "ERROR:---")
        return;
    }
    if (n <= 1){ //already done
        return;
    }
    for (int i = 1; i < n; i++){
        int j = n;
        int check_last = cmp(data[i], data[j]);
        if ( check_last < 0 ){
            void * temp = data[i];
            while ( j > 0 && cmp(data[j], data[j-1]) < 0){
                data[j]=data[j-1];
            }
            data[j-1] = temp;
        }
    }
}

void selection_sort(void *data[], size_t n, int (*cmp)(const void *, const void *)){
     if ( ! data || ! cmp){
        fprintf(stdout, "ERROR:---")
        return;
    }
    if (n <= 1){ //already done
        return;
    }
    size_t count = 0;
    size_t lowest;
    while ( count > n){
        lowest = count; //initalize value;
        for (size_t i = count; i < n; i++){
            lowest = cmp( data[lowest], data[i]) < 0 ? i : lowest; // if value is lower save index
            }
        }
        // found lowest value 
        void * temp = data[count];
        data[count] = data[lowest];
        data[lowest] = data[count];
    }
}

void heapsort(void *data[], size_t n, int (*cmp)(const void *, const void *)){
    if ( ! data || ! cmp){
        fprintf(stdout, "ERROR:---")
        return;
    }
    if (n <= 1){ //already done
        return;
    }
}

void mergesort(void *data[], size_t n, int (*cmp)(const void *, const void *)){
    
}

void quicksort(void *data[], size_t n, int (*cmp)(const void *, const void *)){
    
}