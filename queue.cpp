#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Library untuk fungsi string

#define MAX_QUEUE_SIZE 5
#define MAX_NAME_LENGTH 50 // Panjang maksimum nama pasien
#define MAX_DISEASE_LENGTH 50 // Panjang maksimum nama penyakit
#define MAX_DOCTOR_NAME_LENGTH 50 // Panjang maksimum nama dokter

// Struktur data untuk pasien
typedef struct {
    int nomor_antrian;
    char nama[MAX_NAME_LENGTH];
    int umur;
    char penyakit[MAX_DISEASE_LENGTH];
    float harga;
    char nama_dokter[MAX_DOCTOR_NAME_LENGTH];
} Pasien;

// Struktur data untuk queue
typedef struct {
    Pasien data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Fungsi untuk mengecek apakah queue kosong
int is_empty(Queue *queue) {
    return (queue->front == -1 && queue->rear == -1);
}

// Fungsi untuk mengecek apakah queue penuh
int is_full(Queue *queue) {
    return ((queue->rear + 1) % MAX_QUEUE_SIZE == queue->front);
}

// Fungsi untuk menambahkan elemen ke dalam queue (Enqueue)
void enqueue(Queue *queue, int nomor_antrian, char *nama, int umur, char *penyakit, float harga, char *nama_dokter) {
    if (is_full(queue)) {
        printf("Queue penuh. Tidak dapat menambahkan elemen.\n");
    } else {
        if (is_empty(queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
        }
        queue->data[queue->rear].nomor_antrian = nomor_antrian;
        strcpy(queue->data[queue->rear].nama, nama);
        queue->data[queue->rear].umur = umur;
        strcpy(queue->data[queue->rear].penyakit, penyakit);
        queue->data[queue->rear].harga = harga;
        strcpy(queue->data[queue->rear].nama_dokter, nama_dokter);
        printf("Pasien %s dengan nomor antrian %d ditambahkan ke dalam antrian.\n", nama, nomor_antrian);
    }
}

// Fungsi untuk mengeluarkan elemen dari queue (Dequeue)
void dequeue(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue kosong. Tidak ada pasien yang bisa dikeluarkan.\n");
    } else {
        Pasien removed_patient = queue->data[queue->front];
        
        printf("Pasien %s dengan nomor antrian %d, umur %d tahun, penyakit %s, ditangani oleh Dokter %s, dan harga Rp%.2f telah selesai dilayani dan dikeluarkan dari antrian.\n", 
                removed_patient.nama, removed_patient.nomor_antrian, removed_patient.umur, removed_patient.penyakit, removed_patient.nama_dokter, removed_patient.harga);
        
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
        }
    }
}

// Fungsi untuk menampilkan elemen-elemen dalam queue
void display(Queue *queue) {
    if (is_empty(queue)) {
        printf("Antrian kosong.\n");
    } else {
        printf("Isi antrian:\n");
        int i = queue->front;
        while (i != queue->rear) {
            printf("%d. Nama: %s, Nomor Antrian: %d, Umur: %d tahun, Penyakit: %s, Nama Dokter: %s, Harga: Rp%.2f\n", 
                    i+1, queue->data[i].nama, queue->data[i].nomor_antrian, queue->data[i].umur, queue->data[i].penyakit, queue->data[i].nama_dokter, queue->data[i].harga);
            i = (i + 1) % MAX_QUEUE_SIZE;
        }
        printf("%d. Nama: %s, Nomor Antrian: %d, Umur: %d tahun, Penyakit: %s, Nama Dokter: %s, Harga: Rp%.2f\n", 
                i+1, queue->data[i].nama, queue->data[i].nomor_antrian, queue->data[i].umur, queue->data[i].penyakit, queue->data[i].nama_dokter, queue->data[i].harga);
    }
}

int main() {
    Queue queue;
    queue.front = queue.rear = -1;

    int choice, nomor_antrian, umur;
    char nama[MAX_NAME_LENGTH];
    char penyakit[MAX_DISEASE_LENGTH];
    float harga;
    char nama_dokter[MAX_DOCTOR_NAME_LENGTH];

    do {
        printf("\n=== MENU ANTRIAN PUSKESMAS ESAUNGGUL ===\n");
        printf("1. Tambahkan pasien ke dalam antrian (Enqueue)\n");
        printf("2. Keluarkan pasien dari antrian (Dequeue)\n");
        printf("3. Tampilkan antrian saat ini (Display)\n");
        printf("4. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nomor antrian pasien: ");
                scanf("%d", &nomor_antrian);
                printf("Masukkan nama pasien: ");
                scanf(" %[^\n]s", nama);
                printf("Masukkan umur pasien: ");
                scanf("%d", &umur);
                printf("Masukkan penyakit pasien: ");
                scanf(" %[^\n]s", penyakit);
                printf("Masukkan harga pengobatan pasien (Rp): ");
                scanf("%f", &harga);
                printf("Masukkan nama dokter yang menangani: ");
                scanf(" %[^\n]s", nama_dokter);
                enqueue(&queue, nomor_antrian, nama, umur, penyakit, harga, nama_dokter);
                break;
            case 2:
                dequeue(&queue);
                break;
            case 3:
                display(&queue);
                break;
            case 4:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid. Masukkan pilihan yang benar.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}