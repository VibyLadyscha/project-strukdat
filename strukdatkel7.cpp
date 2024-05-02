#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

#define size 1000
#define h(k) k % size

// Struct untuk menyimpan data barang
struct Buku {
    string kategori;
    string genre;
    string judul;
    string penulis;
    string penerbit;
    int harga;
    int stok;
};

// Struct untuk menyimpan data key dan isinya dalam hash table
struct NodeHash {
    string key;
    Buku* buku;
    NodeHash* next;
};

struct NodeHash* chain[size][size];

// Fungsi untuk menambahkan barang baru ke dalam sistem stok barang
void tambahBuku(vector<Buku> &stokbuku) {
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

    stokbuku.push_back(buku); // Menambahkan buku ke dalam stok buku
    insertHash(buku.kategori, &stokbuku.back()); // Menambahkan buku ke dalam hash table dengan key kategori
    insertHash(buku.judul, &stokbuku.back()); // Menambahkan buku ke dalam hash table dengan key judul
    insertHash(buku.penulis, &stokbuku.back()); // Menambahkan buku ke dalam hash table dengan key penulis

    cout << "Buku " << buku.judul << " sebanyak " << buku.stok << " buah berhasil ditambahkan ke dalam stok buku!\n";
    cout << "=============================================\n";
}

// Membuat kerangka hash table
void init() { // Inisialisasi hash table
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            chain[i][j] = NULL;
        }
    }
}

int keyToValue(string key) { // Mengubah key menjadi value
    int n = key.length();
    int i;
    int radix128 = 0;
    for (i = 0; i < n; i++) {
        radix128 += key[n - 1 - i] * pow(128, i);
    }
    return radix128;
}

void insertHash(string key, Buku* buku) { // Memasukkan data ke dalam hash table
    int idx = h(keyToValue(key));

    NodeHash* temp = chain[idx][0];
    while (temp != NULL) {
        
        if (temp->key == key) {
            // Jika kunci sudah ada, maka tambahkan ke dalam linked list
            while (temp->next != NULL) {
                temp = temp->next;
            }
            NodeHash* newNode = new NodeHash;
            newNode->key = key;
            newNode->buku = buku;
            newNode->next = NULL;
            temp->next = newNode;
            return;
        }
        temp = temp->next;
    }

    for (int i = 0; i < size; i++) {
        if (chain[idx][i] == NULL) {
            NodeHash* newNode = new NodeHash;
            newNode->key = key;
            newNode->buku = buku;
            newNode->next = NULL;
            chain[idx][i] = newNode;
            return;
        }
    }

}

void updateHash(string key, int stok) { // Mengupdate stok buku dalam hash table
    int idx = h(keyToValue(key));

    NodeHash* temp = chain[idx][0];
    while (temp && temp->key != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    temp->buku->stok = stok;
}

void deleteHash(string key) { // Menghapus data dari hash table
    int idx = h(keyToValue(key));

    NodeHash* temp = chain[idx][0];
    NodeHash* prev = temp;

    while (temp != NULL && temp->key != key) { // Mencari key yang akan dihapus
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) { // Jika key tidak ditemukan
        return;
    }

    if (temp == chain[idx][0]) { // Jika node yang akan dihapus berada di head
        chain[idx][0] = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
}

// Fungsi untuk mencari buku berdasarkan kategori


int main() {
    vector<Buku> stokbuku;
    // Menambahkan buku dari input file
    ifstream inputFile("default stock.txt");
    Buku buku;

    while (getline(inputFile, buku.kategori, '\t') &&
           getline(inputFile, buku.genre, '\t') &&
           getline(inputFile, buku.judul, '\t') &&
           getline(inputFile, buku.penulis, '\t') &&
           getline(inputFile, buku.penerbit, '\t') &&
           inputFile >> buku.harga >> buku.stok) {
        inputFile.ignore(); // Mengabaikan karakter newline yang tersisa di buffer
        stokbuku.push_back(buku);
        insertHash(buku.kategori, &stokbuku.back()); // Menambahkan buku ke dalam hash table dengan key kategori
        insertHash(buku.judul, &stokbuku.back()); // Menambahkan buku ke dalam hash table dengan key judul
        insertHash(buku.penulis, &stokbuku.back()); // Menambahkan buku ke dalam hash table dengan key penulis
    }

    inputFile.close();

    int pilihan, login;

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
                cout << "Anda masuk sebagai Admin.\n";
                cout << "=============================================\n\n";
                do {
                    cout << "=============================================\n";
                    cout << "Silakan pilih menu yang tersedia:\n";
                    cout << "=============================================\n";
                    cout << "1. Tambah buku\n"; // admin
                    cout << "2. Pembaruan stok buku setelah transaksi\n"; // admin, nambah stok
                    cout << "3. Cari buku\n";
                    cout << "4. Menampilkan seluruh stok buku\n"; // customer dan admin
                    cout << "5. Kembali\n"; // keluar dari menu admin
                    cout << "Pilihan: ";

                    cin >> pilihan;

                    switch (pilihan) {
                        case 1:
                            // Tambah buku
                            tambahBuku(stokbuku);
                            break;
                        case 2:
                            // Pembaruan stok buku setelah transaksi
                            cout << "Masukkan judul buku yang akan diupdate: ";
                            break;
                        case 3:
                            // Cari buku
                            cout << "Cari buku berdasarkan: \n";
                            cout << "1. Kategori\n";
                            cout << "2. Judul\n";
                            cout << "3. Penulis\n";
                            cout << "4. Range Harga\n";
                            cout << "5. Kembali\n";
                            break;
                        case 4:
                            // Menampilkan seluruh stok buku
                            cout << "Menampilkan seluruh stok buku";
                            break;
                        case 5:
                            // Kembali ke menu utama
                            break;
                        default:
                            cout << "Menu tidak tersedia!\n";
                    }
                } while (pilihan != 5);
                break;

            case 2:
                cout << "Anda masuk sebagai Customer.\n\n";
                cout << "=============================================\n";
                break;

            case 3:
                cout << "Terima kasih, sampai jumpa!\n";
                break;
            default:
                cout << "Menu tidak tersedia!\n";
                break;
        }    
    } while (login != 3);

    return 0;
}
