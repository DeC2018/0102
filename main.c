#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to perform level order traversal
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (!root) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    struct TreeNode* q[1001];
    int head = 0;
    int tail = 0;
    int** ret = malloc(sizeof(*ret) * 2000);
    *returnColumnSizes = malloc(sizeof(**returnColumnSizes) * 2000);
    q[tail++] = root;

    while ((tail - head) % 1001) {
        int sz = (*returnColumnSizes)[*returnSize] = (tail - head) % 1001;
        ret[*returnSize] = malloc(sizeof(**ret) * sz);
        for (int i = 0; i < sz; i++) {
            struct TreeNode* p = q[head++ % 1001];
            ret[*returnSize][i] = p->val;
            if (p->left)
                q[tail++ % 1001] = p->left;
            if (p->right)
                q[tail++ % 1001] = p->right;
        }
        (*returnSize)++;
    }
    return ret;
}

// Helper function to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to parse input string like "[3,9,20,null,null,15,7]"
int parseInput(const char* s, char arr[][16], int* n) {
    int idx = 0, arr_idx = 0;
    char buf[16];
    int buf_idx = 0;
    while (s[idx]) {
        if (s[idx] == '[' || s[idx] == ']' || s[idx] == ' ' || s[idx] == '\n') {
            idx++;
            continue;
        }
        if (s[idx] == ',') {
            if (buf_idx > 0) {
                buf[buf_idx] = '\0';
                strcpy(arr[arr_idx++], buf);
                buf_idx = 0;
            }
            idx++;
            continue;
        }
        buf[buf_idx++] = s[idx++];
    }
    if (buf_idx > 0) {
        buf[buf_idx] = '\0';
        strcpy(arr[arr_idx++], buf);
    }
    *n = arr_idx;
    return arr_idx;
}

// Helper function to build a binary tree from an array of strings (level order, "null" for NULL)
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode* nodes[1000] = {0};
    int i, j = 1;
    nodes[0] = newNode(atoi(arr[0]));
    int front = 0, rear = 1;
    while (front < rear && j < n) {
        struct TreeNode* curr = nodes[front++];
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->left = newNode(atoi(arr[j]));
            nodes[rear++] = curr->left;
        }
        j++;
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->right = newNode(atoi(arr[j]));
            nodes[rear++] = curr->right;
        }
        j++;
    }
    return nodes[0];
}

// Helper function to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Helper function to print the level order traversal result
void printResult(int** result, int returnSize, int* returnColumnSizes) {
    printf("[");
    for (int i = 0; i < returnSize; ++i) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; ++j) {
            printf("%d", result[i][j]);
            if (j + 1 < returnColumnSizes[i])
                printf(",");
        }
        printf("]");
        if (i + 1 < returnSize)
            printf(",");
    }
    printf("]\n");
}

int main() {
    const char* inputs[] = {
        "[3,9,20,null,null,15,7]",
        "[1]",
        "[]"
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: root = %s\n", inputs[i]);

        char arr[1000][16];
        int n = 0;

        parseInput(inputs[i], arr, &n);
        struct TreeNode* root = buildTree(arr, n);

        int returnSize = 0;
        int* returnColumnSizes = NULL;
        int** result = levelOrder(root, &returnSize, &returnColumnSizes);

        printf("Output: ");
        printResult(result, returnSize, returnColumnSizes);

        for (int j = 0; j < returnSize; ++j)
            free(result[j]);
        free(result);
        free(returnColumnSizes);

        deleteTree(root);
    }

    return 0;
}
