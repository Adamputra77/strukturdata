#include <iostream>
#include <stack>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

stack<string> stackTeks;
stack<string> stackRedo;

void KetikTeks(const string& teks) {
    stackTeks.push(teks);
    stackRedo = stack<string>(); // mengosongkan stack redo
}

void Undo() {
    if (!stackTeks.empty()) {
        stackRedo.push(stackTeks.top());
        stackTeks.pop();
        cout << "Undo berhasil." << endl;
        if (!stackTeks.empty()) {
            cout << "Teks terakhir setelah undo: " << stackTeks.top() << endl;
        } else {
            cout << "Tidak ada teks yang ditambahkan setelah undo." << endl;
        }
    } else {
        cout << "Tidak ada yang bisa di-undo." << endl;
    }
}

void Redo() {
    if (!stackRedo.empty()) {
        stackTeks.push(stackRedo.top());
        stackRedo.pop();
        cout << "Redo berhasil." << endl;
        if (!stackTeks.empty()) {
            cout << "Teks terakhir setelah redo: " << stackTeks.top() << endl;
        } else {
            cout << "Tidak ada teks yang ditambahkan setelah redo." << endl;
        }
    } else {
        cout << "Tidak ada yang bisa di-redo." << endl;
    }
}

bool IsEmptyUndo() {
    return stackTeks.empty();
}

bool IsEmptyRedo() {
    return stackRedo.empty();
}

void TampilkanMenu() {
    cout << "Nama : Adam Putra Pratama" << endl;
    cout << "Nim  : 20230801402" << endl;
    cout << "gmail: adamsap8888@gmail.com" << endl << endl;
    cout << "=== APLIKASI PENGELOLA SEDERHANA ===" << endl;
    cout << "1. Ketik Teks" << endl;
    cout << "2. Undo" << endl;
    cout << "3. Redo" << endl;
    cout << "4. IsEmptyUndo" << endl;
    cout << "5. IsEmptyRedo" << endl;
    cout << "6. Lihat Teks Terakhir" << endl;
    cout << "7. Keluar" << endl;
    cout << "YANG SAMA NYONTEK MATANYA BINTITAN AMPE WISUDA" << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Pilihan: ";
    
}

void TungguDanLanjutkan() {
    cout << "\nTekan enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    system(CLEAR);
}

int main() {
    string operasi, teks;

    do {
        TampilkanMenu();
        cin >> operasi;
        system(CLEAR); // Bersihkan layar

        if (operasi == "1") {
            cout << "Masukkan teks yang ingin diketik: ";
            cin.ignore();
            getline(cin, teks);
            KetikTeks(teks);
            cout << "Teks berhasil ditambahkan." << endl;
        } else if (operasi == "2") {
            Undo();
        } else if (operasi == "3") {
            Redo();
        } else if (operasi == "4") {
            cout << "Stack undo " << (IsEmptyUndo() ? "kosong" : "tidak kosong") << endl;
        } else if (operasi == "5") {
            cout << "Stack redo " << (IsEmptyRedo() ? "kosong" : "tidak kosong") << endl;
        } else if (operasi == "6") {
            if (!stackTeks.empty()) {
                cout << "Teks terakhir: " << stackTeks.top() << endl;
            } else {
                cout << "Tidak ada teks yang ditambahkan." << endl;
            }
        } else if (operasi != "7") {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        
        if (operasi != "7") {
            TungguDanLanjutkan();
        }
        
    } while (operasi != "7");

    return 0;
}