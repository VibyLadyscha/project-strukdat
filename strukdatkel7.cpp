#include <iostream>
#include <vector>
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
    cout << "Masukkan kategori buku: ";
    cin >> buku.kategori;
    cout << "Masukkan genre buku: ";
    cin >> buku.genre;
    cout << "Masukkan judul buku: ";
    cin >> buku.judul;
    cout << "Masukkan penulis buku: ";
    cin >> buku.penulis;
    cout << "Masukkan penerbit buku: ";
    cin >> buku.penerbit;
    cout << "Masukkan harga buku: Rp";
    cin >> buku.harga;
    cout << "Masukkan stok buku: ";
    cin >> buku.stok;

    stokbuku.push_back(buku);
    cout << "Buku " << buku.judul << " sebanyak " << buku.stok << " berhasil ditambahkan ke dalam stok buku!\n";
}

// Fungsi untuk mencari buku

int main() {
    vector<Buku> stokbuku;
    int pilihan;

    cout << "Selamat datang di sistem manajemen stok buku\n";
    
    do {
        cout << "Silakan pilih menu yang tersedia:\n";
        cout << "1. Tambah buku\n"; // admi
        cout << "2. Pembaruan stok buku setelah transaksi\n"; // admin, nambah stok
        cout << "3. Cari buku\n";
        cout << "4. Menampilkan seluruh stok buku\n"; // customer dan admin
        cout << "5. Keluar\n";

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
                cout << "2. Genre\n";
                cout << "3. Judul\n";
                cout << "4. Penulis\n";
                cout << "5. Range Harga\n";
                cout << "6. Kembali\n";
                break;
            case 4:
                // Menampilkan seluruh stok buku
                cout << "Menampilkan seluruh stok buku";
                break;
            case 5:
                // Keluar
                break;
            default:
                cout << "Menu tidak tersedia";
        }
    } while (pilihan != 5);

}