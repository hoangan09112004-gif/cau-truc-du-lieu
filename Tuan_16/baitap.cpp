#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int MAX = 100;
const int VOCUNG = 999999;

string tenThanhPho[] = {
    "Ha Noi",
    "Hai Duong",
    "Hung Yen",
    "Phu Ly",
    "Hoa Binh",
    "Son Tay",
    "Thai Nguyen",
    "Bac Ninh",
    "Bac Giang",
    "Uong Bi",
    "Hai Phong"
};
int soDinh = 11;

int doThi[MAX][MAX];

void khoiTaoDoThi() {
    for (int i = 0; i < soDinh; i++) {
        for (int j = 0; j < soDinh; j++) {
            if (i == j) doThi[i][j] = 0;
            else doThi[i][j] = VOCUNG;
        }
    }

    doThi[0][1] = doThi[1][0] = 1;  
    doThi[1][2] = doThi[2][1] = 1;  
    doThi[2][3] = doThi[3][2] = 1;  
    doThi[0][3] = doThi[3][0] = 1;  
    doThi[0][4] = doThi[4][0] = 1;  
    doThi[0][5] = doThi[5][0] = 1;  
    doThi[0][6] = doThi[6][0] = 1;  
    doThi[0][7] = doThi[7][0] = 1;  
    doThi[7][8] = doThi[8][7] = 1;  
    doThi[8][9] = doThi[9][8] = 1;  
    doThi[7][9] = doThi[9][7] = 1;  
    doThi[9][10] = doThi[10][9] = 1; 
    doThi[1][10] = doThi[10][1] = 1; 
}

void inDuongDi(int batDau, int ketThuc, int truoc[]) {
    if (truoc[ketThuc] == -1 && batDau != ketThuc) {
        cout << "Khong co duong di!" << endl;
        return;
    }

    stack<int> loTrinh;
    int hienTai = ketThuc;

    while (hienTai != -1) {
        loTrinh.push(hienTai);
        hienTai = truoc[hienTai];
    }

    while (!loTrinh.empty()) {
        cout << tenThanhPho[loTrinh.top()];
        loTrinh.pop();
        if (!loTrinh.empty()) cout << " -> ";
    }
    cout << endl;
}

void dijkstra(int batDau, int ketThuc) {
    int khoangCach[MAX];
    bool daChot[MAX];
    int truoc[MAX];

    for (int i = 0; i < soDinh; i++) {
        khoangCach[i] = VOCUNG;
        daChot[i] = false;
        truoc[i] = -1;
    }
    khoangCach[batDau] = 0;

    for (int i = 0; i < soDinh - 1; i++) {
        int minKC = VOCUNG;
        int u = -1;
        for (int j = 0; j < soDinh; j++) {
            if (!daChot[j] && khoangCach[j] < minKC) {
                minKC = khoangCach[j];
                u = j;
            }
        }

        if (u == -1) break;
        daChot[u] = true;

        for (int v = 0; v < soDinh; v++) {
            if (!daChot[v] && doThi[u][v] != VOCUNG) {
                if (khoangCach[u] + doThi[u][v] < khoangCach[v]) {
                    khoangCach[v] = khoangCach[u] + doThi[u][v];
                    truoc[v] = u;
                }
            }
        }
    }

    if (khoangCach[ketThuc] == VOCUNG) {
        cout << "Khong co duong di tu " << tenThanhPho[batDau] << " den " << tenThanhPho[ketThuc] << endl;
    } else {
        cout << "Lo trinh tu " << tenThanhPho[batDau] << " den " << tenThanhPho[ketThuc] << ": ";
        inDuongDi(batDau, ketThuc, truoc);
    }
}

int main() {
    khoiTaoDoThi();

    // Test tim duong tu Ha Noi (0) den Hai Phong (10)
    dijkstra(0, 10);
    
    
    // Test tim duong tu Phu Ly (3) den Uong Bi (9)
    dijkstra(3, 9);

    return 0;
}
