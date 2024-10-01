#include <iostream>
#include <string>
#include <limits> 

using namespace std;

struct Sepatu {
    int id;
    string nama;
    double harga;
    Sepatu* next; 
};


void tambahSepatu(Sepatu** head, int* idCounter);
void tampilkanSepatu(Sepatu* head);
void updateSepatu(Sepatu* head);
void hapusSepatu(Sepatu** head);
void inisialisasiSepatu(Sepatu** head, int* idCounter);
void clearInput(); 

int main() {
    Sepatu* head = nullptr;  
    int idCounter = 0;       
    int pilihan;
    inisialisasiSepatu(&head, &idCounter);

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
            clearInput();  
            cout << "Input tidak valid! Masukkan angka antara 1 hingga 5." << endl;
            continue;
        }

        switch (pilihan) {
            case 1:
                tambahSepatu(&head, &idCounter);
                break;
            case 2:
                tampilkanSepatu(head);
                break;
            case 3:
                updateSepatu(head);
                break;
            case 4:
                hapusSepatu(&head);
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

void tambahSepatu(Sepatu** head, int* idCounter) {
    Sepatu* sepatuBaru = new Sepatu();
    sepatuBaru->id = ++(*idCounter);

    cout << "Masukkan nama sepatu: ";
    cin.ignore();
    getline(cin, sepatuBaru->nama);

    cout << "Masukkan harga sepatu: ";
    cin >> sepatuBaru->harga;

    if (cin.fail()) {
        clearInput();
        cout << "Input harga tidak valid! Masukkan angka." << endl;
        delete sepatuBaru;
        return;
    }

    sepatuBaru->next = *head; 
    *head = sepatuBaru;

    cout << "Sepatu berhasil ditambahkan!" << endl;
}

void tampilkanSepatu(Sepatu* head) {
    if (head == nullptr) {
        cout << "Belum ada sepatu yang ditambahkan." << endl;
        return;
    }

    Sepatu* current = head;
    cout << "\nDaftar Sepatu:" << endl;
    while (current != nullptr) {
        cout << "ID: " << current->id << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Harga: Rp" << current->harga << endl;
        cout << "-------------------------" << endl;
        current = current->next;
    }
}

void updateSepatu(Sepatu* head) {
    int id;
    cout << "Masukkan ID sepatu yang ingin diupdate: ";
    cin >> id;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid! Masukkan ID yang benar." << endl;
        return;
    }

    Sepatu* current = head;
    while (current != nullptr && current->id != id) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "ID sepatu tidak ditemukan!" << endl;
        return;
    }

    cout << "Masukkan nama sepatu baru: ";
    cin.ignore();
    getline(cin, current->nama);

    cout << "Masukkan harga sepatu baru: ";
    cin >> current->harga;

    if (cin.fail()) {
        clearInput();
        cout << "Input harga tidak valid! Masukkan angka." << endl;
        return;
    }

    cout << "Data sepatu berhasil diperbarui!" << endl;
}

void hapusSepatu(Sepatu** head) {
    int id;
    cout << "Masukkan ID sepatu yang ingin dihapus: ";
    cin >> id;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid! Masukkan ID yang benar." << endl;
        return;
    }

    Sepatu* current = *head;
    Sepatu* prev = nullptr;

    while (current != nullptr && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "ID sepatu tidak ditemukan!" << endl;
        return;
    }

    if (prev == nullptr) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    cout << "Sepatu berhasil dihapus!" << endl;
}

void inisialisasiSepatu(Sepatu** head, int* idCounter) {
    Sepatu* sepatu1 = new Sepatu{ ++(*idCounter), "Nike Air Max", 1500000, nullptr };
    Sepatu* sepatu2 = new Sepatu{ ++(*idCounter), "Adidas Ultraboost", 1700000, nullptr };
    Sepatu* sepatu3 = new Sepatu{ ++(*idCounter), "Converse Chuck Taylor", 900000, nullptr };
    Sepatu* sepatu4 = new Sepatu{ ++(*idCounter), "Vans Old Skool", 800000, nullptr };

    sepatu1->next = sepatu2;
    sepatu2->next = sepatu3;
    sepatu3->next = sepatu4;
    sepatu4->next = nullptr;

    *head = sepatu1;

    cout << "Sepatu default berhasil diinisialisasi!" << endl;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
