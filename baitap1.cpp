#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

// Khai báo cấu trúc dữ liệu theo yêu cầu ---
struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[12];
    char hoTen[50];
    int gioiTinh; // 0: Nam, 1: Nữ
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

// --- Các hàm bổ trợ ---
void init(List &L) {
    L.first = L.last = NULL;
}

Node* createNode(SinhVien sv) {
    Node* p = new Node;
    p->data = sv;
    p->link = NULL;
    return p;
}

// So sánh ngày sinh
bool laCungNgaySinh(Ngay n1, Ngay n2) {
    return (n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam);
}

// 2: Chèn sinh viên vào danh sách đã sắp xếp theo mã SV
void insertSorted(List &L, SinhVien sv) {
    Node* newNode = createNode(sv);
    if (L.first == NULL || strcmp(sv.maSV, L.first->data.maSV) < 0) {
        newNode->link = L.first;
        L.first = newNode;
        if (L.last == NULL) L.last = newNode;
        return;
    }

    Node* curr = L.first;
    while (curr->link != NULL && strcmp(curr->link->data.maSV, sv.maSV) < 0) {
        curr = curr->link;
    }
    newNode->link = curr->link;
    curr->link = newNode;
    if (newNode->link == NULL) L.last = newNode;
}

//  3: In các sinh viên có cùng ngày sinh
void inSinhVienCungNgaySinh(List L) {
    bool found = false;
    for (Node* p = L.first; p != NULL; p = p->link) {
        bool hasMatch = false;
        for (Node* q = L.first; q != NULL; q = q->link) {
            if (p != q && laCungNgaySinh(p->data.ngaySinh, q->data.ngaySinh)) {
                hasMatch = true;
                break;
            }
        }
        if (hasMatch) {
            cout << "SV: " << p->data.hoTen << " - MSV: " << p->data.maSV << endl;
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
}

// 4: Loại bỏ các sinh viên có cùng ngày sinh
void xoaSinhVienCungNgaySinh(List &L) {
    if (L.first == NULL) return;

    // Đánh dấu các node cần xóa (để đơn giản trong bài tập DSLK)
    Node* curr = L.first;
    while (curr != NULL) {
        bool trung = false;
        for (Node* temp = L.first; temp != NULL; temp = temp->link) {
            if (curr != temp && laCungNgaySinh(curr->data.ngaySinh, temp->data.ngaySinh)) {
                trung = true;
                break;
            }
        }

        if (trung) {
            // Logic xóa node curr
            Node* toDelete = curr;
            if (curr == L.first) {
                L.first = L.first->link;
                curr = L.first;
            } else {
                Node* prev = L.first;
                while (prev->link != curr) prev = prev->link;
                prev->link = curr->link;
                if (curr == L.last) L.last = prev;
                curr = curr->link;
            }
            delete toDelete;
        } else {
            curr = curr->link;
        }
    }
}

void hienThi(List L) {
    for (Node* p = L.first; p != NULL; p = p->link) {
        printf("[%s] %s\n", p->data.maSV, p->data.hoTen);
    }
}

int main() {
    List ds;
    init(ds);

    // Test data
    SinhVien sv1 = {"20223835", "An Hoang", 0, {9, 11, 2004}, "NgheAn", "ET1", "SET"};
    SinhVien sv2 = {"20223836", "Cong Minh", 0, {9, 11, 2004}, "VinhPhuc", "ET1", "SET"};
    SinhVien sv3 = {"20233385", "Trong Hung", 1, {15, 5, 2005}, "Hanoi", "IT1", "SET"};

    insertSorted(ds, sv1);
    insertSorted(ds, sv2);
    insertSorted(ds, sv3);

    cout << "Danh sach sau khi chen sorted: " << endl;
    hienThi(ds);

    cout << "\n SV co cung ngay sinh: " << endl;
    inSinhVienCungNgaySinh(ds);

    return 0;
}