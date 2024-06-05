/*=======================================================================================================================
Program Proyek Akhir Semester
Judul Program : "Digital Bookstore Inventory Navigator"
Program ini akan menyimpan buku dan barang ATK beserta informasinya (judul, tahun terbit, harga, kode, dan lain-lain)
ke dalam sebuah file inventaris, lalu file inventaris tersebut dapat digunakan dalam program ini agar user dapat mencari
buku atau barang ATK dalam database inventaris.

Pemrograman Lanjut Kelas 02

Rabu, 22 Mei 2024

Kelompok 22

Anggota : 
Adhikananda Wira Januar     / 2306267113
Muhammad Hilmi Al Muttaqi   / 2306367082

Edisi Pertama
Link github : https://github.com/adhikwj/PAS-22
=======================================================================================================================*/

/*=======================================================================================================================
Program Proyek Akhir Semester
Judul Program : "Digital Bookstore Inventory Navigator"
Program ini akan menyimpan buku dan barang ATK beserta informasinya (judul, tahun terbit, harga, kode, dan lain-lain)
ke dalam sebuah file inventaris, lalu file inventaris tersebut dapat digunakan dalam program ini agar user dapat mencari
buku atau barang ATK dalam database inventaris.

Pemrograman Lanjut Kelas 02

Rabu, 22 Mei 2024

Kelompok 22

Anggota : 
Adhikananda Wira Januar     / 2306267113
Muhammad Hilmi Al Muttaqi   / 2306367082

Edisi Pertama
Link github : https://github.com/adhikwj/PAS-22
=======================================================================================================================*/


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "PAS-22.h"

#define MAX_STRING_LENGTH 100

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


int main() {
    Item *inventory = NULL;
    Cart *cart = NULL;
    feedbackBox feedback[100];
    int feedbackCount = 0;
    
    loadInventoryFromFile(&inventory);
    loadFeedbackFromFile(feedback, &feedbackCount);

    int choice, sortOption;
    char keyword[MAX_STRING_LENGTH];
    char user[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];

    do {
    	
    	system("CLS");
    	printf(CYAN "----------------------------------" RESET);
        printf(CYAN "\n=== Database Toko Buku dan ATK ===\n" RESET);
        printf(CYAN "----------------------------------\n" RESET);
        printf("1. " GREEN "Mode Karyawan\n" RESET);
        printf("2. " YELLOW "Mode Customer\n" RESET);
        printf("3. " RED "Keluar\n" RESET);
        printf(CYAN "----------------------------------\n" RESET);
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	do{
            	printf("Input username: ");
            	scanf("%s", &user);
            	
            	if(strcmp(user, "admin") != 0){
            		printf("Username invalid.\n");
				}
				
				} while (strcmp(user, "admin") != 0);
				
				do{
            	printf("Input password: ");
            	scanf("%s", &password);
            	
            	if(strcmp(password, "abc123") != 0){
            		printf("Password invalid.\n");
				}
				
				} while (strcmp(password, "abc123") != 0);
				
                do {
                	system("CLS");
                	printf(GREEN "---------------------------------------" RESET);
                    printf(GREEN "\n===\t     Mode Karyawan\t    ===\n" RESET);
                    printf(GREEN "---------------------------------------\n" RESET);
                    printf("1. Tambah barang ke inventory\n");
                    printf("2. Hapus barang dari inventory\n");
                    printf("3. Kurangi stok barang dari inventory\n");
                    printf("4. Tambahkan stok barang ke inventory\n");
                    printf("5. Ubah harga barang\n");
                    printf("6. Tampilkan inventory\n");
                    printf("7. Lihat kotak saran\n");
                    printf("8. Kembali ke menu utama\n");
                    printf(GREEN "---------------------------------------\n" RESET);
                    warningStock(inventory);
                    printf("Pilihan Anda: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addNewItem(&inventory);
                            system("pause");
                            system("CLS");
                            break;
                        case 2:
                            removeItem(&inventory);
                            system("pause");
                            system("CLS");
                            break;
                        case 3:
                            reduceStock(inventory);
                            system("pause");
                            system("CLS");
                            break;
                        case 4:
                            addStock(inventory);
                            system("pause");
                            system("CLS");
                            break;
                        case 5:
                            updatePrice(inventory);
                            system("pause");
                            system("CLS");
                            break;
                        case 6:
                            printf("\nUrutkan berdasarkan (1. Nama Barang, 2. Jenis): ");
                            int sortOption;
                            scanf("%d", &sortOption);
                            displayInventory(inventory, sortOption);
                            system("pause");
                            system("CLS");
                            break;
                        case 7:
                        	displayFeedback(feedback, feedbackCount);
                            system("pause");
                            system("CLS");
                            break;
                        case 8:
                            break;
                        default:
                            printf(RED "Pilihan tidak valid.\n" RESET);
                            system("pause");
                            system("CLS");
                    }
                } while (choice != 8);
                break;
            case 2:
                do {
                	saveFeedbackToFile(feedback, feedbackCount);
                	system("CLS");
                	printf(YELLOW "-----------------------------------" RESET);
                    printf(YELLOW "\n===\t  Mode Customer  \t===\n" RESET);
                    printf(YELLOW "-----------------------------------\n" RESET);
                    printf("1. Cari Barang\n");
                    printf("2. Cari Berdasarkan Jenis Barang\n");
                    printf("3. Tampilkan Keranjang\n");
                    printf("4. Beri Feedback\n");
                    printf("5. Kembali ke menu utama\n");
                    printf(YELLOW "-----------------------------------\n" RESET);
                    printf("Pilihan Anda: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printf("Masukkan kata kunci: ");
                            scanf(" %[^\n]s", keyword); // Menggunakan format %[^\n]s untuk membaca spasi
                            searchItemCustomer(inventory, keyword,  1);
                            system("pause");
                            system("CLS");
                            break;
                        case 2:
                            printf("Masukkan kata kunci (Buku / ATK): ");
                            scanf(" %[^\n]s", keyword); // Menggunakan format %[^\n]s untuk membaca spasi
                            searchItem(inventory, keyword, 2);
                            system("pause");
                            system("CLS");
                            break;
                        case 3:
                            printf("\nUrutkan berdasarkan (1. Alfabet, 2. Jenis): ");
			                int sortOption;
			                scanf("%d", &sortOption);
			                displayCartInventory(cart, sortOption);
			                system("pause");
			                break;
                        case 4:
                            getFeedback(feedback, &feedbackCount);
                        	system("pause");
                            system("CLS");
							break;
                        case 5:
                            break;
                        default:
                            printf(RED "Pilihan tidak valid.\n" RESET);
                            system("pause");
                            system("CLS");
                    }
                } while (choice != 5);
                break;
            case 3:
                saveInventoryToFile(inventory);
                saveFeedbackToFile(feedback, feedbackCount);
                system("CLS");
                printf("Terima kasih, program selesai.\n");
                break;
            default:
                printf(RED "Pilihan tidak valid.\n" RESET);
                system("pause");
                system("CLS");
        }
    } while (choice != 3);

    freeInventory(inventory);
    return 0;
}
