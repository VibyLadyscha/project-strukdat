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

// Fungsi untuk mencari buku

int main() {
    vector<Buku> stokbuku;
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
                            // Kembali ke menu utama
                            break;
                        default:
                            cout << "Menu tidak tersedia";
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

    return 0;
}
