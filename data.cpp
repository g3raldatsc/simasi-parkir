// ============================================================
//  data.cpp — Definisi Global + Inisialisasi Grid & Slot
// ============================================================
#include "data.h"

// --- Definisi variabel global ---
char      grid[BARIS][KOLOM];
Slot      daftar_slot[MAX_SLOT];
int       jumlah_slot = 0;
Kendaraan daftar_kendaraan[MAX_KENDARAAN];
int       jumlah_kendaraan = 0;

// ============================================================
//  Inisialisasi peta 2D parkir
//  'O' = Jalan  |  'F' = Slot kosong  |  '1' = Bangunan
//  y=0 (bawah/gerbang) ... y=14 (atas/blok K)
// ============================================================
void init_grid() {
    // Baris 0 - Gerbang (semua '1' kecuali kolom GX)
    for (int x = 0; x < KOLOM; x++) grid[0][x] = '1';
    grid[0][GX] = 'O';

    // Baris 1 - Jalur (kolom 8-12 = Pos)
    for (int x = 0; x < KOLOM; x++) grid[1][x] = 'O';
    for (int x = 8; x < KOLOM; x++) grid[1][x] = '1';

    // Baris 2 - Slot A + Gudang
    for (int x = 0; x < KOLOM; x++) grid[2][x] = 'O';
    for (int x = 0; x < 5;     x++) grid[2][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[2][x] = '1';

    // Baris 3 - Jalur + Gudang
    for (int x = 0; x < KOLOM; x++) grid[3][x] = 'O';
    for (int x = 8; x < KOLOM; x++) grid[3][x] = '1';

    // Baris 4 - Slot B + Gudang
    for (int x = 0; x < KOLOM; x++) grid[4][x] = 'O';
    for (int x = 0; x < 5;     x++) grid[4][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[4][x] = '1';

    // Baris 5, 7, 9, 11, 13 - Jalur murni
    for (int x = 0; x < KOLOM; x++) grid[5][x]  = 'O';
    for (int x = 0; x < KOLOM; x++) grid[7][x]  = 'O';
    for (int x = 0; x < KOLOM; x++) grid[9][x]  = 'O';
    for (int x = 0; x < KOLOM; x++) grid[11][x] = 'O';
    for (int x = 0; x < KOLOM; x++) grid[13][x] = 'O';

    // Baris 6 - Slot C + Slot D
    for (int x = 0; x < KOLOM; x++) grid[6][x] = 'O';
    for (int x = 0; x < 5;     x++) grid[6][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[6][x] = 'F';

    // Baris 8 - Slot E + Slot F
    for (int x = 0; x < KOLOM; x++) grid[8][x] = 'O';
    for (int x = 0; x < 5;     x++) grid[8][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[8][x] = 'F';

    // Baris 10 - Slot G + Slot H
    for (int x = 0; x < KOLOM; x++) grid[10][x] = 'O';
    for (int x = 0; x < 5;     x++) grid[10][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[10][x] = 'F';

    // Baris 12 - Slot I + Slot J
    for (int x = 0; x < KOLOM; x++) grid[12][x] = 'O';
    for (int x = 0; x < 5;     x++) grid[12][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[12][x] = 'F';

    // Baris 14 - Slot K + Gedung
    for (int x = 0; x < KOLOM; x++) grid[14][x] = 'F';
    for (int x = 8; x < KOLOM; x++) grid[14][x] = '1';
}

// ============================================================
//  Inisialisasi daftar slot parkir beserta koordinatnya
// ============================================================
static void tambah(string blok, int no, int x, int y) {
    daftar_slot[jumlah_slot++] = {blok, no, x, y, false, 0};
}

void init_slot() {
    for (int i = 0; i < 5; i++) tambah("A", i+1, i,   2);
    for (int i = 0; i < 5; i++) tambah("B", i+1, i,   4);
    for (int i = 0; i < 5; i++) tambah("C", i+1, i,   6);
    for (int i = 0; i < 5; i++) tambah("D", i+1, i+8, 6);
    for (int i = 0; i < 5; i++) tambah("E", i+1, i,   8);
    for (int i = 0; i < 5; i++) tambah("F", i+1, i+8, 8);
    for (int i = 0; i < 5; i++) tambah("G", i+1, i,   10);
    for (int i = 0; i < 5; i++) tambah("H", i+1, i+8, 10);
    for (int i = 0; i < 5; i++) tambah("I", i+1, i,   12);
    for (int i = 0; i < 5; i++) tambah("J", i+1, i+8, 12);
    for (int i = 0; i < 8; i++) tambah("K", i+1, i,   14);
}
