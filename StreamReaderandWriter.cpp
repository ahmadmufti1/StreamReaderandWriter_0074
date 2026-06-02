//deklarasi library yang akan digunakan
#include <iostream>
#include <fstream> //untuk file I/O (Stream Reader/Writer)
#include <string>
using namespace std;

int main()
{
    //deklarasi variabel baris untuk menyimpan data string
    string baris;

    //membuka file dalam mode menulis
    ofstream outfile;
    //menunjuk ke sebuah nama file
    outfile.open("contohfile.txt");

    cout << ">= Menulis file, \'q\' untuk keluar " << endl;

}