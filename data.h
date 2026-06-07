// ============================================================
//  data.h — Struktur Data, Konstanta, dan Variabel Global
// ============================================================
#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
using namespace std;

// --- Ukuran grid dan batas array ---
const int BARIS = 15, KOLOM = 13;
const int MAX_SLOT = 60, MAX_KENDARAAN = 60;

// --- Koordinat gerbang parkir (kolom 8, baris 1) ---
const int GX = 7, GY = 0;

// --- Struct slot parkir ---
struct Slot {
    string id_blok;
    int nomor, x, y;
    bool terisi;
    int jarak;
};

// --- Struct kendaraan ---
struct Kendaraan {
    string plat;
    int x, y;
    string blok;
    int nomor_slot;
};

// --- Struct titik koordinat (untuk BFS) ---
struct Titik { int x, y; };

// --- Variabel global (didefinisikan di data.cpp) ---
extern char      grid[BARIS][KOLOM];
extern Slot      daftar_slot[MAX_SLOT];
extern int       jumlah_slot;
extern Kendaraan daftar_kendaraan[MAX_KENDARAAN];
extern int       jumlah_kendaraan;

// --- Inisialisasi peta dan slot ---
void init_grid();
void init_slot();

#endif
