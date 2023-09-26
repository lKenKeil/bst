#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ���� Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ���� ������ ��Ʈ ��� ����
TreeNode* root = NULL;

// �湮�� ��� ���� ���� ����
int visitedNodes = 0;

// ���� Ʈ���� ��� �߰� (���)
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

// ���� Ʈ������ ��� ���� (���)
TreeNode* delete(TreeNode* node, int data) {
    if (node == NULL)
        return node;

    if (data < node->data)
        node->left = delete(node->left, data);
    else if (data > node->data)
        node->right = delete(node->right, data);
    else {
        // ��带 ã���� ��
        visitedNodes++; // �� ��ġ�� �̵�
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

        // �� �ڽ� ��尡 �ִ� ���
        TreeNode* temp = node->right;
        while (temp->left != NULL)
            temp = temp->left;

        node->data = temp->data;
        node->right = delete(node->right, temp->data);
    }
    return node;
}


// ���� ��ȸ (���)
void inorderTraversal(TreeNode* node) {
    if (node == NULL)
        return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

// ���� Ʈ������ ��� �˻� (�ݺ�)
int search(TreeNode* node, int data) {
    visitedNodes = 0;
    while (node != NULL) {
        visitedNodes++;
        if (data < node->data)
            node = node->left;
        else if (data > node->data)
            node = node->right;
        else
            return 1; // ��带 ã��
    }
    return 0; // ��带 ã�� ����
}

int main() {
    // �־��� ���� Ʈ�� ��� ����
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
        printf("s: ���� Ʈ������ ��� �˻�\n");
        printf("i: ���� Ʈ���� ��� �߰�\n");
        printf("d: ���� Ʈ������ ��� ����\n");
        printf("t: ���� ��ȸ ���\n");
        printf("I: i �޴��� �ݺ� ����\n");
        printf("D: d �޴��� �ݺ� ����\n");

        scanf(" %c", &choice);

        switch (choice) {
        case 's':
            printf("�˻��� ��� ���� �Է��ϼ���: ");
            scanf("%d", &data);
            if (search(root, data))
            {
                printf("��带 ã�ҽ��ϴ�.\n");
                
            }
            else
                printf("��带 ã�� ���߽��ϴ�.\n");
            printf("���� ��ȸ ���: ");
            inorderTraversal(root);
            printf("�湮�� ��� ��: %d\n", visitedNodes);
            break;

        case 'i':
            printf("�߰��� ��� ���� �Է��ϼ���: ");
            scanf("%d", &data);
            root = insert(root, data);
            printf("���� ��ȸ ���: ");
            inorderTraversal(root);
            printf("\n�湮�� ��� ��: %d\n", visitedNodes);
            break;

        case 'd':
            printf("������ ��� ���� �Է��ϼ���: ");
            scanf("%d", &data);
            root = delete(root, data);
            printf("���� ��ȸ ���: ");
            inorderTraversal(root);
            printf("\n�湮�� ��� ��: %d\n", visitedNodes);
            break;

        case 't':
            printf("���� ��ȸ ���: ");
            inorderTraversal(root);
            printf("\n�湮�� ��� ��: %d\n", visitedNodes);
            break;

        case 'I':
            printf("�ݺ��� Ƚ���� �Է��ϼ���: ");
            int count;
            scanf("%d", &count);
            for (int i = 0; i < count; i++) {
                printf("�߰��� ��� ���� �Է��ϼ���: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("���� ��ȸ ���: ");
                inorderTraversal(root);
                printf("\n�湮�� ��� ��: %d\n", visitedNodes);
            }
            break;

        case 'D':
            printf("�ݺ��� Ƚ���� �Է��ϼ���: ");
            scanf("%d", &count);
            for (int i = 0; i < count; i++) {
                printf("������ ��� ���� �Է��ϼ���: ");
                scanf("%d", &data);
                root = delete(root, data);
                printf("���� ��ȸ ���: ");
                inorderTraversal(root);
                printf("\n�湮�� ��� ��: %d\n", visitedNodes);
            }
            break;

        default:
            printf("�߸��� �޴� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    return 0;
}
