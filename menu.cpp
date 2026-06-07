// ============================================================
//  menu.cpp — Implementasi Menu Sistem SIMASI-PARKIR
// ============================================================
#include "menu.h"
#include "data.h"
#include "quicksort.h"
#include "bfs.h"
#include <iostream>
#include <cmath>
using namespace std;

// ============================================================
//  Tampil Peta Parkir (Grid 2D)
// ============================================================
void tampil_peta() {
    cout << "\n  === PETA PARKIR FASILKOM UNEJ ===\n";
    cout << "  O=Jalan  F=Slot Kosong  T=Slot Terisi  1=Bangunan\n\n";
    cout << "     ";
    for (int x = 0; x < KOLOM; x++)
        cout << (x+1 < 10 ? " " : "") << (x+1) << " ";
    cout << "\n";
    for (int y = BARIS-1; y >= 0; y--) {
        cout << " " << (y+1 < 10 ? " " : "") << (y+1) << " [";
        for (int x = 0; x < KOLOM; x++) cout << " " << grid[y][x] << " ";
        cout << "]\n";
    }
}

// ============================================================
//  Cek apakah plat sudah terparkir (cegah duplikat)
// ============================================================
static bool plat_duplikat(const string& plat) {
    for (int i = 0; i < jumlah_kendaraan; i++)
        if (daftar_kendaraan[i].plat == plat) return true;
    return false;
}

// ============================================================
//  Menu 1 - Registrasi Kendaraan Masuk
//  Alur: Input plat -> Quick Sort slot -> BFS navigasi -> Simpan
// ============================================================
void menu_masuk() {
    cout << "\n========== REGISTRASI KENDARAAN MASUK ==========\n";
    string plat;
    cout << "Masukkan nomor plat kendaraan: ";
    cin >> plat;

    if (plat_duplikat(plat)) {
        cout << "[!] Error: Plat " << plat << " sudah terparkir.\n";
        return;
    }

    // Kumpulkan slot kosong + hitung jarak Manhattan
    Slot kosong[MAX_SLOT];
    int n = 0;
    for (int i = 0; i < jumlah_slot; i++) {
        if (!daftar_slot[i].terisi) {
            daftar_slot[i].jarak = abs(daftar_slot[i].x - GX)
                                 + abs(daftar_slot[i].y - GY);
            kosong[n++] = daftar_slot[i];
        }
    }
    if (n == 0) { cout << "[!] Area Parkir Sedang Penuh.\n"; return; }

    // Quick Sort -> slot[0] adalah yang terdekat
    quick_sort_slot(kosong, 0, n - 1);
    Slot rec = kosong[0];

    cout << "\n[*] Slot Rekomendasi : Blok " << rec.id_blok << "-" << rec.nomor
         << " | Koordinat (x=" << rec.x+1 << ", y=" << rec.y+1
         << ") | Jarak=" << rec.jarak << "\n";

    // BFS: tampilkan rute dari gerbang ke slot rekomendasi
    vector<Titik> jalur = cari_rute_BFS(rec.x, rec.y);
    cetak_instruksi(jalur);

    // Update status slot dan peta
    for (int i = 0; i < jumlah_slot; i++)
        if (daftar_slot[i].x == rec.x && daftar_slot[i].y == rec.y)
            { daftar_slot[i].terisi = true; break; }
    grid[rec.y][rec.x] = 'T';

    // Simpan kendaraan lalu Quick Sort by plat agar Binary Search bisa jalan
    daftar_kendaraan[jumlah_kendaraan++] = {plat, rec.x, rec.y, rec.id_blok, rec.nomor};
    if (jumlah_kendaraan > 1)
        quick_sort_kendaraan(daftar_kendaraan, 0, jumlah_kendaraan - 1);

    cout << "[OK] Kendaraan " << plat << " parkir di Blok "
         << rec.id_blok << "-" << rec.nomor << ".\n";
}

// ============================================================
//  Menu 2 - Cari Lokasi Kendaraan (Binary Search)
// ============================================================
void menu_cari() {
    cout << "\n========== PENCARIAN LOKASI KENDARAAN ==========\n";
    if (jumlah_kendaraan == 0) { cout << "[!] Belum ada kendaraan terparkir.\n"; return; }
    string plat;
    cout << "Masukkan nomor plat kendaraan: ";
    cin >> plat;

    int idx = binary_search_kendaraan(plat);
    if (idx == -1) {
        cout << "[!] Data tidak ditemukan. Periksa kembali nomor plat.\n";
    } else {
        Kendaraan& k = daftar_kendaraan[idx];
        cout << "[OK] Kendaraan ditemukan di Blok " << k.blok
             << ", Slot " << k.nomor_slot
             << " (Koordinat x=" << k.x+1 << ", y=" << k.y+1 << ")\n";
    }
}

// ============================================================
//  Menu 3 - Registrasi Kendaraan Keluar
//  Alur: Binary Search -> bebaskan slot -> hapus data (array shift)
// ============================================================
void menu_keluar() {
    cout << "\n========== REGISTRASI KENDARAAN KELUAR ==========\n";
    if (jumlah_kendaraan == 0) { cout << "[!] Tidak ada kendaraan di area parkir.\n"; return; }
    string plat;
    cout << "Masukkan nomor plat kendaraan yang keluar: ";
    cin >> plat;

    int idx = binary_search_kendaraan(plat);
    if (idx == -1) { cout << "[!] Validasi Gagal! Kendaraan tidak terdata.\n"; return; }

    int kx = daftar_kendaraan[idx].x, ky = daftar_kendaraan[idx].y;

    // Bebaskan slot di peta dan daftar_slot
    grid[ky][kx] = 'F';
    for (int i = 0; i < jumlah_slot; i++)
        if (daftar_slot[i].x == kx && daftar_slot[i].y == ky)
            { daftar_slot[i].terisi = false; break; }

    // Hapus kendaraan dengan Array Shifting
    for (int j = idx; j < jumlah_kendaraan - 1; j++)
        daftar_kendaraan[j] = daftar_kendaraan[j+1];
    jumlah_kendaraan--;

    cout << "[OK] Kendaraan " << plat << " keluar. Slot dikosongkan.\n";
}

// ============================================================
//  Menu 4 - Tampil Daftar Kendaraan Terparkir
// ============================================================
void menu_daftar() {
    cout << "\n========== DAFTAR KENDARAAN TERPARKIR ==========\n";
    if (jumlah_kendaraan == 0) { cout << "  (Belum ada kendaraan)\n"; return; }
    cout << "  No | Plat        | Blok | Slot | Koordinat\n";
    cout << "  ---|-------------|------|------|----------\n";
    for (int i = 0; i < jumlah_kendaraan; i++) {
        Kendaraan& k = daftar_kendaraan[i];
        cout << "  " << (i+1 < 10 ? " " : "") << i+1
             << " | " << k.plat << string(11 - k.plat.size(), ' ')
             << " | " << k.blok << "    | " << k.nomor_slot
             << "    | (" << k.x+1 << "," << k.y+1 << ")\n";
    }
}
