#include <iostream>
#include <string>

using namespace std;

// 1. Khai bao cau truc File
struct File {
    string name;
    double size_MB;  // Kich thuoc tinh bang Megabyte
    int timestamp;   // Trat tu thoi gian (vi du: 1, 2, 3...)
};

// 2. Khai bao cau truc mot Nut (Node) trong DSLK
struct Node {
    File data;
    Node* next;
};

// Ham chen file theo trat tu thoi gian (Cau 2)
void insertFileSorted(Node*& head, string name, double size, int time) {
    Node* newNode = new Node;
    newNode->data = {name, size, time};
    newNode->next = nullptr;

    // Neu DS rong hoac file moi cu hon file dau tien
    if (head == nullptr || head->data.timestamp >= newNode->data.timestamp) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Tim vi tri thich hop de chen
    Node* current = head;
    while (current->next != nullptr && current->next->data.timestamp < newNode->data.timestamp) {
        current = current->next;
    }
    
    // Chen vao sau current
    newNode->next = current->next;
    current->next = newNode;
}

// Ham tinh tong kich thuoc cac file (Cau 3)
double calculateTotalSize(Node* head) {
    double total = 0;
    Node* current = head;
    while (current != nullptr) {
        total += current->data.size_MB;
        current = current->next;
    }
    return total;
}

// Ham loai bo file nho nhat de sao luu USB 32GB (Cau 4)
void backupToUSB(Node*& head) {
    double maxSize = 32.0 * 1024; // 32768 MB (Tuong duong 32GB)
    double currentTotal = calculateTotalSize(head);

    // Xoa dan file nho nhat cho den khi tong dung luong vua voi USB
    while (currentTotal > maxSize && head != nullptr) {
        Node* minNode = head;
        Node* minPrev = nullptr;
        
        Node* current = head;
        Node* prev = nullptr;

        // Duyet tim node co dung luong nho nhat
        while (current != nullptr) {
            if (current->data.size_MB < minNode->data.size_MB) {
                minNode = current;
                minPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        cout << "  -> Dang loai bo file nho nhat: " << minNode->data.name 
             << " (" << minNode->data.size_MB << " MB)\n";

        // Thuc hien xoa minNode khoi danh sach de giai phong dung luong
        currentTotal -= minNode->data.size_MB; // Cap nhat lai tong dung luong
        
        if (minPrev == nullptr) { 
            // Neu file nho nhat nam o dau danh sach
            head = head->next;
        } else {
            // Neu file nho nhat nam o giua hoac cuoi
            minPrev->next = minNode->next; 
        }
        delete minNode; // Giai phong bo nho cua file da xoa
    }
}