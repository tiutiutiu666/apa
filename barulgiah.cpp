#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct Buku {
    string judul;
    string penulis;
    int tahun;
};

class Perpus {
private:
    list<Buku> bukuList;
    stack<list<Buku>> riwayatPerubahan;
    queue<Buku> antrianPeminjaman;
    set<string> bukuSet;
    map<string, int> bukuMap;

    struct TreeNode {
        Buku buku;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const Buku& buku) : buku(buku), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    bool bukuAwalDitambahkan;

    void insertBuku(TreeNode*& node, const Buku& buku) {
        if (node == nullptr) {
            node = new TreeNode(buku);
        } else {
            if (buku.judul < node->buku.judul) {
                insertBuku(node->left, buku);
            } else {
                insertBuku(node->right, buku);
            }
        }
    }

    void tampilDaftarBuku(TreeNode* node) {
        if (node != nullptr) {
            tampilDaftarBuku(node->left);
            cout << "- " << node->buku.judul << " oleh " << node->buku.penulis << " (" << node->buku.tahun << ")" << endl;
            tampilDaftarBuku(node->right);
        }
    }

    bool cariBuku(TreeNode* node, const string& judul) {
        if (node == nullptr) {
            return false;
        } else if (judul == node->buku.judul) {
            return true;
        } else if (judul < node->buku.judul) {
            return cariBuku(node->left, judul);
        } else {
            return cariBuku(node->right, judul);
        }
    }

    void hapusBuku(TreeNode*& node, const string& judul) {
        if (node == nullptr) {
            return;
        } else if (judul < node->buku.judul) {
            hapusBuku(node->left, judul);
        } else if (judul > node->buku.judul) {
            hapusBuku(node->right, judul);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
            } else {
                TreeNode* minRightNode = findMinNode(node->right);
                node->buku = minRightNode->buku;
                hapusBuku(node->right, minRightNode->buku.judul);
            }
        }
    }

    TreeNode* findMinNode(TreeNode* node) {
        if (node->left == nullptr) {
            return node;
        }
        return findMinNode(node->left);
    }

public:
    Perpus() : root(nullptr), bukuAwalDitambahkan(false) {
        Buku buku1 = {"Laskar Pelangi", "Andrea Hirata", 2005};
        Buku buku2 = {"Bumi Manusia", "Pramoedya Ananta Toer", 1980};
        Buku buku3 = {"Dilan: Dia adalah Dilanku Tahun 1990", "Pidi Baiq", 2014};
        Buku buku4 = {"Pulau Bung Karno: Mengungkap Fakta Sejarah yang Terlupakan", "Bastiaan H. Pardede", 2012};
        Buku buku5 = {"Sapiens: Revolusi Manusia", "Yuval Noah Harari", 2017};
        Buku buku6 = {"Biologi untuk SMA/MA Kelas X", "Sri Lestari", 2020};
        Buku buku7 = {"Fisika untuk SMA/MA Kelas XI", "Yohanes Surya", 2018};
        Buku buku8 = {"Kimia untuk SMA/MA Kelas XII", "Sri Wahyuni", 2019};

        tambahBuku(buku1);
        tambahBuku(buku2);
        tambahBuku(buku3);
        tambahBuku(buku4);
        tambahBuku(buku5);
        tambahBuku(buku6);
        tambahBuku(buku7);
        tambahBuku(buku8);
    }

    void tambahBuku(const Buku& buku) {
        if (bukuMap.find(buku.judul) != bukuMap.end()) {
            cout << "Buku sudah ada di perpustakaan." << endl;
            return;
        }

        bukuList.push_back(buku);
        bukuMap[buku.judul] = buku.tahun;
        insertBuku(root, buku);

        if (!bukuAwalDitambahkan) {
            bukuAwalDitambahkan = true;
            cout << "Buku berhasil ditambahkan." << endl;
        }
    }

    void hapusBuku(const string& judul) {
        if (bukuMap.find(judul) == bukuMap.end()) {
            cout << "Buku tidak ada di perpustakaan." << endl;
            return;
        }

        bukuList.remove_if([&judul](const Buku& buku) {
            return buku.judul == judul;
        });

        bukuMap.erase(judul);
        hapusBuku(root, judul);

        cout << "Buku berhasil dihapus." << endl;
    }

    void tampilDaftarBuku() {
        cout << "\nDaftar buku dalam perpustakaan:" << endl;
        tampilDaftarBuku(root);
    }

    bool cariBuku(const string& judul) {
        return cariBuku(root, judul);
    }

    void tambahAntrianPeminjaman(const Buku& buku) {
        if (bukuMap.find(buku.judul) == bukuMap.end()) {
            cout << "Buku tidak ada di perpustakaan." << endl;
            return;
        }

        antrianPeminjaman.push(buku);
        cout << "Buku " << buku.judul << " ditambahkan ke antrian peminjaman." << endl;
    }

    void prosesPeminjaman() {
        if (antrianPeminjaman.empty()) {
            cout << "Tidak ada buku dalam antrian peminjaman." << endl;
            return;
        }

        Buku buku = antrianPeminjaman.front();
        antrianPeminjaman.pop();
        cout << "Buku " << buku.judul << " dipinjam." << endl;
    }

    void kembalikanBuku(const Buku& buku) {
        if (bukuMap.find(buku.judul) == bukuMap.end()) {
            cout << "Buku tidak ada di perpustakaan." << endl;
            return;
        }

        antrianPeminjaman.push(buku);
        cout << "Buku " << buku.judul << " dikembalikan." << endl;
    }

    void undoPerubahan() {
        if (riwayatPerubahan.empty()) {
            cout << "Tidak ada perubahan yang dapat dibatalkan." << endl;
            return;
        }

        bukuList = riwayatPerubahan.top();
        riwayatPerubahan.pop();

        // Update bukuMap dan bukuSet
        bukuMap.clear();
        bukuSet.clear();
        for (const auto& buku : bukuList) {
            bukuMap[buku.judul] = buku.tahun;
            bukuSet.insert(buku.judul);
        }

        cout << "Perubahan terakhir berhasil dibatalkan." << endl;
    }
};

int main() {
    Perpus perpus;

    while (true) {
        cout << "\n*** Program Pengelola Perpustakaan ***" << endl;
        cout << "Menu:" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Hapus Buku" << endl;
        cout << "3. Cari Buku" << endl;
        cout << "4. Tampil Daftar Buku" << endl;
        cout << "5. Tambah Antrian Peminjaman" << endl;
        cout << "6. Proses Peminjaman" << endl;
        cout << "7. Kembalikan Buku" << endl;
        cout << "8. Undo Perubahan" << endl;
        cout << "9. Keluar" << endl;
        int choice;
        cout << "Pilihan Anda: ";
        cin >> choice;

        if (choice == 1) {
            Buku buku;
            cout << "\n**Tambah Buku**" << endl;
            cout << "Masukkan judul: ";
            cin.ignore();
            getline(cin, buku.judul);
            cout << "Masukkan penulis: ";
            getline(cin, buku.penulis);
            cout << "Masukkan tahun: ";
            cin >> buku.tahun;

            perpus.tambahBuku(buku);
        }
        else if (choice == 2) {
            string judul;
            cout << "\n**Menghapus Buku**" << endl;
            cout << "Masukkan judul buku yang akan dihapus: ";
            cin.ignore();
            getline(cin, judul);

            perpus.hapusBuku(judul);
        }
        else if (choice == 3) {
            string judul;
            cout << "\n**Pencarian Buku**" << endl;
            cout << "Masukkan judul buku yang akan dicari: ";
            cin.ignore();
            getline(cin, judul);

            if (perpus.cariBuku(judul)) {
                cout << "Buku ditemukan dalam perpustakaan." << endl;
            } 
            else {
                cout << "Buku tidak ditemukan dalam perpustakaan." << endl;
            }
        }
        else if (choice == 4) {
            perpus.tampilDaftarBuku();
        }
        else if (choice == 5) {
            Buku buku;
            cout << "\n**Tambah Antrian Peminjaman**" << endl;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, buku.judul);

            perpus.tambahAntrianPeminjaman(buku);
        }
        else if (choice == 6) {
            cout << "\n**Proses Peminjaman**" << endl;
            perpus.prosesPeminjaman();
        }
        else if (choice == 7) {
            Buku buku;
            cout << "\n**Kembalikan Buku**" << endl;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, buku.judul);

            perpus.kembalikanBuku(buku);
        }
        else if (choice == 8) {
            cout << "\n**Undo Perubahan**" << endl;
            perpus.undoPerubahan();
        }
        else if (choice == 9) {
            break;
        }
        else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
