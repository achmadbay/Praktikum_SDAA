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

struct Stack {
    Sepatu* top;
};

struct Queue {
    Sepatu* front;
    Sepatu* rear;
};

void tambahSepatu(Sepatu** head, int* idCounter);
void tampilkanSepatu(Sepatu* head);
void updateSepatu(Sepatu* head);
void hapusSepatu(Sepatu** head);
void inisialisasiSepatu(Sepatu** head, int* idCounter);
void clearInput();

void push(Stack* stack, Sepatu* newSepatu);
Sepatu* pop(Stack* stack);
void displayStack(Stack* stack);

void enqueue(Queue* queue, Sepatu* newSepatu);
Sepatu* dequeue(Queue* queue);
void displayQueue(Queue* queue);

Sepatu* mergeSort(Sepatu* head);
Sepatu* sortedMerge(Sepatu* a, Sepatu* b);
void frontBackSplit(Sepatu* source, Sepatu** frontRef, Sepatu** backRef);

Sepatu* quickSort(Sepatu* head);
Sepatu* partition(Sepatu* head, Sepatu** newHead, Sepatu** newEnd);
Sepatu* getTail(Sepatu* current);

int main() {
    Sepatu* head = nullptr;
    int idCounter = 0;
    int pilihan;
    inisialisasiSepatu(&head, &idCounter);

    Stack stack = {nullptr};
    Queue queue = {nullptr, nullptr};

    do {
        cout << "\n===== Menu Manajemen Toko Sepatu =====" << endl;
        cout << "1. Tambah Sepatu" << endl;
        cout << "2. Tampilkan Semua Sepatu" << endl;
        cout << "3. Update Sepatu" << endl;
        cout << "4. Hapus Sepatu" << endl;
        cout << "5. Push ke Stack" << endl;
        cout << "6. Pop dari Stack" << endl;
        cout << "7. Enqueue ke Queue" << endl;
        cout << "8. Dequeue dari Queue" << endl;
        cout << "9. Tampilkan Stack" << endl;
        cout << "10. Tampilkan Queue" << endl;
        cout << "11. Sorting Ascending (Merge Sort)" << endl;
        cout << "12. Sorting Descending (Quick Sort)" << endl;
        cout << "13. Keluar" << endl;
        cout << "Pilih opsi (1-13): ";
        cin >> pilihan;

        if (cin.fail()) {
            clearInput();
            cout << "Input tidak valid! Masukkan angka antara 1 hingga 13." << endl;
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
        case 5: {
            Sepatu* newSepatu = new Sepatu();
            tambahSepatu(&newSepatu, &idCounter);
            push(&stack, newSepatu);
            break;
        }
        case 6: {
            Sepatu* poppedSepatu = pop(&stack);
            if (poppedSepatu) {
                cout << "Sepatu diambil dari Stack: " << poppedSepatu->nama << endl;
                delete poppedSepatu;
            } else {
                cout << "Stack kosong!" << endl;
            }
            break;
        }
        case 7: {
            Sepatu* newSepatu = new Sepatu();
            tambahSepatu(&newSepatu, &idCounter);
            enqueue(&queue, newSepatu);
            break;
        }
        case 8: {
            Sepatu* dequeuedSepatu = dequeue(&queue);
            if (dequeuedSepatu) {
                cout << "Sepatu diambil dari Queue: " << dequeuedSepatu->nama << endl;
                delete dequeuedSepatu;
            } else {
                cout << "Queue kosong!" << endl;
            }
            break;
        }
        case 9:
            displayStack(&stack);
            break;
        case 10:
            displayQueue(&queue);
            break;
        case 11:
            head = mergeSort(head);
            cout << "Sepatu berhasil diurutkan secara ascending menggunakan Merge Sort!" << endl;
            break;
        case 12:
            head = quickSort(head); 
            cout << "Sepatu berhasil diurutkan secara descending menggunakan Quick Sort!" << endl;
            break; 
        case 13:
            cout << "Keluar dari program." << endl;
            break; 
        default:
            cout << "Pilihan tidak valid! Pilih opsi antara 1 hingga 13." << endl;
    }

    } while (pilihan != 13);

    return 0;
}

Sepatu* mergeSort(Sepatu* head) {
    if (!head || !head->next)
        return head;

    Sepatu* a;
    Sepatu* b;

    frontBackSplit(head, &a, &b);

    a = mergeSort(a);
    b = mergeSort(b);

    return sortedMerge(a, b);
}

Sepatu* sortedMerge(Sepatu* a, Sepatu* b) {
    if (!a)
        return b;
    if (!b)
        return a;

    Sepatu* result = nullptr;

    if (a->harga <= b->harga) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void frontBackSplit(Sepatu* source, Sepatu** frontRef, Sepatu** backRef) {
    Sepatu* fast;
    Sepatu* slow;
    slow = source;
    fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

Sepatu* quickSort(Sepatu* head) {
    if (!head || !head->next)  
        return head;

    Sepatu* newHead = nullptr;
    Sepatu* newEnd = nullptr;

    Sepatu* pivot = partition(head, &newHead, &newEnd);

    if (newHead != pivot) {
        Sepatu* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSort(newHead);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSort(pivot->next);

    return newHead;
}

Sepatu* partition(Sepatu* head, Sepatu** newHead, Sepatu** newEnd) {
    Sepatu* pivot = head;
    Sepatu* prev = nullptr;
    Sepatu* current = head->next;
    Sepatu* tail = pivot;

    while (current) {
        Sepatu* next = current->next;
        if (current->harga > pivot->harga) {
            if (prev) {
                prev->next = current->next;
            }
            current->next = *newHead;
            *newHead = current;
        } else {
            if (!prev) {
                *newHead = pivot;
            } else {
                prev->next = current;
            }
            prev = current;
        }
        current = next;
    }

    if (!prev) {
        *newEnd = pivot;
    } else {
        prev->next = nullptr;
        *newEnd = prev;
    }

    return pivot;
}


Sepatu* getTail(Sepatu* current) {
    while (current != nullptr && current->next != nullptr)
        current = current->next;
    return current;
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
    Sepatu* sepatu1 = new Sepatu{++(*idCounter), "Nike Air Max", 1500000, nullptr};
    Sepatu* sepatu2 = new Sepatu{++(*idCounter), "Adidas Ultraboost", 1700000, nullptr};
    Sepatu* sepatu3 = new Sepatu{++(*idCounter), "Converse Chuck Taylor", 900000, nullptr};
    Sepatu* sepatu4 = new Sepatu{++(*idCounter), "Vans Old Skool", 800000, nullptr};

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

void push(Stack* stack, Sepatu* newSepatu) {
    newSepatu->next = stack->top;
    stack->top = newSepatu;
    cout << "Sepatu berhasil ditambahkan ke Stack!" << endl;
}

Sepatu* pop(Stack* stack) {
    if (stack->top == nullptr) {
        return nullptr;
    }
    Sepatu* temp = stack->top;
    stack->top = stack->top->next;
    return temp;
}

void displayStack(Stack* stack) {
    if (stack->top == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }

    Sepatu* current = stack->top;
    cout << "\nDaftar Sepatu di Stack:" << endl;
    while (current != nullptr) {
        cout << "ID: " << current->id << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Harga: Rp" << current->harga << endl;
        cout << "-------------------------" << endl;
        current = current->next;
    }
}

void enqueue(Queue* queue, Sepatu* newSepatu) {
    newSepatu->next = nullptr;
    if (queue->rear == nullptr) {
        queue->front = queue->rear = newSepatu;
    } else {
        queue->rear->next = newSepatu;
        queue->rear = newSepatu;
    }
    cout << "Sepatu berhasil ditambahkan ke Queue!" << endl;
}

Sepatu* dequeue(Queue* queue) {
    if (queue->front == nullptr) {
        return nullptr;
    }
    Sepatu* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }
    return temp;
}

void displayQueue(Queue* queue) {
    if (queue->front == nullptr) {
        cout << "Queue kosong!" << endl;
        return;
    }

    Sepatu* current = queue->front;
    cout << "\nDaftar Sepatu di Queue:" << endl;
    while (current != nullptr) {
        cout << "ID: " << current->id << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Harga: Rp" << current->harga << endl;
        cout << "-------------------------" << endl;
        current = current->next;
    }
}
