#include <ncurses.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

int main() {
    int arr[5] = {1,2,3,4,5,6};

    initscr();

    return 0;
}
