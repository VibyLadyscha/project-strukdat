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

struct Keranjang {
    Buku buku;
    int jumlah;
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

// Fungsi untuk menambahkan barang ke keranjang
void tambahKeKeranjang(vector<Buku> &stokbuku, vector<Keranjang> &keranjang) {
    string judul;
    int jumlah;
    cout << "\tMasukkan judul buku yang ingin ditambahkan ke keranjang: ";
    cin.ignore();
    getline(cin, judul);
    cout << "\tMasukkan jumlah buku yang ingin ditambahkan: ";
    cin >> jumlah;

    for (int i = 0; i < stokbuku.size(); i++) {
        if (stokbuku[i].judul == judul) {
            if (stokbuku[i].stok >= jumlah) {
                Keranjang k;
                k.buku = stokbuku[i];
                k.jumlah = jumlah;
                keranjang.push_back(k);
                stokbuku[i].stok -= jumlah;
                cout << "Buku " << judul << " sebanyak " << jumlah << " buah berhasil ditambahkan ke keranjang!\n";
            } else {
                cout << "Stok buku tidak cukup!\n";
            }
            return;
        }
    }

    cout << "Buku dengan judul " << judul << " tidak ditemukan!\n";
}

// Fungsi untuk menampilkan isi keranjang
void tampilkanKeranjang(vector<Keranjang> &keranjang) {
    cout << "Isi Keranjang:\n";
    for (int i = 0; i < keranjang.size(); i++) {
        cout << i + 1 << ". " << keranjang[i].buku.judul << " (" << keranjang[i].jumlah << ")\n";
    }
}

// Fungsi untuk melakukan checkout
void checkout(vector<Keranjang> &keranjang) {
    cout << "Anda telah melakukan checkout dengan item berikut:\n";
    tampilkanKeranjang(keranjang);
    keranjang.clear();
    cout << "Terima kasih telah berbelanja!\n";
}

int main() {
    vector<Buku> stokbuku;
    vector<Keranjang> keranjang;
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
            do {
                cout << "=============================================\n";
                cout << "Silakan pilih menu yang tersedia:\n";
                cout << "=============================================\n";
                cout << "1. Tambah barang ke keranjang\n";
                cout << "2. Tampilkan isi keranjang\n";
                cout << "3. Checkout\n";
                cout << "4. Kembali\n";
                cout << "Pilihan: ";
                cin >> pilihan;
                switch (pilihan) {
                case 1:
                    // Tambah barang ke keranjang
                    tambahKeKeranjang(stokbuku, keranjang);
                    break;
                case 2:
                    // Tampilkan isi keranjang
                    tampilkanKeranjang(keranjang);
                    break;
                case 3:
                    // Checkout
                    checkout(keranjang);
                    break;
                case 4:
                    // Kembali ke menu utama
                    break;
                default:
                    cout << "Menu tidak tersedia";
                }
            } while (pilihan != 4);
            break;
        default:
            cout << "Menu tidak tersedia!\n\n";
            break;
        }
    } while (login != 3);
    return 0;
}
