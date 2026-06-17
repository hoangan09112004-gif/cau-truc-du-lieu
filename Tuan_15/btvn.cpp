#include <iostream>
#include <string>
#include <queue>

using namespace std;

const int MAX = 100;

string tenThanhPho[] = {
    "Ha Noi",
    "Bac Ninh",
    "Hai Phong",
    "Lang Son",
    "Nam Dinh",
    "Ninh Binh"
};
int soDinh = 6;

int maTranKe[MAX][MAX];

void khoiTaoMaTran() {
    for (int i = 0; i < soDinh; i++) {
        for (int j = 0; j < soDinh; j++) {
            maTranKe[i][j] = 0;
        }
    }
    
    maTranKe[0][1] = maTranKe[1][0] = 1; 
    maTranKe[0][2] = maTranKe[2][0] = 1;
    maTranKe[0][4] = maTranKe[4][0] = 1;
    
    maTranKe[1][3] = maTranKe[3][1] = 1;
    
    maTranKe[2][3] = maTranKe[3][2] = 1;
    
    maTranKe[4][5] = maTranKe[5][4] = 1;
}

void BFS_MaTran(int dinhBatDau) {
    bool chuaXet[MAX];
    for (int i = 0; i < soDinh; i++) chuaXet[i] = true;
    
    queue<int> hangDoi;
    
    hangDoi.push(dinhBatDau);
    chuaXet[dinhBatDau] = false;
    
    cout << "Thu tu duyet BFS: ";
    
    while (!hangDoi.empty()) {
        int u = hangDoi.front();
        hangDoi.pop();
        
        cout << tenThanhPho[u] << " -> ";
        
        for (int v = 0; v < soDinh; v++) {
            if (maTranKe[u][v] == 1 && chuaXet[v] == true) {
                hangDoi.push(v);
                chuaXet[v] = false;
            }
        }
    }
    cout << "KET THUC." << endl;
}

struct Node {
    int id_dinh;
    Node* next;
};

Node* dsKe[MAX]; 

void themCanh(int u, int v) {
    Node* p = new Node;
    p->id_dinh = v;
    p->next = dsKe[u];
    dsKe[u] = p;
}

void khoiTaoDSLK() {
    for (int i = 0; i < soDinh; i++) {
        dsKe[i] = NULL;
    }
    
    themCanh(0, 1); themCanh(1, 0);
    themCanh(0, 2); themCanh(2, 0);
    themCanh(0, 4); themCanh(4, 0);
    
    themCanh(1, 3); themCanh(3, 1);
    
    themCanh(2, 3); themCanh(3, 2);
    
    themCanh(4, 5); themCanh(5, 4);
}

void BFS_DSLK(int dinhBatDau) {
    bool chuaXet[MAX];
    for (int i = 0; i < soDinh; i++) chuaXet[i] = true;
    
    queue<int> hangDoi;
    hangDoi.push(dinhBatDau);
    chuaXet[dinhBatDau] = false;
    
    cout << "Thu tu duyet BFS: ";
    
    while (!hangDoi.empty()) {
        int u = hangDoi.front();
        hangDoi.pop();
        
        cout << tenThanhPho[u] << " -> ";
        
        Node* temp = dsKe[u];
        while (temp != NULL) {
            int v = temp->id_dinh;
            if (chuaXet[v] == true) {
                hangDoi.push(v);
                chuaXet[v] = false;
            }
            temp = temp->next;
        }
    }
    cout << "KET THUC." << endl;
}

void giaiPhongBoNho() {
    for (int i = 0; i < soDinh; i++) {
        Node* p = dsKe[i];
        while (p != NULL) {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }
}

int main() {
    cout << "==========================================================" << endl;
    cout << "BAI TAP TUAN 14: DO THI GIAO THONG (BAT DAU TU HA NOI)" << endl;
    cout << "==========================================================" << endl << endl;

    cout << "CACH 1: LUU TRU BANG MANG DONG/MA TRAN KE:" << endl;
    khoiTaoMaTran();
    BFS_MaTran(0); 
    cout << "----------------------------------------------------------" << endl;

    cout << "CACH 2: LUU TRU BANG DANH SACH LIEN KET:" << endl;
    khoiTaoDSLK();
    BFS_DSLK(0);
    cout << "----------------------------------------------------------" << endl;

    giaiPhongBoNho();
    
   return 0;
}
