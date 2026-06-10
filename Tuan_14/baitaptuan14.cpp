#include <iostream>
using namespace std;

// Cấu trúc node của cây AVL
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
};

// Hàm tiện ích lấy chiều cao của cây
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Hàm tiện ích tìm max giữa 2 số
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Khởi tạo node mới
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Node mới thêm vào luôn ở mức lá, có height = 1
    return(node);
}

// Xoay phải (Right Rotate)
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật lại chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Trả về root mới
    return x;
}

// Xoay trái (Left Rotate)
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật lại chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Trả về root mới
    return y;
}

// Lấy hệ số cân bằng (Balance Factor) của node N
int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Đệ quy thêm 1 node vào cây AVL
Node* insert(Node* node, int key) {
    // 1. Thực hiện chèn node như cây nhị phân tìm kiếm (BST) bình thường
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Không cho phép các node có giá trị trùng nhau
        return node;

    // 2. Cập nhật chiều cao của node cha (tổ tiên)
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Lấy hệ số cân bằng để kiểm tra xem node có bị mất cân bằng không
    int balance = getBalance(node);

    // Mất cân bằng -> Xử lý 4 trường hợp

    // Trường hợp 1: Mất cân bằng Trái - Trái (Left Left)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp 2: Mất cân bằng Phải - Phải (Right Right)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp 3: Mất cân bằng Trái - Phải (Left Right)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp 4: Mất cân bằng Phải - Trái (Right Left)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Trả về con trỏ node hiện tại
    return node;
}

// Duyệt In-order (Trái - Gốc - Phải) 
// -> Kết quả sẽ in ra dãy số tăng dần (đặc tính của BST/AVL)
void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Duyệt Pre-order (Gốc - Trái - Phải) 
// -> Để hình dung rõ hơn cấu trúc gốc - cành của cây sau khi xoay
void preOrder(Node *root) {
    if (root != NULL) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = NULL;

    // Mảng đầu vào theo đề bài
    int arr[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Thêm các phần tử vào cây
    for(int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }
    
    cout << "Duyet cay theo thu tu giua (In-order): \n";
    inOrder(root);
    
    cout << "\n\nDuyet cay theo thu tu truoc (Pre-order): \n";
    preOrder(root);

    return 0;
}
