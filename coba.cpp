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

// Membuat tiga hash table terpisah untuk kategori, judul, dan penulis
struct NodeHash* chainKategori[size];
struct NodeHash* chainJudul[size];
struct NodeHash* chainPenulis[size];

// Menginisialisasi ketiga hash table
void init() {
    int i;
    for (i = 0; i < size; i++) {
        chainKategori[i] = NULL;
        chainJudul[i] = NULL;
        chainPenulis[i] = NULL;
    }
}


int keyToValue(string key) { // Mengubah key menjadi value
    int n = key.length();
    int i;
    int radix8 = 0;
    for (i = 0; i < n; i++) {
        radix8 += key[n - 1 - i] * pow(8, i);
    }
    return radix8;
}

void insertHash(string key, Buku* buku, NodeHash* chain[]) { // Memasukkan data ke dalam hash table
    int idx = h(keyToValue(key));

    if (chain[idx] == NULL) {
        // Jika tidak ada data di indeks hash tersebut, langsung masukkan
        NodeHash* newNode = new NodeHash;
        newNode->key = key;
        newNode->buku = buku;
        newNode->next = NULL;
        chain[idx] = newNode;
    } else {
        // Jika ada data di indeks hash tersebut
        NodeHash* temp = chain[idx];
        // Cek apakah key yang sama sudah ada di indeks tersebut
        while (temp != NULL) {
            if (temp->key == key) {
                // Jika key yang sama sudah ada, gunakan chaining untuk menyimpan data tambahan
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
        // Jika tidak ada key yang sama, gunakan open addressing untuk mencari lokasi yang tepat
        int nextIdx = (idx + 1) % size;
        while (nextIdx != idx) {
            if (chain[nextIdx] == NULL) {
                NodeHash* newNode = new NodeHash;
                newNode->key = key;
                newNode->buku = buku;
                newNode->next = NULL;
                chain[nextIdx] = newNode;
                return;
            }
            nextIdx = (nextIdx + 1) % size;
        }
        // Jika tidak ada ruang kosong, pesan kesalahan
        //cout << "Hash table penuh.\n";
    }
}

NodeHash* searchHash(string key, NodeHash* chain[]) { // Mencari data berdasarkan key dalam hash table
    int idx = h(keyToValue(key));
    NodeHash* temp = chain[idx];
    while (temp != NULL) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void updateHash(string key, int stok, NodeHash* chain[]) { // Mengupdate stok buku dalam hash table
    NodeHash* node = searchHash(key, chain);
    if (node != NULL) {
        node->buku->stok = stok;
    }
}

void deleteHash(string key,  NodeHash* chain[]) { // Menghapus data dari hash table
    int idx = h(keyToValue(key));

    NodeHash* temp = chain[idx];
    NodeHash* prev = NULL;

    while (temp != NULL && temp->key != key) { // Mencari key yang akan dihapus
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) { // Jika key tidak ditemukan
        return;
    }

    if (prev == NULL) { // Jika node yang akan dihapus berada di head
        chain[idx] = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
}

// Fungsi untuk menambahkan barang baru ke dalam sistem stok barang
void tambahBuku(vector<Buku> &stokbuku, NodeHash* chainKategori[], NodeHash* chainJudul[], NodeHash* chainPenulis[]) {
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
    insertHash(buku.kategori, &stokbuku.back(), chainKategori); // Menambahkan buku ke dalam hash table dengan key kategori
    insertHash(buku.judul, &stokbuku.back(), chainJudul); // Menambahkan buku ke dalam hash table dengan key judul
    insertHash(buku.penulis, &stokbuku.back(), chainPenulis); // Menambahkan buku ke dalam hash table dengan key penulis

    cout << "Buku " << buku.judul << " sebanyak " << buku.stok << " buah berhasil ditambahkan ke dalam stok buku!\n";
    cout << "=============================================\n";
}

// Fungsi untuk mencari buku berdasarkan kategori


int main() {
    vector<Buku> stokbuku;
    // Menambahkan buku dari input file
    ifstream inputFile("defaultstock.txt");
    Buku buku;

    while (getline(inputFile, buku.kategori, '\t') &&
           getline(inputFile, buku.genre, '\t') &&
           getline(inputFile, buku.judul, '\t') &&
           getline(inputFile, buku.penulis, '\t') &&
           getline(inputFile, buku.penerbit, '\t') &&
           inputFile >> buku.harga >> buku.stok) {
        inputFile.ignore(); // Mengabaikan karakter newline yang tersisa di buffer
        stokbuku.push_back(buku);
        insertHash(buku.kategori, &stokbuku.back(), chainKategori); // Menambahkan buku ke dalam hash table dengan key kategori
        insertHash(buku.judul, &stokbuku.back(), chainJudul); // Menambahkan buku ke dalam hash table dengan key judul
        insertHash(buku.penulis, &stokbuku.back(), chainPenulis); // Menambahkan buku ke dalam hash table dengan key penulis
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
                            tambahBuku(stokbuku, chainKategori, chainJudul, chainPenulis);
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