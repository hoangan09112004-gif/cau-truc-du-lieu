#include <iostream>
#include <vector>

using namespace std;

// Khai bao cau truc node
struct Node {
    int year;
    Node* left;
    Node* right;
    
    Node(int y) {
        year = y;
        left = nullptr;
        right = nullptr;
    }
};

// Khoi tao cay rong
Node* initial_BST() {
    return nullptr;
}

// Them nut vao BST (Trai < Cha, Phải >= Cha)
Node* add_node_BST(Node* root, int year) {
    if (root == nullptr) {
        return new Node(year);
    }
    
    if (year < root->year) {
        root->left = add_node_BST(root->left, year);
    } else {
        root->right = add_node_BST(root->right, year);
    }
    
    return root;
}

// Ham vua tim kiem vua in ra trinh tu duyet cay
void Search_And_Print(Node* root, int target_year) {
    // Neu gap node rong tuc la khong tim thay
    if (root == nullptr) {
        cout << " (Khong tim thay gtri can tim)" << endl;
        return;
    }
    
    // In ra node dang xet
    cout << root->year;
    
    // Neu day chinh la node can tim -> In thong bao va dung de quy
    if (root->year == target_year) {
        cout << " (Da tim thay gtri can tim)" << endl;
        return;
    }
    
    // Neu chua tim thay, in them mui ten de chuan bi di tiep
    cout << " -> ";
    
    // Re trai hoac re phai tuy vao gia tri
    if (target_year < root->year) {
        Search_And_Print(root->left, target_year);
    } else {
        Search_And_Print(root->right, target_year);
    }
}

int main() {
    vector<int> data = {2001, 2002, 2006, 2007, 2003, 2004, 2005, 2001, 1999, 2004};
    Node* root = initial_BST();
    
    for (int y : data) {
        root = add_node_BST(root, y);
    }
    
    int target = 2004;
    
    // In ra dong text mo dau truoc khi chay ham tim kiem
    cout << "Trinh tu duyet cay: ";
    Search_And_Print(root, target);

    return 0;
}
