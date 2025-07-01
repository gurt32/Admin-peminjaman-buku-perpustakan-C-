#include <iostream>  //header untuk menggunakan fungsi I/O (cin dan cout)
using namespace std; // untuk menghilangkan penggunaan `std::` ketika menggunakan cin dan cout

typedef struct ElmPeminjam *addressPeminjam; // deklarasi variabel addressPeminjam untuk pointer ke elmPeminjam
typedef struct ElmBuku *addressBuku;         // deklarasi variabel addressBuku untuk pointer ke elmBuku

struct infoPeminjam
{
    string idPeminjam;
    string namaPeminjam;
};
struct infoBuku
{
    string idBuku;
    string namaBuku;
    int jumlahPeminjam;
};

struct listPeminjam
{
    addressPeminjam firstPeminjam;
};
struct listBuku
{
    addressBuku firstBuku;
    addressBuku lastBuku;
};

struct ElmPeminjam
{
    infoPeminjam info;
    addressPeminjam nextPeminjam;
};
struct ElmBuku
{
    infoBuku info;
    addressBuku nextBuku;
    addressBuku prevBuku;
    listPeminjam Peminjam;
};

void createlistPeminjam(listPeminjam &LN)
{
    LN.firstPeminjam = NULL;
}
void createlistBuku(listBuku &LG)
{
    LG.firstBuku = NULL;
    LG.lastBuku = NULL;
}

addressPeminjam createElmPeminjam(infoPeminjam info)
{
    addressPeminjam c = new ElmPeminjam;
    c->info = info;
    c->nextPeminjam = NULL;
    return c;
}
addressBuku createElmBuku(infoBuku info)
{
    addressBuku p = new ElmBuku;
    p->info = info;
    p->nextBuku = NULL;
    p->prevBuku = NULL;
    p->Peminjam.firstPeminjam = NULL;
    p->info.jumlahPeminjam = 0;
    return p;
}

void insertFirstPeminjam(listPeminjam &LN, addressPeminjam c)
{
    if (LN.firstPeminjam == NULL)
    {
        LN.firstPeminjam = c;
    }
    else
    {
        c->nextPeminjam = LN.firstPeminjam;
        LN.firstPeminjam = c;
    }
}
void insertLastBuku(listBuku &LG, addressBuku p)
{
    if ((LG.firstBuku == NULL) && (LG.lastBuku == NULL))
    {
        LG.firstBuku = p;
        LG.lastBuku = p;
    }
    else
    {
        p->prevBuku = LG.lastBuku;
        LG.lastBuku->nextBuku = p;
        LG.lastBuku = p;
    }
}

addressPeminjam searchPeminjam(listPeminjam LN, string idPeminjam)
{
    addressPeminjam p = LN.firstPeminjam; // pointer untuk traversal
    if (p != NULL)
    {
        while ((p->info.idPeminjam != idPeminjam) && (p->nextPeminjam != NULL))
        { // akan berhanti jika menemukan id yang sama atau pointer menunjuk elemen terakhir
            p = p->nextPeminjam;
        }
        if (p->info.idPeminjam == idPeminjam)
        {             // cek elemen apakah menemukan id yang sama atau di elemen terakhir yang tidak sempat dicek dikondisi perulanagan dicek disini
            return p; // jika benar keluarkan alamat p
        }
        else
        {
            return NULL; // jika tidak ada bahkan sampai elemen terakhir dicek tetao tidak ada makan id yang dicari tidak ada
        }
    }
    else
    {
        return NULL;
    }
}

addressBuku searchBuku(listBuku LG, string idBuku)
{
    addressBuku temp;                                    // membuar address temp
    if ((LG.firstBuku != NULL) && (LG.lastBuku != NULL)) // jika first dan last tidak null (ada data pada list)
    {                                                    //
        temp = LG.firstBuku;                             // temp diisi nilai first
        if (temp->nextBuku == NULL)                      // jika next temp adalah null (hanya ada satu data pada list)
        {
            if (temp->info.idBuku == idBuku) // jika info dari temp sama dengan data dicari, maka data akan ditampilkan
            {
                return temp;
            }
            else // jika info dari data tidak sama dengan dicari, maka data tidak ada
            {
                return NULL;
            }
        }
        else                                      // jila next temp tidak null (ada lebih dari 1 data)
        {                                         //
            while ((temp->info.idBuku != idBuku)) // melakukan perulangan hingga info temp sama dengan data dicari
            {                                     //
                temp = temp->nextBuku;            // temp diisi dengan next temp
            }                                     //
            if (temp->info.idBuku == idBuku)      // apabila perulangan berhenti, akan di cek apakeh info temp sama dengan data dicari. apabila sama akan ditampilkan
            {
                return temp;
            }
            else // jika info dari data tidak sama dengan dicari, maka data tidak ada
            {
                return NULL;
            }
        }
    }
    else // jika hanya ada satu data dan data tidak sama dengan yang dicari, maka data tidak ada
    {
        return NULL;
    }
}

void addPeminjam(listBuku &LG, listPeminjam &LN, string idBuku, string idPeminjam)
{
    addressPeminjam c, q;
    addressBuku p;
    c = searchPeminjam(LN, idPeminjam);
    p = searchBuku(LG, idBuku);
    if ((c != NULL) && (p != NULL))
    {
        q = createElmPeminjam(c->info);
        insertFirstPeminjam(p->Peminjam, q);
        cout << " Peminjam Telah Ditambahkan ke Buku !" << endl;
    }
    cout << endl;
}

void viewPeminjam(listPeminjam &LN)
{
    if (LN.firstPeminjam == NULL)
    {
        cout << "\n Peminjam Masih Kosong!";
    }
    else
    {
        addressPeminjam c = LN.firstPeminjam;
        while (c != NULL)
        {
            cout << "ID Peminjam   \t:" << c->info.idPeminjam << endl;
            cout << "Nama Peminjam \t:" << c->info.namaPeminjam << endl;
            c = c->nextPeminjam;
        }
    }
}

void viewBukuPeminjam(listBuku &LG)
{
    if ((LG.firstBuku == NULL) && (LG.lastBuku == NULL))
    {
        cout << "\n Buku Masih Kosong!";
    }
    else
    {
        addressBuku p = LG.firstBuku;
        while (p != NULL)
        {
            cout << "\nID Buku \t:" << p->info.idBuku << endl;
            cout << "Nama Buku \t:" << p->info.namaBuku << endl;
            cout << endl;
            viewPeminjam(p->Peminjam);
            cout << "====================================";
            p = p->nextBuku;
        }
    }
}

void deleteAfterBuku(listBuku &LG, string idBuku)
{
    addressBuku p = LG.firstBuku;
    while (p != NULL && p->info.idBuku != idBuku)
    {
        p = p->nextBuku;
    }

    if (p != NULL)
    {
        if (p == LG.firstBuku)
        {
            LG.firstBuku = p->nextBuku;
            if (LG.firstBuku != NULL)
            {
                LG.firstBuku->prevBuku = NULL;
            }
        }
        else if (p == LG.lastBuku)
        {
            LG.lastBuku = p->prevBuku;
            if (LG.lastBuku != NULL)
            {
                LG.lastBuku->nextBuku = NULL;
            }
        }
        else
        {
            p->prevBuku->nextBuku = p->nextBuku;
            p->nextBuku->prevBuku = p->prevBuku;
        }
        p->nextBuku = NULL;
        p->prevBuku = NULL;
    }
}

void deleteBuku(listBuku &LG, string idBuku)
{
    addressBuku p = searchBuku(LG, idBuku);
    if (p != NULL)
    {
        p->Peminjam.firstPeminjam = NULL;
        deleteAfterBuku(LG, idBuku);
        cout << "\n Buku Berhasil Dihapus!";
    }
}

void deleteAfterPeminjam(listPeminjam &LN, string idPeminjam)
{
    if (LN.firstPeminjam != NULL)
    {
        addressPeminjam temp = LN.firstPeminjam;
        if (temp->nextPeminjam == NULL)
        {
            createlistPeminjam(LN);
        }
        else
        {
            addressPeminjam c;
            while ((temp->nextPeminjam != NULL) && (temp->info.idPeminjam != idPeminjam))
            {
                c = temp;
                temp = temp->nextPeminjam;
            }
            if (temp->info.idPeminjam == idPeminjam)
            {
                if (temp == LN.firstPeminjam)
                {
                    LN.firstPeminjam = temp->nextPeminjam;
                    temp->nextPeminjam = NULL;
                }
                else
                {
                    c->nextPeminjam = temp->nextPeminjam;
                    temp->nextPeminjam = NULL;
                }
            }
        }
    }
}

void deletePeminjam(listBuku &LG, listPeminjam &LN, string idPeminjam)
{
    addressPeminjam c;
    addressBuku p;

    c = searchPeminjam(LN, idPeminjam);
    if (c != NULL)
    {
        p = LG.firstBuku;
        while (p->nextBuku != NULL)
        {
            deleteAfterPeminjam(p->Peminjam, idPeminjam);
            p = p->nextBuku;
        }
        deleteAfterPeminjam(p->Peminjam, idPeminjam);
        deleteAfterPeminjam(LN, idPeminjam);
        cout << "\n Peminjam Berhasil Dihapus!";
    }
}