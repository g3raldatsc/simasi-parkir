// ============================================================
//  main.cpp — Entry Point SIMASI-PARKIR
//  Sistem Manajemen dan Navigasi Parkir - Fasilkom Unej
//  Algoritma: Quick Sort | BFS | Binary Search
// ============================================================
#include "data.h"
#include "menu.h"
#include <iostream>
using namespace std;

int main() {
    init_grid();  // Inisialisasi peta 2D
    init_slot();  // Inisialisasi data slot parkir

    int pilihan;
    do {
        cout << "\n====================================================\n";
        cout << "          SIMASI-PARKIR - Fasilkom Unej             \n";
        cout << "====================================================\n";
        cout << "  1. Registrasi Kendaraan Masuk\n";
        cout << "  2. Cari Lokasi Kendaraan\n";
        cout << "  3. Registrasi Kendaraan Keluar\n";
        cout << "  4. Tampil Peta Parkir\n";
        cout << "  5. Tampil Daftar Kendaraan\n";
        cout << "  6. Keluar dari Sistem\n";
        cout << "----------------------------------------------------\n";
        cout << "  Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: menu_masuk();  break;
            case 2: menu_cari();   break;
            case 3: menu_keluar(); break;
            case 4: tampil_peta(); break;
            case 5: menu_daftar(); break;
            case 6: cout << "\n[SIMASI-PARKIR] Sistem dimatikan. Terima kasih.\n"; break;
            default: cout << "\n[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}
