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
    stack<Buku> bukuStack;
    queue<Buku> bukuQueue;
    set<string> bukuSet;
    map<string, int> bukuMap;

    struct TreeNode {
        Buku buku;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const Buku& buku) : buku(buku), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

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
            cout << node->buku.judul << " oleh " << node->buku.penulis << " (" << node->buku.tahun << ")" << endl;
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
    Perpus() : root(nullptr) {
        // Menambahkan beberapa buku pada awal program
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
        bukuList.push_back(buku);
        bukuStack.push(buku);
        bukuQueue.push(buku);
        bukuSet.insert(buku.judul);
        bukuMap[buku.judul] = buku.tahun;
        insertBuku(root, buku);
    }

    void hapusBuku(const string& judul) {
        bukuList.remove_if([&judul](const Buku& buku) {
            return buku.judul == judul;
        });

        stack<Buku> tempStack;
        while (!bukuStack.empty()) {
            Buku topBuku = bukuStack.top();
            bukuStack.pop();
            if (topBuku.judul != judul) {
                tempStack.push(topBuku);
            }
        }
        while (!tempStack.empty()) {
            bukuStack.push(tempStack.top());
            tempStack.pop();
        }

        queue<Buku> tempQueue;
        while (!bukuQueue.empty()) {
            Buku frontBuku = bukuQueue.front();
            bukuQueue.pop();
            if (frontBuku.judul != judul) {
                tempQueue.push(frontBuku);
            }
        }
        while (!tempQueue.empty()) {
            bukuQueue.push(tempQueue.front());
            tempQueue.pop();
        }

        bukuSet.erase(judul);
        bukuMap.erase(judul);
        hapusBuku(root, judul);
    }

    void tampilDaftarBuku() {
        cout << "Daftar buku dalam perpustakaan:" << endl;
        tampilDaftarBuku(root);
    }

    bool cariBuku(const string& judul) {
        return cariBuku(root, judul);
    }
};

class Hubbuku {
private:
    map<string, list<string>> daftHub;

public:
    void tambahHub(const string& buku1, const string& buku2) {
        daftHub[buku1].push_back(buku2);
        daftHub[buku2].push_back(buku1);
    }

    void hapusHub(const string& buku1, const string& buku2) {
        daftHub[buku1].remove(buku2);
        daftHub[buku2].remove(buku1);
    }

    void tampilBukuTerhub(const string& buku) {
        cout << "Buku terhubung dengan " << buku << ":" << endl;
        for (const auto& bukuTerhub : daftHub[buku]) {
            cout << bukuTerhub << endl;
        }
    }
};

class Himpunan {
private:
    map<string, string> parent;

    string cariHim(const string& buku) {
        if (parent[buku] == buku) {
            return buku;
        }
        return cariHim(parent[buku]);
    }

public:
    void buatHim(const string& buku) {
        parent[buku] = buku;
    }

    void gabungHim(const string& buku1, const string& buku2) {
        string parent1 = cariHim(buku1);
        string parent2 = cariHim(buku2);
        parent[parent1] = parent2;
    }

    bool cekHimBuku(const string& buku1,const string& buku2) {
        return cariHim(buku1) == cariHim(buku2);
    }
};

int main() {
    Perpus perpus;
    Hubbuku hub;
    Himpunan himPisah;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Hapus Buku" << endl;
        cout << "3. Cari Buku" << endl;
        cout << "4. Tampil Daftar Buku" << endl;
        cout << "5. Tambah Buku Terkait" << endl;
        cout << "6. Tampil Buku Terkait" << endl;
        cout << "7. Periksa Himpunan yang Sama" << endl;
        cout << "8. Keluar" << endl;
        //tambah judul selamat datang, konfirmasi hapus
        int choice;
        cout << "Pilihan Anda: ";
        cin >> choice;

        if (choice == 1) {
            Buku buku;
            cout << "Masukkan judul: ";
            cin.ignore();
            getline(cin, buku.judul);
            cout << "Masukkan penulis: ";
            getline(cin, buku.penulis);
            cout << "Masukkan tahun: ";
            cin >> buku.tahun;

            perpus.tambahBuku(buku);
            himPisah.buatHim(buku.judul);
        } else if (choice == 2) {
            string judul;
            cout << "Masukkan judul buku yang akan dihapus: ";
            cin.ignore();
            getline(cin, judul);

            perpus.hapusBuku(judul);
        } else if (choice == 3) {
            string judul;
            cout << "Masukkan judul buku yang akan dicari: ";
            cin.ignore();
            getline(cin, judul);

            if (perpus.cariBuku(judul)) {
                cout << "Buku ditemukan dalam perpustakaan." << endl;
            } else {
                cout << "Buku tidak ditemukan dalam perpustakaan." << endl;
            }
        } else if (choice == 4) {
            perpus.tampilDaftarBuku();
        } else if (choice == 5) {
            string buku1, buku2;
            cout << "Masukkan buku pertama: ";
            cin.ignore();
            getline(cin, buku1);
            cout << "Masukkan buku kedua: ";
            getline(cin, buku2);

            hub.tambahHub(buku1, buku2);
            himPisah.gabungHim(buku1, buku2);
        } else if (choice == 6) {
            string buku;
            cout << "Masukkan buku judul: ";
            cin.ignore();
            getline(cin, buku);

            hub.tampilBukuTerhub(buku);
        } else if (choice == 7) {
            string buku1, buku2;
            cout << "Masukkan buku pertama: ";
            cin.ignore();
            getline(cin, buku1);
            cout << "Masukkan buku kedua: ";
            getline(cin, buku2);

            if (himPisah.cekHimBuku(buku1, buku2)) {
                cout << "Buku-buku berada dalam himpunan yang sama." << endl;
            } else {
                cout << "Buku-buku tidak berada dalam himpunan yang sama." << endl;
            }
        } else if (choice == 8) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
