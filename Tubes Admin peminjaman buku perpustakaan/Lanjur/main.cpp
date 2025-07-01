#include "source.cpp"

using namespace std;
int main()
{
    listBuku listBuku;
    listPeminjam listPeminjam;
    createlistBuku(listBuku);
    createlistPeminjam(listPeminjam);
    addressBuku Buku, terbanyak = NULL, tersedikit = NULL;
    addressPeminjam Peminjam;
    infoBuku temp;

    int pilihan = 0, count = 0;
    string namaPeminjam, namaBuku, idPeminjam, idBuku;

    while (pilihan < 10)
    {
        system("cls");

        cout << "\n\n Pilihan Menu Tersedia : " << endl;
        cout << " 1. Tambah Buku\n 2. Tambah Peminjam\n 3. Masukkan Peminjam ke Buku\n 4. Hapus Sebuah Buku\n 5. Hapus Seorang Peminjam\n 6. Menampilkan Seluruh Buku Beserta Peminjamnya\n 7. Tampilkan Buku Yang Berisi Peminjam Tertentu\n 8. Tampilkan Peminjam Dari Buku\n 9. Tampilkan Buku dengan Peminjam Terbanyak dan Tersedikit\n"
             << endl;
        cout << " Masukkan Pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "\n Masukkan Id Buku   : ";
            cin >> idBuku;
            cout << " Masukkan Nama Buku : ";
            cin >> namaBuku;
            insertLastBuku(listBuku, createElmBuku({idBuku, namaBuku, 0}));
            break;
        case 2:
            cout << "\n Masukkan Id Peminjam    : ";
            cin >> idPeminjam;
            cout << " Masukkan Nama Peminjam  : ";
            cin >> namaPeminjam;
            insertFirstPeminjam(listPeminjam, createElmPeminjam({idPeminjam, namaPeminjam}));
            break;
        case 3:
            cout << "\n Masukkan Id Buku   : ";
            cin >> idBuku;
            cout << " Masukkan Id Peminjam : ";
            cin >> idPeminjam;
            addPeminjam(listBuku, listPeminjam, idBuku, idPeminjam);
            break;
        case 4:
            cout << "\n Masukkan Id Buku : ";
            cin >> idBuku;
            deleteBuku(listBuku, idBuku);
            break;
        case 5:
            cout << "\n Masukkan Id Peminjam : ";
            cin >> idPeminjam;
            deletePeminjam(listBuku, listPeminjam, idPeminjam);
            break;
        case 6:
            viewBukuPeminjam(listBuku);
            break;
        case 7:
            cout << "\n Masukkan Id Peminjam : ";
            cin >> idPeminjam;

            cout << "ID Peminjam \t:" << idPeminjam << endl;
            cout << endl;

            Buku = listBuku.firstBuku;
            while (Buku != NULL)
            {
                addressPeminjam Peminjam = Buku->Peminjam.firstPeminjam;
                while (Peminjam != NULL)
                {
                    if (Peminjam->info.idPeminjam == idPeminjam)
                    {
                        cout << "ID Peminjam \t:" << Peminjam->info.idPeminjam << endl;
                        cout << "Nama Peminjam \t:" << Peminjam->info.namaPeminjam << endl;
                    }
                    Peminjam = Peminjam->nextPeminjam;
                }
                Buku = Buku->nextBuku;
            }
            break;
        case 8:
            cout << "\n Masukkan Id Buku   : ";
            cin >> idBuku;
            Buku = listBuku.firstBuku;

            cout << "\n Daftar Peminjam dari Buku " << idBuku << " : " << endl;
            cout << endl;

            while (Buku != NULL)
            {
                if (Buku->info.idBuku == idBuku)
                {
                    addressPeminjam Peminjam = Buku->Peminjam.firstPeminjam;
                    while (Peminjam != NULL)
                    {
                        cout << "ID Peminjam \t:" << Peminjam->info.idPeminjam << endl;
                        cout << "Nama Peminjam \t:" << Peminjam->info.namaPeminjam << endl;

                        Peminjam = Peminjam->nextPeminjam;
                    }
                }
                Buku = Buku->nextBuku;
            }
            break;
        case 9:
            Buku = listBuku.firstBuku;
            while (Buku != NULL)
            {
                Peminjam = Buku->Peminjam.firstPeminjam;
                while (Peminjam != NULL)
                {
                    count++;
                    Peminjam = Peminjam->nextPeminjam;
                }
                Buku->info.jumlahPeminjam = count;
                Buku = Buku->nextBuku;
            }
            Buku = listBuku.firstBuku;
            while (Buku != NULL)
            {
                if (terbanyak == NULL || Buku->info.jumlahPeminjam > terbanyak->info.jumlahPeminjam)
                {
                    terbanyak = Buku;
                }
                if (tersedikit == NULL || Buku->info.jumlahPeminjam < tersedikit->info.jumlahPeminjam)
                {
                    tersedikit = Buku;
                }
                Buku = Buku->nextBuku;
            }

            cout << "\n Buku Dengan Peminjam Terbanyak : " << endl;
            cout << "ID Buku \t:" << terbanyak->info.idBuku << endl;
            cout << "Nama Buku \t:" << terbanyak->info.namaBuku << endl;
            cout << "Jumlah Peminjam\t:" << terbanyak->info.jumlahPeminjam << endl;

            cout << "\n Buku Dengan Peminjam Tersedikit : " << endl;
            cout << "ID Buku \t:" << tersedikit->info.idBuku << endl;
            cout << "Nama Buku \t:" << tersedikit->info.namaBuku << endl;
            cout << "Jumlah Peminjam\t:" << tersedikit->info.jumlahPeminjam << endl;

            break;
        default:
            cout << "\n Pilihan Anda Tidak Tersedia!" << endl;
            break;
        }
        cout << endl;
        system("pause");
    }

    return 0;
}