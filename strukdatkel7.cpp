#include <iostream>
#include <vector>
#include <fstream>
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

    stokbuku.push_back(buku);
    cout << "Buku " << buku.judul << " sebanyak " << buku.stok << " buah berhasil ditambahkan ke dalam stok buku!\n";
    cout << "=============================================\n";
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
    }

    inputFile.close();

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
                            cout << "Menu tidak tersedia\n";
                    }
                } while (pilihan != 5);
                break;

            case 2:
                cout << "Anda masuk sebagai Customer!\n\n";
                cout << "=============================================\n";
                break;
            default:
                
                break;
        }    
    } while (login != 3);

    return 0;
}
