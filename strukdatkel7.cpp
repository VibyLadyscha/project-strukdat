#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
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

// Struct untuk menyimpan data keranjang belanja
struct Keranjang
{
    Buku buku;
    int jumlah;
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
        cout << "-------------------------------------------------\n";
        cout << "Masukkan data buku yang ingin ditambahkan:\n";
        cout << "\tMasukkan kategori buku: ";
        cin >> buku.kategori;
        cout << "\tMasukkan genre buku: ";
        cin >> buku.genre;
        cin.ignore(); 
        cout << "\tMasukkan judul buku: ";
        getline(cin, buku.judul);
        cout << "\tMasukkan penulis buku: ";
        getline(cin, buku.penulis);
        cout << "\tMasukkan penerbit buku: ";
        getline(cin, buku.penerbit);
        cout << "\tMasukkan harga buku: Rp";
        cin >> buku.harga;
        cout << "\tMasukkan stok buku: ";
        cin >> buku.stok;

        cout << "Buku berhasil ditambahkan!\n";
        cout << "-------------------------------------------------\n\n";
    }

    stokbuku.push_back(buku);                                              // Menambahkan buku ke dalam vektor stokbuku
    tambahBukuMap(kumpulanKategori, kumpulanPenulis, kumpulanJudul, buku); // Menambahkan buku ke dalam unordered_map
}

// Fungsi untuk update stok unordered map setelah transaksi
void updateMap(unordered_map<string, vector<Buku>> &kumpulanKategori, unordered_map<string, vector<Buku>> &kumpulanPenulis, unordered_map<string, vector<Buku>> &kumpulanJudul, const Buku &buku)
{
    for (auto &b : kumpulanKategori[buku.kategori])
    {
        if (b.judul == buku.judul)
        {
            b.stok = buku.stok;
        }
    }

    for (auto &b : kumpulanPenulis[buku.penulis])
    {
        if (b.judul == buku.judul)
        {
            b.stok = buku.stok;
        }
    }

    for (auto &b : kumpulanJudul[buku.judul])
    {
        if (b.judul == buku.judul)
        {
            b.stok = buku.stok;
        }
    }
}

// Fungsi untuk menambahkan barang ke keranjang
void tambahKeKeranjang(vector<Buku> &stokbuku, vector<Keranjang> &keranjang, unordered_map<string, vector<Buku>> &kumpulanKategori, unordered_map<string, vector<Buku>> &kumpulanPenulis, unordered_map<string, vector<Buku>> &kumpulanJudul)
{
    string judul;
    int jumlah;
    cout << "\tMasukkan judul buku yang ingin ditambahkan ke keranjang: ";
    cin.ignore();
    getline(cin, judul);
    cout << "\tMasukkan jumlah buku yang ingin ditambahkan: ";
    cin >> jumlah;

    for (int i = 0; i < stokbuku.size(); i++)
    {
        if (stokbuku[i].judul == judul)
        {
            if (stokbuku[i].stok >= jumlah)
            {
                Keranjang k;
                k.buku = stokbuku[i];
                k.jumlah = jumlah;
                keranjang.push_back(k);
                stokbuku[i].stok -= jumlah;
                updateMap(kumpulanKategori, kumpulanPenulis, kumpulanJudul, stokbuku[i]);
                cout << "Buku " << judul << " sebanyak " << jumlah << " buah berhasil ditambahkan ke keranjang!\n";
            }
            else
            {
                cout << "Stok buku tidak cukup!\n";
            }
            return;
        }
    }

    cout << "Buku dengan judul " << judul << " tidak ditemukan!\n";
}

// Fungsi untuk menampilkan isi keranjang
void tampilkanKeranjang(vector<Keranjang> &keranjang)
{
    cout << "Isi Keranjang:\n";
    for (int i = 0; i < keranjang.size(); i++)
    {
        cout << i + 1 << ". " << keranjang[i].buku.judul << " (" << keranjang[i].jumlah << ")\n";
    }
}

// Fungsi untuk melakukan checkout
void checkout(vector<Keranjang> &keranjang)
{
    cout << "Anda telah melakukan checkout dengan item berikut:\n";
    tampilkanKeranjang(keranjang);
    keranjang.clear();
    cout << "Terima kasih telah berbelanja!\n";
}

// Fungsi untuk mencari buku berdasarkan kategori atau penulis
void cariBuku(string cari, unordered_map<string, vector<Buku>> &chain)
{
    bool found = false;

    // Ubah string cari menjadi huruf kecil
    transform(cari.begin(), cari.end(), cari.begin(), ::tolower);
        cout << "+-------------------------------+--------------------+--------------------+-------+------+\n";
        cout << "| " << setw(30) << left << "Judul"
             << "| " << setw(19) << left << "Penulis"
             << "| " << setw(19) << left << "Penerbit"
             << "|" << setw(6) << left << "Harga"
             << "| " << setw(6) << left << "Stok"
             << "|\n";
        cout << "+-------------------------------+--------------------+--------------------+-------+------+\n";

    // Cek apakah kata kunci cocok dengan judul, penulis, atau kategori buku
    for (const auto& pair : chain) {
        for (const auto& buku : pair.second) {
            string judul = buku.judul;
            string penulis = buku.penulis;
            string kategori = buku.kategori;

            // Ubah string judul, penulis, dan kategori menjadi huruf kecil
            transform(judul.begin(), judul.end(), judul.begin(), ::tolower);
            transform(penulis.begin(), penulis.end(), penulis.begin(), ::tolower);
            transform(kategori.begin(), kategori.end(), kategori.begin(), ::tolower);

            if (judul.find(cari) != string::npos ||
                penulis.find(cari) != string::npos ||
                kategori.find(cari) != string::npos) {
                found = true;
                
                // Memeriksa panjang judul, penulis, dan kategori
                if (buku.judul.length() > 30) {
                    cout << "| " << setw(30) << left << buku.judul.substr(0, 30) << "|\n";
                    cout << "| " << setw(30) << left << buku.judul.substr(30) << "| ";
                } else {
                    cout << "| " << setw(30) << left << buku.judul << "| ";
                }

                if (buku.penulis.length() > 20) {
                    cout << setw(20) << left << buku.penulis.substr(0, 20) << "| ";
                } else {
                    cout << setw(20) << left << buku.penulis << "| ";
                }

                if (buku.penerbit.length() > 20) {
                    cout << setw(20) << left << buku.penerbit.substr(0, 20) << "| ";
                } else {
                    cout << setw(20) << left << buku.penerbit << "| ";
                }

                cout << setw(6) << left << buku.harga
                     << "| " << setw(6) << left << buku.stok
                     << "|\n";
            }
        }
    }

    if (!found) {
        cout << "Buku tidak ditemukan.\n";
    }
    cout << "+-------------------------------+--------------------+--------------------+-------+------+\n\n";
}

// Tahap radix sort
int getMax(vector<Buku> &stokbuku, int n)
{
    int max = stokbuku[0].harga;
    for (int i = 1; i < n; i++)
        if (stokbuku[i].harga > max)
            max = stokbuku[i].harga;
    return max;
}

void countSort(vector<Buku> &stokbuku, int n, int exp)
{
    vector<Buku> output(n);
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(stokbuku[i].harga / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[(stokbuku[i].harga / exp) % 10] - 1] = stokbuku[i];
        count[(stokbuku[i].harga / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        stokbuku[i] = output[i];
}

void radixsort(vector<Buku> &stokbuku)
{
    int max = getMax(stokbuku, stokbuku.size());

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(stokbuku, stokbuku.size(), exp);
}

// Fungsi untuk mencari buku berdasarkan range harga
void cariBukuHarga(vector<Buku> &stokbuku, int hargaMin, int hargaMax)
{
    bool found = false;
    
    radixsort(stokbuku);

    if (found == false)
    {
        cout << "\nBuku dengan harga antara Rp " << hargaMin << " sampai Rp " << hargaMax << " ditemukan!\n";
        cout << "+-------------------------------+--------------------+--------------------+-------+------+\n";
        cout << "| " << setw(30) << left << "Judul"
             << "| " << setw(19) << left << "Penulis"
             << "| " << setw(19) << left << "Penerbit"
             << "|" << setw(6) << left << "Harga"
             << "| " << setw(6) << left << "Stok"
             << "|\n";
        cout << "+-------------------------------+--------------------+--------------------+-------+------+\n";

        for (const auto &buku : stokbuku)
        {
            if (buku.harga >= hargaMin && buku.harga <= hargaMax)
            {
                if (buku.judul.length() > 30) {
                cout << "| " << setw(30) << left << buku.judul.substr(0, 30) << "|\n";
                cout << "| " << setw(30) << left << buku.judul.substr(30) << "| ";
            } else {
                cout << "| " << setw(30) << left << buku.judul << "| ";
            }

            if (buku.penulis.length() > 20) {
                cout << setw(20) << left << buku.penulis.substr(0, 20) << "| ";
            } else {
                cout << setw(20) << left << buku.penulis << "| ";
            }

            if (buku.penerbit.length() > 20) {
                cout << setw(20) << left << buku.penerbit.substr(0, 20) << "| ";
            } else {
                cout << setw(20) << left << buku.penerbit << "| ";
            }

            cout << setw(6) << left << buku.harga
                 << "| " << setw(6) << left << buku.stok
                 << "|\n";
            }
        }
    }

    else
    {
        cout << "Tidak ada buku dalam range harga tersebut.\n";
    } 
    cout << "+-------------------------------+--------------------+--------------------+-------+------+\n\n";
}

// Fungsi untuk mengurutkan vector stokbuku berdasarkan judul
bool compareJudul(const Buku &a, const Buku &b)
{
    return a.judul < b.judul;
}

// Fungsi untuk menampilkan stok buku
void printAll(vector<Buku> &stokbuku)
{
    // sort stokbuku berdasarkan huruf dalam judul
    sort(stokbuku.begin(), stokbuku.end(), compareJudul);

    cout << "Stok buku yang tersedia:\n";
    cout << "+-----------+-----------+-------------------------------+---------------------+---------------------+-------+-------+\n";
    cout << "| " << setw(10) << left << "Kategori"
         << "| " << setw(10) << left << "Genre"
         << "| " << setw(30) << left << "Judul"
         << "| " << setw(20) << left << "Penulis"
         << "| " << setw(20) << left << "Penerbit"
         << "| " << setw(6) << left << "Harga"
         << "| " << setw(6) << left << "Stok"
         << "|\n";
    cout << "+-----------+-----------+-------------------------------+---------------------+---------------------+-------+-------+\n";

    for (const auto &buku : stokbuku)
    {
        if (buku.judul.length() > 30) {
            cout << "| " << setw(10) << left << buku.kategori
                 << "| " << setw(10) << left << buku.genre
                 << "| " << setw(30) << left << buku.judul.substr(0, 30) << "| ";
            cout << setw(30) << left << buku.judul.substr(30) << "| ";
        } else {
            cout << "| " << setw(10) << left << buku.kategori
                 << "| " << setw(10) << left << buku.genre
                 << "| " << setw(30) << left << buku.judul << "| ";
        }

        if (buku.penulis.length() > 20) {
            cout << setw(20) << left << buku.penulis.substr(0, 20) << "| ";
        } else {
            cout << setw(20) << left << buku.penulis << "| ";
        }

        if (buku.penerbit.length() > 20) {
            cout << setw(20) << left << buku.penerbit.substr(0, 20) << "| ";
        } else {
            cout << setw(20) << left << buku.penerbit << "| ";
        }

        cout << setw(6) << left << buku.harga
             << "| " << setw(6) << left << buku.stok
             << "|\n";
    }
    cout << "+-----------+-----------+-------------------------------+---------------------+---------------------+-------+-------+\n\n";
}

int main()
{
    vector<Buku> stokbuku;
    vector<Keranjang> keranjang;
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
        cout << "--------------------------------------------\n";
        cout << "Selamat datang di sistem manajemen stok buku\n";
        cout << "--------------------------------------------\n";
        cout << "Masuk sebagai\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";

        cin >> login;

        switch (login)
        {
        case 1:
            cout << "Anda masuk sebagai Admin.\n";
            cout << "--------------------------------------------\n\n";
            do
            {
                cout << "Silakan pilih menu yang tersedia:\n";
                cout << "1. Tambah buku\n";                     // admin
                cout << "2. Pembaruan stok buku\n";            // admin, nambah stok
                cout << "3. Cari buku\n";
                cout << "4. Menampilkan seluruh stok buku\n"; // customer dan admin
                cout << "5. Kembali\n";                       // keluar dari menu admin
                cout << "Pilihan: ";

                cin >> pilihan;
                cout << "\n";

                switch (pilihan)
                {
                case 1:
                    // Tambah buku
                    tambahBuku(stokbuku, kumpulanKategori, kumpulanPenulis, kumpulanJudul, buku);
                    break;
                case 2:
                    // Pembaruan stok buku setelah transaksi
                    cout << "\nMasukkan judul buku yang akan diupdate: ";
                    break;
                case 3:
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
                        switch (pilihanCari)
                        {
                        case 1:
                            cout << "Masukkan kategori buku yang ingin dicari: ";
                            cin >> kategori;
                            cariBuku(kategori, kumpulanKategori);
                            break;
                        case 2:
                            cout << "Masukkan judul buku yang ingin dicari: ";
                            cin.ignore();
                            getline(cin, judul);
                            cariBuku(judul, kumpulanJudul);
                            break;
                        case 3:
                            cout << "Masukkan penulis buku yang ingin dicari: ";
                            cin.ignore();
                            getline(cin, penulis);
                            cariBuku(penulis, kumpulanPenulis);
                            break;
                        case 4:
                            cout << "Masukkan range harga buku yang ingin dicari: \n";
                            cout << "\tHarga minimum: Rp ";
                            cin >> hargaMin;
                            cout << "\tHarga maksimum: Rp ";
                            cin >> hargaMax;
                            cariBukuHarga(stokbuku, hargaMin, hargaMax);
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Menu tidak tersedia!\n";
                            break;
                        }
                    } while (pilihanCari != 5);
                    break;
                case 4:
                    // Menampilkan seluruh stok buku
                    printAll(stokbuku);
                    break;
                case 5:
                    // Kembali ke menu utama
                    break;
                default:
                    cout << "Menu tidak tersedia!\n";
                    break;
                }
            } while (pilihan != 5);
            break;
        case 2:
            cout << "Anda masuk sebagai Customer.\n";
            cout << "--------------------------------------------\n\n";
            do
            {
                cout << "Silakan pilih menu yang tersedia:\n";
                cout << "1. Cari buku\n";
                cout << "2. Tambah barang ke keranjang\n";
                cout << "3. Tampilkan isi keranjang\n";
                cout << "4. Checkout\n";
                cout << "5. Kembali\n";
                cout << "Pilihan: ";
                cin >> pilihan;
                switch (pilihan)
                {
                case 1:
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
                        switch (pilihanCari)
                        {
                        case 1:
                            cout << "Masukkan kategori buku yang ingin dicari: ";
                            cin >> kategori;
                            cariBuku(kategori, kumpulanKategori);
                            break;
                        case 2:
                            cout << "Masukkan judul buku yang ingin dicari: ";
                            cin >> judul;
                            cariBuku(judul, kumpulanJudul);
                            break;
                        case 3:
                            cout << "Masukkan penulis buku yang ingin dicari: ";
                            cin >> penulis;
                            cariBuku(penulis, kumpulanPenulis);
                            break;
                        case 4:
                            cout << "Masukkan range harga buku yang ingin dicari: \n";
                            cout << "\tHarga minimum: Rp ";
                            cin >> hargaMin;
                            cout << "\tHarga maksimum: Rp ";
                            cin >> hargaMax;
                            cariBukuHarga(stokbuku, hargaMin, hargaMax);
                            break;
                        case 5:
                            cout << "\n";
                            break;
                        default:
                            cout << "Menu tidak tersedia!\n";
                            break;
                        }
                    } while (pilihanCari != 5);
                    break;
                case 2:
                    // Tambah barang ke keranjang
                    tambahKeKeranjang(stokbuku, keranjang, kumpulanKategori, kumpulanPenulis, kumpulanJudul);
                    break;
                case 3:
                    // Tampilkan isi keranjang
                    tampilkanKeranjang(keranjang);
                    break;
                case 4:
                    // Checkout
                    checkout(keranjang);
                    break;
                case 5:
                    // Kembali ke menu utama
                    break;
                default:
                    cout << "Menu tidak tersedia";
                }
            } while (pilihan != 5);
            break;
        case 3:
            cout << "Terima kasih, sampai jumpa kembali!\n";
            break;
        default:
            cout << "Menu tidak tersedia!\n";
            break;
        }
    } while (login != 3);

    return 0;
}