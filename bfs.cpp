// ============================================================
//  bfs.cpp — Implementasi BFS (Navigasi) & Binary Search
// ============================================================
#include "bfs.h"
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

// ============================================================
//  BFS — Cari jalur terpendek dari gerbang ke slot target
//  Aturan: hanya boleh lewat 'O' (jalan) atau titik target
// ============================================================
vector<Titik> cari_rute_BFS(int tx, int ty) {
    Titik  parent[BARIS][KOLOM];
    bool   visited[BARIS][KOLOM] = {};
    for (int i = 0; i < BARIS; i++)
        for (int j = 0; j < KOLOM; j++)
            parent[i][j] = {-1, -1};

    queue<Titik> Q;
    Q.push({GX, GY});
    visited[GY][GX] = true;

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1,-1,  0, 0};
    bool ketemu = false;

    while (!Q.empty() && !ketemu) {
        Titik cur = Q.front(); Q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d], ny = cur.y + dy[d];
            if (nx < 0 || nx >= KOLOM || ny < 0 || ny >= BARIS) continue;
            if (visited[ny][nx]) continue;
            if (grid[ny][nx] != 'O' && !(nx == tx && ny == ty)) continue;
            visited[ny][nx]  = true;
            parent[ny][nx]   = cur;
            Q.push({nx, ny});
            if (nx == tx && ny == ty) { ketemu = true; break; }
        }
    }

    // Rekonstruksi jalur mundur dari target ke start
    vector<Titik> jalur;
    if (!ketemu) return jalur;
    Titik cur = {tx, ty};
    while (!(cur.x == GX && cur.y == GY)) {
        jalur.push_back(cur);
        cur = parent[cur.y][cur.x];
    }
    jalur.push_back({GX, GY});
    reverse(jalur.begin(), jalur.end());
    return jalur;
}

// ============================================================
//  Cetak instruksi navigasi berdasarkan jalur BFS
// ============================================================
void cetak_instruksi(const vector<Titik>& jalur) {
    if (jalur.empty()) { cout << "  [!] Rute tidak ditemukan.\n"; return; }
    cout << "\n  --- Instruksi Navigasi ---\n";
    int step = 1, i = 1;
    while (i < (int)jalur.size()) {
        int dx = jalur[i].x - jalur[i-1].x;
        int dy = jalur[i].y - jalur[i-1].y;
        string arah;
        if      (dy > 0) arah = "MAJU (Utara)";
        else if (dy < 0) arah = "MUNDUR (Selatan)";
        else if (dx > 0) arah = "KANAN (Timur)";
        else              arah = "KIRI (Barat)";
        int jml = 0;
        while (i < (int)jalur.size() &&
               (jalur[i].x - jalur[i-1].x) == dx &&
               (jalur[i].y - jalur[i-1].y) == dy)
            { jml++; i++; }
        cout << "  " << step++ << ". " << arah << " " << jml << " langkah\n";
    }
    cout << "  => Anda telah tiba di slot parkir tujuan.\n";
}

// ============================================================
//  Binary Search — Cari kendaraan di array terurut (by plat)
// ============================================================
int binary_search_kendaraan(const string& key) {
    int lo = 0, hi = jumlah_kendaraan - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if      (daftar_kendaraan[mid].plat == key) return mid;
        else if (daftar_kendaraan[mid].plat <  key) lo = mid + 1;
        else                                         hi = mid - 1;
    }
    return -1;
}
