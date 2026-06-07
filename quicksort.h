// ============================================================
//  quicksort.h — Deklarasi Fungsi Quick Sort
// ============================================================
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "data.h"

// Quick Sort slot berdasarkan jarak Manhattan (ascending)
void quick_sort_slot(Slot S[], int lo, int hi);

// Quick Sort kendaraan berdasarkan nomor plat (alfabetis)
void quick_sort_kendaraan(Kendaraan K[], int lo, int hi);

#endif
