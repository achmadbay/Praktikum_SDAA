#include <iostream>
using namespace std;


void hanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari " << asal << " ke " << tujuan << endl;
        return;
    }
    
    hanoi(n - 1, asal, sementara, tujuan);
    cout << "Pindahkan piringan " << n << " dari " << asal << " ke " << tujuan << endl;
    hanoi(n - 1, sementara, tujuan, asal);
}

int main() {
    int n = 3;

    cout << "Langkah-langkah untuk menyelesaikan Menara Hanoi dengan " << n << " piringan:" << endl;
    hanoi(n, 'A', 'C', 'B'); // A adalah menara asal, C adalah menara tujuan, B adalah menara sementara

    return 0;
}
