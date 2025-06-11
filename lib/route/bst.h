#ifndef CRSERVER_ROUTES_BST
#define CRSERVER_ROUTES_BST

typedef void* (*HandlerFn)(void*);

typedef struct {
    // maybe store each name is contigous memory (arena) or use char[] instead to store inside struct (requires putting a cap on name length)
    char* name;
    HandlerFn handler;
} RouteBstNode;


void route_bst_format(RouteBstNode* arr, RouteBstNode* root, int arr_len, int bst_len);
// returns a pointer to the handler function of the route with the matching `name`
// returns NULL if `name` did not match any route
HandlerFn route_bst_get(RouteBstNode* root, int len, char* name);

#endif