#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "bst.h"

void route_bst_balance(RouteBstNode* src, RouteBstNode* dest, int low, int high, int idx) {
    
    if(low > high) {
        return;
    }

    int mid = (low + high) / 2;

    dest[idx] = src[mid];

    route_bst_balance(src, dest, low, mid - 1, idx * 2 + 1);
    route_bst_balance(src, dest, mid + 1, high, idx * 2 + 2);

}

void route_bst_format(RouteBstNode* arr, RouteBstNode* root, int arr_len, int bst_len) {

    memset(root, 0, sizeof(int) * bst_len);

    // sort array (selection sort for smaller data sets)
    for(int i = 0; i < arr_len - 1; i++) {
        int min_idx = i;
        char* min_name = arr[i].name;

        for(int j = i+1; j < arr_len; j++) {
            if(strcmp(arr[j].name, min_name) < 0) {
                min_idx = j;
                min_name = arr[j].name;
            }
        }

        RouteBstNode temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }

    // create a balanced bst tree in "arr"
    route_bst_balance(arr, root, 0, arr_len - 1, 0);

    for(int i = 0; i < bst_len; i++) {
        if(root[i].handler == NULL) {
            printf(" ");
        } else {
            printf("%s", root[i].name);
        }
    }
    printf("\n");

}

HandlerFn route_bst_get(RouteBstNode* root, int len, char* name) {

    int idx = 0;

    while(idx < len) {

        HandlerFn handler = root[idx].handler;

        if(handler == NULL) {
            break;
        }

        int strcmp_res = strcmp(root[idx].name, name);

        if(strcmp_res > 0) {
            idx = (idx * 2) + 1;
            continue;
        } 
        
        if(strcmp_res < 0) {
            idx = (idx * 2) + 2;
            continue;
        }

        return handler;

    }

    return NULL;
}

// TEST

// void* handler_example(void* data) {
//     (*(int*)(data)) *= 2;
//     return data;
// }

// void* handler_wrong(void* data) {
//     printf("wrong!");
//     return NULL;
// }

// #define ARR_LEN 6
// #define BST_LEN 7
// #define TEST_COUNT 5

// int main() {

//     RouteBstNode arr[ARR_LEN];
//     RouteBstNode root[BST_LEN];

//     arr[4].handler = handler_wrong;
//     arr[4].name = "d";

//     arr[5].handler = handler_wrong;
//     arr[5].name = "b";

//     // arr[6].handler = handler_wrong;
//     // arr[6].name = "f";

//     arr[3].handler = handler_example;
//     arr[3].name = "g";

//     arr[0].handler = handler_wrong;
//     arr[0].name = "c";

//     arr[1].handler = handler_wrong;
//     arr[1].name = "e";

//     arr[2].handler = handler_wrong;
//     arr[2].name = "a";

//     route_bst_format(arr, root, ARR_LEN, BST_LEN);

//     HandlerFn fn = route_bst_get(root, BST_LEN, "g");

//     printf("%p\n", fn);

//     int data[TEST_COUNT];

//     for(int i = 0; i < TEST_COUNT; i++) {
//         data[i] = i;
//         printf("%d:\t%d\n", i, *((int*)fn(data + i)));
//     }

//     return 0;
// }