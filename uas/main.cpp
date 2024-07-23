#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "coba123";
const char* dbname = "perpustakaan";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Berhasil terhubung ke database." << endl;
        } else {
            cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init gagal" << endl;
    }
    return conn;
}

void register_user(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "INSERT INTO users (username, password) VALUES ('" << username << "', '" << password << "')";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Pendaftaran pengguna gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Pengguna berhasil didaftarkan." << endl;
        }
        mysql_close(conn);
    }
}

void register_admin(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "INSERT INTO admins (username, password) VALUES ('" << username << "', '" << password << "')";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Pendaftaran admin gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Admin berhasil didaftarkan." << endl;
        }
        mysql_close(conn);
    }
}

bool login_user(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "SELECT * FROM users WHERE username = '" << username << "' AND password = '" << password << "'";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Login gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return false;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res && mysql_num_rows(res) > 0) {
            mysql_free_result(res);
            mysql_close(conn);
            return true;
        }
        mysql_free_result(res);
        mysql_close(conn);
    }
    return false;
}

bool login_admin(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "SELECT * FROM admins WHERE username = '" << username << "' AND password = '" << password << "'";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Login gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return false;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res && mysql_num_rows(res) > 0) {
            mysql_free_result(res);
            mysql_close(conn);
            return true;
        }
        mysql_free_result(res);
        mysql_close(conn);
    }
    return false;
}

void delete_all_users() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "DELETE FROM users")) {
            cerr << "Penghapusan semua pengguna gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Semua pengguna berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void delete_all_data() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "DELETE FROM users")) {
            cerr << "Penghapusan semua pengguna gagal: " << mysql_error(conn) << endl;
        }
        if (mysql_query(conn, "DELETE FROM admins")) {
            cerr << "Penghapusan semua admin gagal: " << mysql_error(conn) << endl;
        }
        if (mysql_query(conn, "DELETE FROM books")) {
            cerr << "Penghapusan semua buku gagal: " << mysql_error(conn) << endl;
        }
        cout << "Semua data berhasil dihapus." << endl;
        mysql_close(conn);
    }
}

void add_book(const string& title, const string& author, const string& publisher, const string& year) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "INSERT INTO books (title, author, publisher, year) VALUES ('" << title << "', '" << author << "', '" << publisher << "', '" << year << "')";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "Penambahan buku gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil ditambahkan." << endl;
        }
        mysql_close(conn);
    }
}

void get_books() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM books")) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Judul: " << row[1] << ", Penulis: " << row[2] << ", Penerbit: " << row[3] << ", Tahun: " << row[4] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_book(int book_id, const string& title, const string& author, const string& publisher, const string& year) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE books SET title = '" << title << "', author = '" << author << "', publisher = '" << publisher << "', year = '" << year << "' WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

void delete_book(int book_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM books WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void admin_menu() {
    int choice;
    while (true) {
        cout << "\nMenu Admin:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Semua Buku\n";
        cout << "3. Perbarui Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Logout\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            string title, author, publisher, year;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, title);
            cout << "Masukkan penulis buku: ";
            getline(cin, author);
            cout << "Masukkan penerbit buku: ";
            getline(cin, publisher);
            cout << "Masukkan tahun terbit: ";
            getline(cin, year);
            add_book(title, author, publisher, year);
        } else if (choice == 2) {
            get_books();
        } else if (choice == 3) {
            int book_id;
            string title, author, publisher, year;
            cout << "Masukkan ID buku yang akan diperbarui: ";
            cin >> book_id;
            cin.ignore();
            cout << "Masukkan judul baru: ";
            getline(cin, title);
            cout << "Masukkan penulis baru: ";
            getline(cin, author);
            cout << "Masukkan penerbit baru: ";
            getline(cin, publisher);
            cout << "Masukkan tahun terbit baru: ";
            getline(cin, year);
            update_book(book_id, title, author, publisher, year);
        } else if (choice == 4) {
            int book_id;
            cout << "Masukkan ID buku yang akan dihapus: ";
            cin >> book_id;
            delete_book(book_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void user_menu() {
    while (true) {
        cout << "\nMenu Pengguna:\n";
        cout << "1. Tampilkan Semua Buku\n";
        cout << "2. Logout\n";
        cout << "Masukkan pilihan: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            get_books();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void register_menu() {
    int choice;
    string username, password;

    while (true) {
        cout << "\nMenu Pendaftaran:\n";
        cout << "1. Daftarkan Pengguna\n";
        cout << "2. Daftarkan Admin\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Masukkan username: ";
            getline(cin, username);
            cout << "Masukkan password: ";
            getline(cin, password);
            register_user(username, password);
        } else if (choice == 2) {
            cout << "Masukkan username: ";
            getline(cin, username);
            cout << "Masukkan password: ";
            getline(cin, password);
            register_admin(username, password);
        } else if (choice == 3) {
            return;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void login_menu() {
    int choice;
    string username, password;
    int login_attempts = 0;
    const int max_attempts = 3;

    while (true) {
        cout << "\nMenu Login:\n";
        cout << "1. Login Pengguna\n";
        cout << "2. Login Admin\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;
        cin.ignore();

        bool loggedIn = false;

        if (choice == 1) {
            cout << "Masukkan username: ";
            getline(cin, username);
            cout << "Masukkan password: ";
            getline(cin, password);
            loggedIn = login_user(username, password);
            if (loggedIn) {
                user_menu();
                return;
            }
        } else if (choice == 2) {
            cout << "Masukkan username: ";
            getline(cin, username);
            cout << "Masukkan password: ";
            getline(cin, password);
            loggedIn = login_admin(username, password);
            if (loggedIn) {
                admin_menu();
                return;
            }
        } else if (choice == 3) {
            return;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        if (!loggedIn) {
            login_attempts++;
            cout << "Login gagal. Percobaan " << login_attempts << " dari " << max_attempts << "." << endl;
            if (choice == 1 && login_attempts >= max_attempts) {
                delete_all_users();
                cout << "Semua data pengguna telah dihapus karena terlalu banyak percobaan login yang gagal." << endl;
                break;
            } else if (choice == 2 && login_attempts >= max_attempts) {
                delete_all_data();
                cout << "Semua data telah dihapus karena terlalu banyak percobaan login yang gagal." << endl;
                break;
            }
        }
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu Utama:\n";
        cout << "1. Daftar\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            register_menu();
        } else if (choice == 2) {
            login_menu();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}
