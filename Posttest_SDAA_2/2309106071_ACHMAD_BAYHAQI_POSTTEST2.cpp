#include <iostream>
#include <string>
#include <limits> 

using namespace std;

const int MAX_SEPATU = 100;
struct Sepatu {
    int id;
    string nama;
    double harga;
};

void tambahSepatu(Sepatu* daftarSepatu, int* jumlahSepatu);
void tampilkanSepatu(Sepatu* daftarSepatu, int jumlahSepatu);
void updateSepatu(Sepatu* daftarSepatu, int jumlahSepatu);
void hapusSepatu(Sepatu* daftarSepatu, int* jumlahSepatu);
void inisialisasiSepatu(Sepatu* daftarSepatu, int* jumlahSepatu);
void clearInput(); 

int main() {
    Sepatu daftarSepatu[MAX_SEPATU];  
    int jumlahSepatu = 0;             
    int pilihan;
    inisialisasiSepatu(daftarSepatu, &jumlahSepatu);

    do {
        cout << "\n===== Menu Manajemen Toko Sepatu =====" << endl;
        cout << "1. Tambah Sepatu" << endl;
        cout << "2. Tampilkan Semua Sepatu" << endl;
        cout << "3. Update Sepatu" << endl;
        cout << "4. Hapus Sepatu" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        if (cin.fail()) {
            clearInput();  // Tangani error input
            cout << "Input tidak valid! Masukkan angka antara 1 hingga 5." << endl;
            continue;
        }
        switch (pilihan) {
            case 1:
                tambahSepatu(daftarSepatu, &jumlahSepatu);
                break;
            case 2:
                tampilkanSepatu(daftarSepatu, jumlahSepatu);
                break;
            case 3:
                updateSepatu(daftarSepatu, jumlahSepatu);
                break;
            case 4:
                hapusSepatu(daftarSepatu, &jumlahSepatu);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Pilih opsi antara 1 hingga 5." << endl;
        }
    } while (pilihan != 5);

    return 0;
}

void tambahSepatu(Sepatu* daftarSepatu, int* jumlahSepatu) {
    if (*jumlahSepatu >= MAX_SEPATU) {
        cout << "Tidak dapat menambah sepatu. Kapasitas penuh!" << endl;
        return;
    }
    Sepatu sepatuBaru;
    sepatuBaru.id = *jumlahSepatu + 1;
    cout << "Masukkan nama sepatu: ";
    cin.ignore(); 
    getline(cin, sepatuBaru.nama);

    cout << "Masukkan harga sepatu: ";
    cin >> sepatuBaru.harga;

    if (cin.fail()) {
        clearInput();
        cout << "Input harga tidak valid! Masukkan angka." << endl;
        return;
    }
    daftarSepatu[*jumlahSepatu] = sepatuBaru;
    (*jumlahSepatu)++;
    cout << "Sepatu berhasil ditambahkan!" << endl;
}

void tampilkanSepatu(Sepatu* daftarSepatu, int jumlahSepatu) {
    if (jumlahSepatu == 0) {
        cout << "Belum ada sepatu yang ditambahkan." << endl;
        return;
    }
    cout << "\nDaftar Sepatu:" << endl;
    for (int i = 0; i < jumlahSepatu; i++) {
        cout << "ID: " << daftarSepatu[i].id << endl;
        cout << "Nama: " << daftarSepatu[i].nama << endl;
        cout << "Harga: Rp" << daftarSepatu[i].harga << endl;
        cout << "-------------------------" << endl;
    }
}

void updateSepatu(Sepatu* daftarSepatu, int jumlahSepatu) {
    int id;
    cout << "Masukkan ID sepatu yang ingin diupdate: ";
    cin >> id;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid! Masukkan ID yang benar." << endl;
        return;
    }
    if (id < 1 || id > jumlahSepatu) {
        cout << "ID sepatu tidak ditemukan!" << endl;
        return;
    }
    Sepatu* sepatu = &daftarSepatu[id - 1];
    cout << "Masukkan nama sepatu baru: ";
    cin.ignore();
    getline(cin, sepatu->nama);

    cout << "Masukkan harga sepatu baru: ";
    cin >> sepatu->harga;

    if (cin.fail()) {
        clearInput();
        cout << "Input harga tidak valid! Masukkan angka." << endl;
        return;
    }
    cout << "Data sepatu berhasil diperbarui!" << endl;
}

void hapusSepatu(Sepatu* daftarSepatu, int* jumlahSepatu) {
    int id;
    cout << "Masukkan ID sepatu yang ingin dihapus: ";
    cin >> id;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid! Masukkan ID yang benar." << endl;
        return;
    }
    if (id < 1 || id > *jumlahSepatu) {
        cout << "ID sepatu tidak ditemukan!" << endl;
        return;
    }
    for (int i = id - 1; i < *jumlahSepatu - 1; i++) {
        daftarSepatu[i] = daftarSepatu[i + 1];
    }
    (*jumlahSepatu)--;
    cout << "Sepatu berhasil dihapus!" << endl;
}

void inisialisasiSepatu(Sepatu* daftarSepatu, int* jumlahSepatu) {
    Sepatu sepatu1 = {1, "Nike Air Max", 1500000};
    Sepatu sepatu2 = {2, "Adidas Ultraboost", 1700000};
    Sepatu sepatu3 = {3, "Converse Chuck Taylor", 900000};
    Sepatu sepatu4 = {4, "Vans Old Skool", 800000};

    daftarSepatu[0] = sepatu1;
    daftarSepatu[1] = sepatu2;
    daftarSepatu[2] = sepatu3;
    daftarSepatu[3] = sepatu4;

    *jumlahSepatu = 4;
    cout << "Sepatu default berhasil diinisialisasi!" << endl;
}

void clearInput() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}
