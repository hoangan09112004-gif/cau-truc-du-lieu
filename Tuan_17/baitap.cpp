#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n = 11;
string ten[] = {"HaNoi","ThaiNguyen","BacNinh","BacGiang","UongBi",
                "HaiPhong","HaiDuong","HungYen","PhuLy","HoaBinh","SonTay"};
int A[20][20]; // ma tran ke

int canh[][3] = {
    {0,6,7},   // HaNoi - HaiDuong   D1
    {6,7,5},   // HaiDuong - HungYen D2
    {7,8,6},   // HungYen - PhuLy    D3
    {0,8,8},   // HaNoi - PhuLy      D4
    {9,10,4},  // HoaBinh - SonTay   D5
    {10,0,3},  // SonTay - HaNoi     D6
    {0,1,9},   // HaNoi - ThaiNguyen D7
    {0,2,6},   // HaNoi - BacNinh    D8
    {2,3,5},   // BacNinh - BacGiang D9
    {3,4,4},   // BacGiang - UongBi  D10
    {2,4,7},   // BacNinh - UongBi   D11
    {4,5,3},   // UongBi - HaiPhong  D12
    {6,5,4}    // HaiDuong - HaiPhong D13
};
int soCanh = 13;

void taoMaTran(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) A[i][j] = (i==j)?0:INF;
    for(int i=0;i<soCanh;i++){
        int u=canh[i][0], v=canh[i][1], w=canh[i][2];
        A[u][v]=w; A[v][u]=w;
    }
}

// ----------- DIJKSTRA -----------
void dijkstra(int start){
    vector<int> dist(n, INF);
    vector<bool> visited(n,false);
    dist[start]=0;
    for(int k=0;k<n;k++){
        int u=-1, minD=INF;
        for(int i=0;i<n;i++)
            if(!visited[i] && dist[i]<minD){ minD=dist[i]; u=i; }
        if(u==-1) break;
        visited[u]=true;
        for(int v=0;v<n;v++)
            if(A[u][v]!=INF && dist[u]+A[u][v]<dist[v])
                dist[v]=dist[u]+A[u][v];
    }
    cout << "=== DIJKSTRA tu " << ten[start] << " ===\n";
    for(int i=0;i<n;i++) cout << ten[i] << " : " << dist[i] << "\n";
}

// ----------- PRIM -----------
void prim(){
    vector<bool> chon(n,false);
    chon[0]=true;
    int tong=0;
    cout << "\n=== PRIM ===\n";
    for(int dem=1; dem<n; dem++){
        int minW=INF, u_min=-1, v_min=-1;
        for(int u=0;u<n;u++) if(chon[u])
            for(int v=0;v<n;v++) if(!chon[v] && A[u][v]<minW){
                minW=A[u][v]; u_min=u; v_min=v;
            }
        chon[v_min]=true;
        tong+=minW;
        cout << ten[u_min] << " - " << ten[v_min] << " : " << minW << "\n";
    }
    cout << "Tong trong so: " << tong << "\n";
}

// ----------- KRUSKAL -----------
int parent[20];
int find(int x){ return parent[x]==x ? x : parent[x]=find(parent[x]); }

void kruskal(){
    for(int i=0;i<n;i++) parent[i]=i;
    vector<array<int,3>> ds;
    for(int i=0;i<soCanh;i++) ds.push_back({canh[i][0], canh[i][1], canh[i][2]});
    sort(ds.begin(), ds.end(), [](array<int,3>&a, array<int,3>&b){ return a[2]<b[2]; });

    cout << "\n=== KRUSKAL ===\n";
    int tong=0;
    for(auto &c : ds){
        int u=c[0], v=c[1], w=c[2];
        int ru=find(u), rv=find(v);
        if(ru!=rv){
            parent[ru]=rv;
            tong+=w;
            cout << ten[u] << " - " << ten[v] << " : " << w << "\n";
        }
    }
    cout << "Tong trong so: " << tong << "\n";
}

int main(){
    taoMaTran();
    dijkstra(0);   // bat dau tu Ha Noi
    prim();
    kruskal();
    return 0;
}
