#include "list.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Verify if list is order */
static bool list_is_ordered(node_t *list)
{       
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void quick_sort(node_t **list)
{
    int n = list_length(list);
    int value;
    int i = 0;
    int max_level = 2 * n;
    node_t *begin[max_level], *end[max_level];
    node_t *result = NULL, *left = NULL, *right = NULL;
    
    begin[0] = *list;
    end[0] = list_tail(list);
            
    while (i >= 0) {
        node_t *L = begin[i], *R = end[i];
        if (L != R) {
            node_t *pivot = L;
            value = pivot->value;
            node_t *p = pivot->next;
            pivot->next = NULL;
    
            while (p) {
                node_t *n = p;
                p = p->next;
                list_add(n->value > value ? &right : &left, n);
            }

            begin[i] = left;
            end[i] = list_tail(&left);
            begin[i + 1] = pivot;
            end[i + 1] = pivot;
            begin[i + 2] = right;
            end[i + 2] = list_tail(&right);

            left = right = NULL;
            i += 2;
        } else {
            if (L)
                list_add(&result, L);
            i--;
        }
    }
    *list = result;
}

int main(int argc, char **argv)
{
    node_t *list = NULL;

    // size_t count = 100000;

    // int *test_arr = malloc(sizeof(int) * count);

    // for (int i = 0; i < count; ++i)
    //     test_arr[i] = i;
    // shuffle(test_arr, count);

    // while (count--)
    //     list = list_construct(list, test_arr[count]);
    // Define the example list directly
    int example_list[] = {4, 1, 7, 2, 8};
    size_t count = sizeof(example_list) / sizeof(example_list[0]);

    // Construct the list
    for (int i = count - 1; i >= 0; --i)
        list = list_construct(list, example_list[i]);

    quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(&list);

    // free(test_arr);

    return 0;
}
