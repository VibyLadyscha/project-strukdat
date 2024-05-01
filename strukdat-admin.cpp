#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Struktur data untuk menyimpan data barang
struct Buku {
    string kategori;
    string genre;
    string judul;
    string penulis;
    string penerbit;
    int harga;
    int stok;
};

// Node untuk linked list -- print buku berdasarkan kategori
struct Node {
    Buku data;
    Node* next;
    Node(const Buku& item) : data(item), next(nullptr) {}
};

// Fungsi untuk menambahkan node baru ke dalam linked list secara berurutan berdasarkan kategori
void addNewNode(Node*& head, const Buku& item) {
    Node* newNode = new Node(item);
    if (!head || item.kategori < head->data.kategori) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next && current->next->data.kategori < item.kategori) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Fungsi untuk menghapus semua node pada linked list
void deleteNode(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Fungsi untuk menampilkan stok buku berdasarkan kategori
void showLinkedList(Node* head, const string& kategori) {
    cout << "Daftar buku dalam kategori '" << kategori << "':\n";
    while (head) {
        if (head->data.kategori == kategori) {
            cout << "Judul: " << head->data.judul << ", Stok: " << head->data.stok << endl;
        }
        head = head->next;
    }
}

// Fungsi untuk menambahkan barang baru ke dalam sistem
void tambahBuku(vector<Buku>& stokbuku, Node*& head) {
    Buku buku;
    cout << "\tMasukkan kategori buku: ";
    cin >> buku.kategori;
    cout << "\tMasukkan genre buku: ";
    cin >> buku.genre;
    cin.ignore();  // Mengabaikan karakter newline yang tersisa di buffer    
    cout << "\tMasukkan judul buku: ";
    getline(cin, buku.judul);
    cout << "\tMasukkan penulis buku: ";
    cin >> buku.penulis;
    cin.ignore();  // Mengabaikan karakter newline yang tersisa di buffer 
    cout << "\tMasukkan penerbit buku: ";
    getline(cin, buku.penerbit);
    cout << "\tMasukkan harga buku: Rp";
    cin >> buku.harga;
    cout << "\tMasukkan stok buku: ";
    cin >> buku.stok;

    stokbuku.push_back(buku);
    addNewNode(head, buku);
    cout << "Buku " << buku.judul << " sebanyak " << buku.stok << " buah berhasil ditambahkan ke dalam stok buku!\n";
    cout << "=============================================\n";
}

int main() {
    vector<Buku> stokbuku;
    Node* head = nullptr; // Head pointer untuk linked list
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
                    cout << "1. Tambah buku\n"; // admin
                    cout << "2. Pembaruan stok buku setelah transaksi\n"; // admin, nambah stok
                    cout << "3. Cari buku\n";
                    cout << "4. Menampilkan seluruh stok buku\n"; // customer dan admin
                    cout << "5. Menampilkan stok buku berdasarkan kategori\n"; // admin
                    cout << "6. Kembali\n"; // keluar dari menu admin
                    cout << "Pilihan: ";

                    cin >> pilihan;

                    switch (pilihan) {
                        case 1:
                            // Tambah buku
                            tambahBuku(stokbuku, head);
                            break;
                        case 2:
                            // Pembaruan stok buku setelah transaksi
                            updateStokBuku(stokbuku);
                            break;
                        case 3:
                            // Cari buku
                            // Implementasi di sini
                            break;
                        case 4:
                            // Menampilkan seluruh stok buku
                            for (const auto &buku : stokbuku) {
                                showDetail(buku);
                            }
                            break;
                        case 5:
                            // Menampilkan stok buku berdasarkan kategori
                            cout << "Masukkan kategori buku: ";
                            string kategori;
                            cin >> kategori;
                            showLinkedList(head, kategori);
                            break;
                        case 6:
                            // Kembali ke menu utama
                            break;

                        default:
                            cout << "Menu tidak tersedia";
                    }
                } while (pilihan != 6);
                break;
            case 2:
                // Menu untuk customer
                break;
            case 3:
                cout << "Terima kasih, sampai jumpa!";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
    } while (login != 3);

    // Hapus semua node pada linked list
    deleteNode(head);

    return 0;
}
