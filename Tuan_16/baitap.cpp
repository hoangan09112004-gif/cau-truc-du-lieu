#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int MAX = 100;
const int VOCUNG = 999999; // Dung mot so rat lon de dai dien cho vo cuc (chua co duong di)

string tenThanhPho[] = {
    "Ha Noi",     // 0
    "Bac Ninh",   // 1
    "Hai Phong",  // 2
    "Lang Son",   // 3
    "Nam Dinh",   // 4
    "Ninh Binh"   // 5
};
int soDinh = 6;

// Ma tran trong so (luu khoang cach giua cac tinh)
int doThi[MAX][MAX];

// Ham khoi tao du lieu ban do
void khoiTaoDoThi() {
    // Ban dau cho khoang cach giua moi dinh la Vo cuc, khoang cach den chinh no la 0
    for (int i = 0; i < soDinh; i++) {
        for (int j = 0; j < soDinh; j++) {
            if (i == j) doThi[i][j] = 0;
            else doThi[i][j] = VOCUNG;
        }
    }

    // Them cac tuyen duong tu tuan 14 KEM THEO KHOANG CACH (km) gia lap
    doThi[0][1] = doThi[1][0] = 30;  // Ha Noi <-> Bac Ninh: 30km
    doThi[0][2] = doThi[2][0] = 100; // Ha Noi <-> Hai Phong: 100km
    doThi[0][4] = doThi[4][0] = 90;  // Ha Noi <-> Nam Dinh: 90km
    doThi[1][3] = doThi[3][1] = 120; // Bac Ninh <-> Lang Son: 120km
    doThi[2][3] = doThi[3][2] = 150; // Hai Phong <-> Lang Son: 150km
    doThi[4][5] = doThi[5][4] = 30;  // Nam Dinh <-> Ninh Binh: 30km
}

// Ham in lo trinh bang cach dung Stack (Ngan xep) de lat nguoc mang truy vet
void inDuongDi(int batDau, int ketThuc, int truoc[]) {
    if (truoc[ketThuc] == -1 && batDau != ketThuc) {
        cout << "Khong co duong di!" << endl;
        return;
    }

    stack<int> loTrinh;
    int hienTai = ketThuc;
    
    // Lan nguoc tu diem ket thuc ve diem bat dau
    while (hienTai != -1) {
        loTrinh.push(hienTai);
        hienTai = truoc[hienTai];
    }

    // In ra man hinh
    while (!loTrinh.empty()) {
        cout << tenThanhPho[loTrinh.top()];
        loTrinh.pop();
        if (!loTrinh.empty()) cout << " -> ";
    }
    cout << endl;
}

// CAI DAT THUAT TOAN DIJKSTRA
void dijkstra(int batDau, int ketThuc) {
    int khoangCach[MAX]; // Mang luu k/c ngan nhat tu diem bat dau den cac diem khac
    bool daChot[MAX];    // Mang danh dau xem dinh do da chot duoc k/c ngan nhat chua
    int truoc[MAX];      // Mang luu lai dinh lien truoc de tim lai duong di

    // Buoc 1: Khoi tao cac mang
    for (int i = 0; i < soDinh; i++) {
        khoangCach[i] = VOCUNG;
        daChot[i] = false;
        truoc[i] = -1; // Chua co dinh lien truoc
    }
    khoangCach[batDau] = 0; // K/c tu diem bat dau den chinh no bang 0

    // Buoc 2: Vong lap tim duong
    for (int i = 0; i < soDinh - 1; i++) {
        // 2.1: Tim dinh u co khoang cach nho nhat trong so cac dinh CHUA CHOT
        int minKC = VOCUNG;
        int u = -1;
        for (int j = 0; j < soDinh; j++) {
            if (!daChot[j] && khoangCach[j] < minKC) {
                minKC = khoangCach[j];
                u = j;
            }
        }

        if (u == -1) break; // Do thi bi dut doan, khong tim them duoc
        daChot[u] = true;   // Chot dinh u

        // 2.2: Tu dinh u vua chot, cap nhat lai khoang cach cho cac dinh ke voi u
        for (int v = 0; v < soDinh; v++) {
            if (!daChot[v] && doThi[u][v] != VOCUNG) {
                // Neu di qua u ma ngan hon duong cu thi cap nhat
                if (khoangCach[u] + doThi[u][v] < khoangCach[v]) {
                    khoangCach[v] = khoangCach[u] + doThi[u][v];
                    truoc[v] = u; // Ghi chu lai: "De den duoc v nhanh nhat, phai di qua u"
                }
            }
        }
    }

    // Buoc 3: Xuat ket qua
    if (khoangCach[ketThuc] == VOCUNG) {
        cout << "Khong co duong di tu " << tenThanhPho[batDau] << " den " << tenThanhPho[ketThuc] << endl;
    } else {
        cout << "=> Quang duong ngan nhat: " << khoangCach[ketThuc] << " km" << endl;
        cout << "=> Lo trinh chi tiet: ";
        inDuongDi(batDau, ketThuc, truoc);
    }
}

int main() {
    khoiTaoDoThi();

    cout << "BAI TAP TUAN 16: TIM DUONG DI NGAN NHAT (DIJKSTRA)" << endl;

    int diemXuatPhat = 0; // Ha Noi
    int diemDich = 3;     // Lang Son

    cout << "Yeu cau: Tim duong di tu " << tenThanhPho[diemXuatPhat] << " den " << tenThanhPho[diemDich] << "\n\n";
    
    dijkstra(diemXuatPhat, diemDich);
    
  
    cout << "Yeu cau: Tim duong di tu Ha Noi (0) den Ninh Binh (5)\n\n";
    dijkstra(0, 5);

    return 0;
}
