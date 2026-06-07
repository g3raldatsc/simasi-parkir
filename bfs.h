// ============================================================
//  bfs.h — Deklarasi Fungsi BFS dan Binary Search
// ============================================================
#ifndef BFS_H
#define BFS_H

#include "data.h"

// BFS: cari rute terpendek dari gerbang ke koordinat (tx, ty)
vector<Titik> cari_rute_BFS(int tx, int ty);

// Cetak instruksi navigasi langkah demi langkah
void cetak_instruksi(const vector<Titik>& jalur);

// Binary Search: cari kendaraan berdasarkan plat
// Mengembalikan indeks jika ditemukan, -1 jika tidak ada
int binary_search_kendaraan(const string& key);

#endif
