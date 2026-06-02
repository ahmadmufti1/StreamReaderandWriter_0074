//Soal Praktikum :
/*Buatlah program C++ berbasis Object-Oriented Programming (OOP) untuk digitalisasi manajemen toko elektronik "Gibran Jaya" dengan ketentuan berikut:
​1. Struktur Kelas TokoElektronik
• ​Atribut Private: Buat sebuah array berkapasitas 3 elemen sebagai perwujudan prinsip enkapsulasi (merepresentasikan barang yang dipajang di etalase).
• ​Constructor: Buat constructor untuk mengisi data awal ke dalam array tersebut secara otomatis.
• ​Method Public: Buat fungsi untuk mengambil produk dengan parameter nomorRak (bertipe data size_t).
​2. Mekanisme Exception Handling (Penanganan Error)
• ​Di dalam method pengambilan produk pada etalase, wajib menggunakan fungsi .at() saat mengakses indeks array.
• ​Jika pencarian indeks melewati batas, tangkap error bawaan out_of_range.
• ​Setelah ditangkap, lemparkan kembali (throw) pesan error kustom berikut: ​"Gagal Mengambil Barang : Rak nomor [X] kosong atau tidak tersedia!" (Ganti [X] dengan nilai nomorRak).
​"Gagal Mengambil Barang : Rak nomor [X] kosong atau tidak tersedia!" (Ganti [X] dengan nilai nomorRak).
3. Fitur Manajemen Gudang Berbasis File (File I/O & CRUD)
• ​Gunakan library <fstream> (Stream Reader/Writer) untuk menyimpan dan membaca basis data barang menggunakan file berekstensi teks (misalnya gudang.txt).
• ​Buatlah sebuah Menu Utama interaktif berbasis Command Line (CLI) yang mengakomodasi operasi CRUD berikut yang terhubung langsung dengan file .txt: 
• ​Create: Menambahkan data barang baru ke dalam file .txt.
• ​Read: Membaca dan menampilkan daftar barang dari dalam file .txt ke layar secara otomatis saat menu dibuka.
• ​Update: Memperbarui/mengubah data barang tertentu di dalam file .txt.
• ​Delete: Menghapus data barang dari dalam file .txt.
​4. Pengujian pada Fungsi main()
• ​Jalankan sistem Menu Utama (menggunakan looping seperti while atau do-while) agar pengguna bisa memilih fitur CRUD gudang.
• ​Tambahkan satu opsi khusus di dalam menu untuk menjalankan Simulasi Etalase (menguji Exception Handling pada poin 2) dengan dua skenario: 
• ​Skenario 1: Pengambilan barang di rak indeks ke-1 (Harus sukses).
• ​Skenario 2: Pengambilan barang di rak indeks ke-5 (Harus gagal dan menampilkan pesan error kustom).
Pastikan sistem menu, operasi file (CRUD), dan penangkapan error array terintegrasi dengan baik sehingga program tetap berjalan aman (tidak crash atau berhenti mendadak) meskipun terjadi error logika.*/

#include <iostream>
#include <exception> //untuk menangani error
#include <array>
#include <string>
#include <fstream> //untuk file I/O (Stream Reader/Writer)
#include <vector> //untuk manipulasi data saat update dan delete

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Laptop ASUS";
        etalase[1] = "Samsung S24";
        etalase[2] = "Earphone";
    }

    string ambilProdukEtalase(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            throw runtime_error("Gagal Mengambil Barang : Rak nomor [" + to_string(nomorRak) + "] kosong atau tidak tersedia!");
        }
    }
};

const string FILE_NAME = "gudang.txt";

int hitungBarang() {
    ifstream file(FILE_NAME);
    if (!file.is_open()) return 0;
    
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) count++;
    }
    file.close();
    return count;
}

void readGudang() {
    ifstream file(FILE_NAME);
    
    cout << "     DAFTAR STOK BARANG DI GUDANG UTAMA     \n";
    cout << "---------------------------------------------\n";
    
    if (!file.is_open() || hitungBarang() == 0) {
        cout << "Gudang masih kosong atau file belum dibuat.\n";
        cout << "---------------------------------------------\n";
        return;
    }

    string line;
    int no = 1;
    while (getline(file, line)) {
        if (!line.empty()) {
            cout << " " << no++ << ". " << line << "\n";
        }
    }
    cout << "---------------------------------------------\n";
    file.close();
}

void createGudang() {
    ofstream file(FILE_NAME, ios::app); // ios::app untuk append (menambah di akhir)
    if (!file.is_open()) {
        cout << "Gagal membuka file gudang\n";
        return;
    }

    string namaBarang;
    cout << "\nMasukkan nama barang elektronik baru: ";
    cin.ignore();
    getline(cin, namaBarang);

    if (!namaBarang.empty()) {
        file << namaBarang << "\n";
        cout << "Barang \"" << namaBarang << "\" berhasil ditambahkan ke gudang.\n";
    }
    file.close();
}


void updateGudang() {
    int total = hitungBarang();
    if (total == 0) {
        cout << " >= Tidak ada barang yang bisa diubah. Gudang kosong.\n";
        return;
    }

    int nomorPilihan;
    cout << "\nMasukkan nomor urut barang yang ingin diubah: ";
    cin >> nomorPilihan;

    if (nomorPilihan < 1 || nomorPilihan > total) {
        cout << "Nomor barang tidak valid!\n";
        return;
    }

    ifstream fileIn(FILE_NAME);
    ofstream fileOut("temp.txt"); // File sementara

    string line;
    string namaBaru;
    int currentLine = 1;

    cout << "Masukkan nama baru untuk barang tersebut: ";
    cin.ignore();
    getline(cin, namaBaru);

    while (getline(fileIn, line)) {
        if (currentLine == nomorPilihan) {
            fileOut << namaBaru << "\n";
        } else {
            fileOut << line << "\n";
        }
        currentLine++;
    }

    fileIn.close();
    fileOut.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    cout << " >= Data barang nomor " << nomorPilihan << " berhasil diperbarui.\n";
}

void deleteGudang() {
    int total = hitungBarang();
    if (total == 0) {
        cout << " >= Tidak ada barang yang bisa dihapus. Gudang kosong.\n";
        return;
    }

    int nomorPilihan;
    cout << "\nMasukkan nomor urut barang yang ingin dihapus: ";
    cin >> nomorPilihan;

    if (nomorPilihan < 1 || nomorPilihan > total) {
        cout << " >= Nomor barang tidak valid!\n";
        return;
    }

    ifstream fileIn(FILE_NAME);
    ofstream fileOut("temp.txt");

    string line;
    int currentLine = 1;
    string barangDihapus = "";

    while (getline(fileIn, line)) {
        if (currentLine == nomorPilihan) {
            barangDihapus = line;
            // Dilewati (tidak ditulis ke file temp) berarti dihapus
        } else {
            fileOut << line << "\n";
        }
        currentLine++;
    }

    fileIn.close();
    fileOut.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    cout << " >= Barang \"" << barangDihapus << "\" berhasil dihapus dari gudang.\n";
}

void SimulasiEtalase(TokoElektronik& toko) {
    cout << "\n============================================\n";
    cout << "      SIMULASI PENGUJIAN EXCEPTION HANDLING   \n";
    cout << "============================================\n";

    
    cout << ">= Skenario 1: Mencoba mengambil barang di rak indeks ke 1\n";
    try {
        string produk = toko.ambilProdukEtalase(1);
        cout << " -> Hasil: Sukses! Barang ditemukan: " << produk << "\n";
    }
    catch (const runtime_error& e) {
        cout << " -> Hasil: " << e.what() << "\n";
    }

    cout << "\n--------------------------------------------\n";

    // Skenario 2: Pengambilan barang di rak indeks ke 5 (Harus Gagal)
    cout << ">= Skenario 2: Mencoba mengambil barang di rak indeks ke 5\n";
    try {
        string produk = toko.ambilProdukEtalase(5);
        cout << " -> Hasil: Sukses, Barang ditemukan: " << produk << "\n";
    }
    catch (const runtime_error& e) {
        // Menangkap error
        cout << " -> Hasil Tangkapan Error:\n";
        cout << "    \"" << e.what() << "\"\n";
    }
    cout << "============================================\n";
    cout << " >= Sistem tetap berjalan aman tanpa crash\n";
}

int main() {
    TokoElektronik tokoGibran;
    int pilihanMenu;

    do {
        // Tampilkan data secara otomatis
        readGudang();

        cout << "\n=== SISTEM DIGITALISASI TOKO \"GIBRAN JAYA\" ===\n";
        cout << "1. Tambah Barang Gudang (Create)\n";
        cout << "2. Ubah Barang Gudang (Update)\n";
        cout << "3. Hapus Barang Gudang (Delete)\n";
        cout << "4. Jalankan Simulasi Etalase (Exception Handling)\n";
        cout << "5. Keluar Aplikasi\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {
            case 1:
                createGudang();
                break;
            case 2:
                updateGudang();
                break;
            case 3:
                deleteGudang();
                break;
            case 4:
                SimulasiEtalase(tokoGibran);
                break;
            case 5:
                cout << "\nTerima kasih telah menggunakan sistem Gibran Jaya.\n";
                break;
            default:
                cout << "\n >= Pilihan tidak valid, Silahkan masukkan angka 1-5.\n";
                // Mengatasi infinite loop jika user memasukkan input selain angka
                cin.clear();
                cin.ignore(10000, '\n');
        }
        
        if (pilihanMenu != 5) {
            cout << "\nTekan Enter untuk kembali ke Menu Utama...";
            cin.ignore();
            cin.get();
        }

    } while (pilihanMenu != 5);

    return 0;
}