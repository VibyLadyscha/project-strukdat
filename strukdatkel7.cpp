#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <unordered_map>
using namespace std;

// Struct untuk menyimpan data barang
struct Buku
{
    string kategori;
    string genre;
    string judul;
    string penulis;
    string penerbit;
    int harga;
    int stok;
};

// Fungsi untuk menambahkan barang ke dalam unordered_map
void tambahBukuMap(unordered_map<string, vector<Buku>> &kumpulanKategori, unordered_map<string, vector<Buku>> &kumpulanPenulis, unordered_map<string, vector<Buku>> &kumpulanJudul, const Buku &buku)
{
    kumpulanKategori[buku.kategori].push_back(buku);
    kumpulanPenulis[buku.penulis].push_back(buku);
    kumpulanJudul[buku.judul].push_back(buku);
}

// Fungsi untuk menambahkan barang baru ke dalam sistem stok barang
void tambahBuku(vector<Buku> &stokbuku, unordered_map<string, vector<Buku>> &kumpulanKategori, unordered_map<string, vector<Buku>> &kumpulanPenulis, unordered_map<string, vector<Buku>> &kumpulanJudul, Buku buku, bool fromFile = false)
{
    if (!fromFile)
    {
        cout << "\tMasukkan kategori buku: ";
        cin >> buku.kategori;
        cout << "\tMasukkan genre buku: ";
        cin >> buku.genre;
        cin.ignore(); // Mengabaikan karakter newline yang tersisa di buffer
        cout << "\tMasukkan judul buku: ";
        getline(cin, buku.judul);
        cout << "\tMasukkan penulis buku: ";
        cin >> buku.penulis;
        cin.ignore(); // Mengabaikan karakter newline yang tersisa di buffer
        cout << "\tMasukkan penerbit buku: ";
        getline(cin, buku.penerbit);
        cout << "\tMasukkan harga buku: Rp";
        cin >> buku.harga;
        cout << "\tMasukkan stok buku: ";
        cin >> buku.stok;
    }

    stokbuku.push_back(buku);                                              // Menambahkan buku ke dalam vektor stokbuku
    tambahBukuMap(kumpulanKategori, kumpulanPenulis, kumpulanJudul, buku); // Menambahkan buku ke dalam unordered_map
}

// Fungsi untuk mencari buku berdasarkan kategori atau penulis
void cariBuku(string cari, unordered_map<string, vector<Buku>> &chain)
{
    if (chain.find(cari) != chain.end())
    {
        cout << "\nBuku ditemukan!\n";
        cout << "=============================================\n";
        for (auto &buku : chain[cari])
        {
            cout << "\tJudul: " << buku.judul << endl;
            cout << "\tPenulis: " << buku.penulis << endl;
            cout << "\tPenerbit: " << buku.penerbit << endl;
            cout << "\tHarga: " << buku.harga << endl;
            cout << "\tStok: " << buku.stok << endl;
            cout << "=============================================\n";
        }
    }
    else
    {
        cout << "Buku tidak ditemukan.\n";
    }
    cout << "\n";
}

// Fungsi untuk mencari buku berdasarkan range harga
void cariBukuHarga(const vector<Buku> &stokbuku, int hargaMin, int hargaMax)
{
    bool found = false;

    if (found == false)
    {
        cout << "\nBuku dengan harga antara Rp " << hargaMin << " sampai Rp " << hargaMax << " ditemukan!\n";
        cout << "=============================================\n";
        for (const auto &buku : stokbuku)
        {
            if (buku.harga >= hargaMin && buku.harga <= hargaMax)
            {
                found = true;
                cout << "\tKategori: " << buku.kategori << "\n";
                cout << "\tGenre: " << buku.genre << "\n";
                cout << "\tJudul: " << buku.judul << endl;
                cout << "\tPenulis: " << buku.penulis << endl;
                cout << "\tPenerbit: " << buku.penerbit << endl;
                cout << "\tHarga: " << buku.harga << endl;
                cout << "\tStok: " << buku.stok << endl;
                cout << "=============================================\n";
            }
        }
        cout << "\n";
    }

    else
    {
        cout << "Tidak ada buku dalam range harga tersebut.\n";
        cout << "=============================================\n";
    }
}

int main()
{
    vector<Buku> stokbuku;
    unordered_map<string, vector<Buku>> kumpulanKategori;
    unordered_map<string, vector<Buku>> kumpulanJudul;
    unordered_map<string, vector<Buku>> kumpulanPenulis;

    // Menambahkan buku dari input file
    ifstream inputFile("defaultstock.txt");
    Buku buku;

    while (getline(inputFile, buku.kategori) &&
           getline(inputFile, buku.genre) &&
           getline(inputFile, buku.judul) &&
           getline(inputFile, buku.penulis) &&
           getline(inputFile, buku.penerbit) &&
           inputFile >> buku.harga >> buku.stok)
    {
        inputFile.ignore(); // Mengabaikan karakter newline
        tambahBuku(stokbuku, kumpulanKategori, kumpulanPenulis, kumpulanJudul, buku, true);
    }

    inputFile.close();

    int pilihan, login, pilihanCari, hargaMin, hargaMax;
    string kategori, judul, penulis;

    do
    {
        cout << "=============================================\n";
        cout << "Selamat datang di sistem manajemen stok buku\n";
        cout << "=============================================\n";
        cout << "Masuk sebagai\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";

        cin >> login;

        if (login == 1)
        {
            cout << "Anda masuk sebagai Admin.\n";
            cout << "=============================================\n\n";
            do
            {
                cout << "=============================================\n";
                cout << "Silakan pilih menu yang tersedia:\n";
                cout << "=============================================\n";
                cout << "1. Tambah buku\n";                           // admin
                cout << "2. Pembaruan stok buku setelah transaksi\n"; // admin, nambah stok
                cout << "3. Cari buku\n";
                cout << "4. Menampilkan seluruh stok buku\n"; // customer dan admin
                cout << "5. Kembali\n";                       // keluar dari menu admin
                cout << "Pilihan: ";

                cin >> pilihan;

                if (pilihan == 1)
                {
                    // Tambah buku
                    tambahBuku(stokbuku, kumpulanKategori, kumpulanPenulis, kumpulanJudul, buku);
                }
                else if (pilihan == 2)
                {
                    // Pembaruan stok buku setelah transaksi
                    cout << "Masukkan judul buku yang akan diupdate: ";
                }
                else if (pilihan == 3)
                {
                    // Cari buku
                    do
                    {
                        cout << "Cari buku berdasarkan: \n";
                        cout << "1. Kategori\n";
                        cout << "2. Judul\n";
                        cout << "3. Penulis\n";
                        cout << "4. Range Harga\n";
                        cout << "5. Kembali\n";
                        cout << "Pilihan: ";

                        cin >> pilihanCari;
                        if (pilihanCari == 1)
                        {
                            cout << "Masukkan kategori buku yang ingin dicari: ";
                            cin >> kategori;
                            cariBuku(kategori, kumpulanKategori);
                        }
                        else if (pilihanCari == 2)
                        {
                            cout << "Masukkan judul buku yang ingin dicari: ";
                            cin >> judul;
                            cariBuku(judul, kumpulanJudul);
                        }
                        else if (pilihanCari == 3)
                        {
                            cout << "Masukkan penulis buku yang ingin dicari: ";
                            cin >> penulis;
                            cariBuku(penulis, kumpulanPenulis);
                        }
                        else if (pilihanCari == 4)
                        {
                            cout << "\n=============================================\n";
                            cout << "Masukkan range harga buku yang ingin dicari: \n";
                            cout << "\tHarga minimum: Rp ";
                            cin >> hargaMin;
                            cout << "\tHarga maksimum: Rp ";
                            cin >> hargaMax;
                            cariBukuHarga(stokbuku, hargaMin, hargaMax);
                        }
                        else
                        {
                            cout << "Menu tidak tersedia!\n";
                        }
                    } while (pilihanCari != 5);
                }
                else if (pilihan == 4)
                {
                    // Menampilkan seluruh stok buku
                    cout << "Menampilkan seluruh stok buku";
                }
                else if (pilihan == 5)
                {
                    // Kembali ke menu utama
                }
                else
                {
                    cout << "Menu tidak tersedia!\n";
                }
            } while (pilihan != 5);
        }
        else if (login == 2)
        {
            cout << "Anda masuk sebagai Customer.\n\n";
            cout << "=============================================\n";
        }
        else if (login == 3)
        {
            cout << "Terima kasih, sampai jumpa!\n";
        }
        else
        {
            cout << "Menu tidak tersedia!\n";
        }
    } while (login != 3);

    return 0;
}
