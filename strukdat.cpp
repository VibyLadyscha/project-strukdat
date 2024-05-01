#include <iostream>
#include <vector>
#include <string>

class Barang {
public:
    std::string nama;
    int kuantitas;

    Barang(std::string n, int k) : nama(n), kuantitas(k) {}
};

class Keranjang {
private:
    std::vector<Barang> items;

public:
    void tambahBarang(std::string nama, int kuantitas) {
        items.push_back(Barang(nama, kuantitas));
    }

    void tampilkanKeranjang() {
        std::cout << "Isi Keranjang:\n";
        for (int i = 0; i < items.size(); i++) {
            std::cout << i + 1 << ". " << items[i].nama << " (" << items[i].kuantitas << ")\n";
        }
    }

    void checkout() {
        std::cout << "Anda telah melakukan checkout dengan item berikut:\n";
        tampilkanKeranjang();
        items.clear();
        std::cout << "Terima kasih telah berbelanja!\n";
    }
};

int main() {
    Keranjang keranjang;
    std::string nama;
    int kuantitas;
    char pilihan;
    char user;

    std::cout << "Apakah Anda Admin atau Pelanggan? (A/P): ";
    std::cin >> user;

    if (user == 'A') {
        do {
            std::cout << "Menu Admin:\n";
            std::cout << "1. Tambah barang ke keranjang\n";
            std::cout << "2. Tampilkan isi keranjang\n";
            std::cout << "3. Checkout\n";
            std::cout << "4. Keluar\n";
            std::cout << "Masukkan pilihan Anda: ";
            std::cin >> pilihan;

            switch (pilihan) {
                case '1':
                    std::cout << "Masukkan nama barang: ";
                    std::cin >> nama;
                    std::cout << "Masukkan kuantitas barang: ";
                    std::cin >> kuantitas;
                    keranjang.tambahBarang(nama, kuantitas);
                    break;
                case '2':
                    keranjang.tampilkanKeranjang();
                    break;
                case '3':
                    keranjang.checkout();
                    break;
                case '4':
                    std::cout << "Terima kasih telah menggunakan program ini.\n";
                    break;
                default:
                    std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            }
        } while (pilihan != '4');
    } else if (user == 'P') {
        do {
            std::cout << "Menu Pelanggan:\n";
            std::cout << "1. Tampilkan isi keranjang\n";
            std::cout << "2. Checkout\n";
            std::cout << "3. Keluar\n";
            std::cout << "Masukkan pilihan Anda: ";
            std::cin >> pilihan;

            switch (pilihan) {
                case '1':
                    keranjang.tampilkanKeranjang();
                    break;
                case '2':
                    keranjang.checkout();
                    break;
                case '3':
                    std::cout << "Terima kasih telah menggunakan program ini.\n";
                    break;
                default:
                    std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            }
        } while (pilihan != '3');
    } else {
        std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
    }

    return 0;
}
