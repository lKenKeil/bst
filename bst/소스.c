#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 전역 변수로 루트 노드 정의
TreeNode* root = NULL;

// 방문한 노드 수를 세는 변수
int visitedNodes = 0;

// 이진 트리에 노드 추가 (재귀)
TreeNode* insert(TreeNode* node, int data) {
    if (node == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        visitedNodes++;
        return newNode;
    }

    visitedNodes++;
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

// 이진 트리에서 노드 삭제 (재귀)
TreeNode* delete(TreeNode* node, int data) {
    if (node == NULL)
        return node;

    if (data < node->data)
        node->left = delete(node->left, data);
    else if (data > node->data)
        node->right = delete(node->right, data);
    else {
        // 노드를 찾았을 때
        visitedNodes++; // 이 위치로 이동
        if (node->left == NULL) {
            TreeNode* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            TreeNode* temp = node->left;
            free(node);
            return temp;
        }

        // 두 자식 노드가 있는 경우
        TreeNode* temp = node->right;
        while (temp->left != NULL)
            temp = temp->left;

        node->data = temp->data;
        node->right = delete(node->right, temp->data);
    }
    return node;
}


// 중위 순회 (재귀)
void inorderTraversal(TreeNode* node) {
    if (node == NULL)
        return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

// 이진 트리에서 노드 검색 (반복)
int search(TreeNode* node, int data) {
    visitedNodes = 0;
    while (node != NULL) {
        visitedNodes++;
        if (data < node->data)
            node = node->left;
        else if (data > node->data)
            node = node->right;
        else
            return 1; // 노드를 찾음
    }
    return 0; // 노드를 찾지 못함
}

int main() {
    // 주어진 이진 트리 노드 생성
    TreeNode n1 = { 25, NULL, NULL };
    TreeNode n2 = { 16, NULL, &n1 };
    TreeNode n3 = { 42, NULL, NULL };
    TreeNode n4 = { 46, &n3, NULL };
    TreeNode n5 = { 55, NULL, NULL };
    TreeNode n6 = { 53, &n4, &n5 };
    TreeNode n7 = { 41, &n2, &n6 };
    TreeNode n8 = { 62, NULL, NULL };
    TreeNode n9 = { 64, NULL, NULL };
    TreeNode n10 = { 63, &n8, &n9 };
    TreeNode n11 = { 70, NULL, NULL };
    TreeNode n12 = { 65, &n10, &n11 };
    TreeNode n13 = { 74, &n12, NULL };
    TreeNode n14 = { 60, &n7, &n13 };
    root = &n14;

    char choice;
    int data;

    while (1) {
        printf("\n<Menu>\n");
        printf("s: 이진 트리에서 노드 검색\n");
        printf("i: 이진 트리에 노드 추가\n");
        printf("d: 이진 트리에서 노드 삭제\n");
        printf("t: 중위 순회 출력\n");
        printf("I: i 메뉴를 반복 실행\n");
        printf("D: d 메뉴를 반복 실행\n");

        scanf(" %c", &choice);

        switch (choice) {
        case 's':
            printf("검색할 노드 값을 입력하세요: ");
            scanf("%d", &data);
            if (search(root, data))
            {
                printf("노드를 찾았습니다.\n");
                
            }
            else
                printf("노드를 찾지 못했습니다.\n");
            printf("중위 순회 결과: ");
            inorderTraversal(root);
            printf("방문한 노드 수: %d\n", visitedNodes);
            break;

        case 'i':
            printf("추가할 노드 값을 입력하세요: ");
            scanf("%d", &data);
            root = insert(root, data);
            printf("중위 순회 결과: ");
            inorderTraversal(root);
            printf("\n방문한 노드 수: %d\n", visitedNodes);
            break;

        case 'd':
            printf("삭제할 노드 값을 입력하세요: ");
            scanf("%d", &data);
            root = delete(root, data);
            printf("중위 순회 결과: ");
            inorderTraversal(root);
            printf("\n방문한 노드 수: %d\n", visitedNodes);
            break;

        case 't':
            printf("중위 순회 결과: ");
            inorderTraversal(root);
            printf("\n방문한 노드 수: %d\n", visitedNodes);
            break;

        case 'I':
            printf("반복할 횟수를 입력하세요: ");
            int count;
            scanf("%d", &count);
            for (int i = 0; i < count; i++) {
                printf("추가할 노드 값을 입력하세요: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("중위 순회 결과: ");
                inorderTraversal(root);
                printf("\n방문한 노드 수: %d\n", visitedNodes);
            }
            break;

        case 'D':
            printf("반복할 횟수를 입력하세요: ");
            scanf("%d", &count);
            for (int i = 0; i < count; i++) {
                printf("삭제할 노드 값을 입력하세요: ");
                scanf("%d", &data);
                root = delete(root, data);
                printf("중위 순회 결과: ");
                inorderTraversal(root);
                printf("\n방문한 노드 수: %d\n", visitedNodes);
            }
            break;

        default:
            printf("잘못된 메뉴 선택입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}
