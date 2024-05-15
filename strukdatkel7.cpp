#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string kategori;
    string genre;
    string judul;
    string penulis;
    string penerbit;
    int harga;
    int stok;
};

struct Node {
    Buku buku;
    Node* next;
};

void tambahBuku(Node*& head) {
    Buku buku;
    cout << "\tMasukkan kategori buku: ";
    cin >> buku.kategori;
    cout << "\tMasukkan genre buku: ";
    cin >> buku.genre;
    cin.ignore();  
    cout << "\tMasukkan judul buku: ";
    getline(cin, buku.judul);
    cout << "\tMasukkan penulis buku: ";
    cin >> buku.penulis;
    cin.ignore(); 
    cout << "\tMasukkan penerbit buku: ";
    getline(cin, buku.penerbit);
    cout << "\tMasukkan harga buku: Rp";
    cin >> buku.harga;
    cout << "\tMasukkan stok buku: ";
    cin >> buku.stok;

    Node* newNode = new Node{buku, nullptr};

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << "Buku " << buku.judul << " sebanyak " << buku.stok << " buah berhasil ditambahkan ke dalam stok buku!\n";
    cout << "=============================================\n";
}

// Update stok buku setelah transaksi
void updateStokBuku(Node* head) {
    string judul;
    cout << "Masukkan judul buku yang akan diupdate: ";
    cin.ignore();
    getline(cin, judul);

    Node* temp = head;
    while (temp != nullptr) {
        if (temp->buku.judul == judul) {
            int stokBaru;
            cout << "Stok saat ini untuk buku \"" << temp->buku.judul << "\" adalah " << temp->buku.stok << "\n";
            cout << "Masukkan jumlah stok baru: ";
            cin >> stokBaru;
            temp->buku.stok = stokBaru;
            cout << "Stok buku \"" << temp->buku.judul << "\" berhasil diperbarui menjadi " << temp->buku.stok << "\n";
            cout << "=============================================\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Buku dengan judul \"" << judul << "\" tidak ditemukan dalam stok.\n";
    cout << "=============================================\n";
}

// Print stok buku
void tampilkanSeluruhStokBuku(Node* head) {
    if (head == nullptr) {
        cout << "Stok buku kosong.\n";
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        cout << "Judul: " << temp->buku.judul << ", Stok: " << temp->buku.stok << "\n";
        temp = temp->next;
    }
}

int main() {
    Node* head = nullptr;
    int pilihan;
    int login;

    do {
        cout << "=============================================\n";
        cout << "Selamat datang di sistem manajemen stok buku\n";
        cout << "=============================================\n";
        cout << "Masuk sebagai\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";

        cin >> login;

        switch (login) {
            case 1:
                cout << "Anda masuk sebagai Admin!\n";
                cout << "=============================================\n\n";
                do {
                    cout << "=============================================\n";
                    cout << "Silakan pilih menu yang tersedia:\n";
                    cout << "=============================================\n";
                    cout << "1. Tambah buku\n";
                    cout << "2. Pembaruan stok buku setelah transaksi\n"; 
                    cout << "3. Cari buku\n";
                    cout << "4. Menampilkan seluruh stok buku\n"; 
                    cout << "5. Kembali\n";
                    cout << "Pilihan: ";

                    cin >> pilihan;

                    switch (pilihan) {
                        case 1:
                            tambahBuku(head);
                            break;
                        case 2:
                            updateStokBuku(head);
                            break;
                        case 3:
                            cout << "Cari buku berdasarkan: \n";
                            cout << "1. Kategori\n";
                            cout << "2. Genre\n";
                            cout << "3. Judul\n";
                            cout << "4. Penulis\n";
                            cout << "5. Range Harga\n";
                            cout << "6. Kembali\n";
                            break;
                        case 4:
                            cout << "Menampilkan seluruh stok buku\n";
                            tampilkanSeluruhStokBuku(head);
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Menu tidak tersedia\n";
                    }
                } while (pilihan != 5);
                break;
            case 2:
                cout << "Anda masuk sebagai Customer!\n\n";
                cout << "=============================================\n";
                break;
            default:
                cout << "Menu tidak tersedia!\n\n";
                break;
        }    
    } while (login != 3);

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
