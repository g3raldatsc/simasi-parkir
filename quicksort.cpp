// ============================================================
//  quicksort.cpp — Implementasi Algoritma Quick Sort
// ============================================================
#include "quicksort.h"
#include <algorithm>
using namespace std;

// --- Partisi slot berdasarkan jarak ---
static int partisi_slot(Slot S[], int lo, int hi) {
    int pivot = S[hi].jarak, i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (S[j].jarak <= pivot) swap(S[++i], S[j]);
    swap(S[i+1], S[hi]);
    return i + 1;
}

// Quick Sort slot: urut dari jarak terpendek ke terpanjang
void quick_sort_slot(Slot S[], int lo, int hi) {
    if (lo < hi) {
        int p = partisi_slot(S, lo, hi);
        quick_sort_slot(S, lo, p-1);
        quick_sort_slot(S, p+1, hi);
    }
}

// --- Partisi kendaraan berdasarkan nomor plat (string) ---
static int partisi_kendaraan(Kendaraan K[], int lo, int hi) {
    string pivot = K[hi].plat;
    int i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (K[j].plat <= pivot) swap(K[++i], K[j]);
    swap(K[i+1], K[hi]);
    return i + 1;
}

// Quick Sort kendaraan: urut alfabetis berdasarkan plat
void quick_sort_kendaraan(Kendaraan K[], int lo, int hi) {
    if (lo < hi) {
        int p = partisi_kendaraan(K, lo, hi);
        quick_sort_kendaraan(K, lo, p-1);
        quick_sort_kendaraan(K, p+1, hi);
    }
}
