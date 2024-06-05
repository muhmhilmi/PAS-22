/*=======================================================================================================================
Header Program Akhir Semester

File Header ini berisi kumpulan-kumpulan function yang kelompok kami gunakan pada program C kami yang berjudul 
"Digital Bookstore Inventory Navigator". Setiap function berada pada header, sehingga dalam program utama kami hanya
terdapat tampilan menu dan kode untuk menerima input.

Pemrograman Lanjut Kelas 02

Rabu, 22 Mei 2024

Kelompok 22

Anggota : 
Adhikananda Wira Januar     / 2306267113
Muhammad Hilmi Al Muttaqi   / 2306367082

Edisi Pertama
=======================================================================================================================*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 100

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef struct Item {
    char name[MAX_STRING_LENGTH];
    char type[MAX_STRING_LENGTH];
    int year;
    float price;
    int quantity;
    struct Item *next;
} Item;

typedef struct feedbackBox{
	char message[MAX_STRING_LENGTH];
	char sender[MAX_STRING_LENGTH];
    int number;
} feedbackBox;

typedef struct Cart {
    Item *item;
    int quantity;
    struct Cart *next;
} Cart;

typedef struct CartItem {
    Item *item;
    int quantity;
} CartItem;

void saveInventoryToFile(Item *head) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    Item *current = head;
    while (current != NULL) {
        fprintf(file, "%s;%s;%d;%.2f;%d\n", current->name, current->type,
                current->year, current->price, current->quantity);
        current = current->next;
    }

    fclose(file);
}

void loadInventoryFromFile(Item **head) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf(YELLOW "File inventaris tidak ditemukan.\n" RESET);
        return;
    }

    Item *current = NULL;
    while (1) {
        Item *newItem = malloc(sizeof(Item));
        if (fscanf(file, "%[^;];%[^;];%d;%f;%d\n", newItem->name, newItem->type,
                    &newItem->year, &newItem->price, &newItem->quantity) != 5) {
            free(newItem);
            break;
        }
        newItem->next = NULL;

        if (*head == NULL) {
            *head = newItem;
            current = *head;
        } else {
            current->next = newItem;
            current = newItem;
        }
    }

    fclose(file);
}

void sortInventoryByName(Item **head) {
    if (*head == NULL) return;

    int swapped;
    Item *ptr1;
    Item *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // Swap data
                char tempName[MAX_STRING_LENGTH], tempType[MAX_STRING_LENGTH];
                int tempYear, tempQuantity;
                float tempPrice;

                strcpy(tempName, ptr1->name);
                strcpy(tempType, ptr1->type);
                tempYear = ptr1->year;
                tempPrice = ptr1->price;
                tempQuantity = ptr1->quantity;

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->type, ptr1->next->type);
                ptr1->year = ptr1->next->year;
                ptr1->price = ptr1->next->price;
                ptr1->quantity = ptr1->next->quantity;

                strcpy(ptr1->next->name, tempName);
                strcpy(ptr1->next->type, tempType);
                ptr1->next->year = tempYear;
                ptr1->next->price = tempPrice;
                ptr1->next->quantity = tempQuantity;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortInventoryByType(Item **head) {
    if (*head == NULL) return;

    int swapped;
    Item *ptr1;
    Item *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->type, ptr1->next->type) > 0) {
                // Swap data
                char tempName[MAX_STRING_LENGTH], tempType[MAX_STRING_LENGTH];
                int tempYear, tempQuantity;
                float tempPrice;

                strcpy(tempName, ptr1->name);
                strcpy(tempType, ptr1->type);
                tempYear = ptr1->year;
                tempPrice = ptr1->price;
                tempQuantity = ptr1->quantity;

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->type, ptr1->next->type);
                ptr1->year = ptr1->next->year;
                ptr1->price = ptr1->next->price;
                ptr1->quantity = ptr1->next->quantity;

                strcpy(ptr1->next->name, tempName);
                strcpy(ptr1->next->type, tempType);
                ptr1->next->year = tempYear;
                ptr1->next->price = tempPrice;
                ptr1->next->quantity = tempQuantity;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void displayInventory(Item *head, int sortOption) {
    if (head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }

    if (sortOption == 1) {
        sortInventoryByName(&head);
    } else if (sortOption == 2) {
        sortInventoryByType(&head);
    }

    printf(CYAN "\n=== Inventaris ===\n" RESET);
    printf("%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
    printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");

    Item *current = head;
    while (current != NULL) {
        printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                current->year, current->price, current->quantity);
        current = current->next;
    }
}


void addNewItem(Item **head) {
    Item *newItem = malloc(sizeof(Item));
    if (!newItem) {
        printf(RED "Memori tidak cukup.\n" RESET);
        return;
    }

    printf("Jenis barang (Buku/ATK): ");
    scanf("%s", newItem->type);
    printf("Nama barang: ");
    scanf(" %[^\n]s", newItem->name); // Menggunakan format %[^\n]s untuk membaca spasi
    printf("Tahun: ");
    scanf("%d", &newItem->year);
    printf("Harga: Rp. ");
    scanf("%f", &newItem->price);
    printf("Jumlah: ");
    scanf("%d", &newItem->quantity);

    newItem->next = *head;
    *head = newItem;
    printf(GREEN "Barang berhasil ditambahkan ke inventory.\n" RESET);
}

void addStock(Item *head) {
    if (head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }
    char keyword[MAX_STRING_LENGTH];
    int x;
    
    do {
        printf("Masukkan nama barang yang akan ditambah stoknya: ");
        scanf(" %[^\n]s", keyword); // Menggunakan format %[^\n]s untuk membaca spasi
        
        char name[MAX_STRING_LENGTH];
        char keylow[MAX_STRING_LENGTH];
        
        int found = 0;
        Item *current = head;
        while (current != NULL) {
            strcpy(name, current->name);
            int c;
            for (c = 0; name[c]; c++) {
                name[c] = tolower(name[c]);
            }

            strcpy(keylow, keyword);
            for (c = 0; keylow[c]; c++) {
                keylow[c] = tolower(keylow[c]);
            }

            if (strcmp(name, keylow) == 0) {
                int addAmount;
                printf("Masukkan jumlah stok yang akan ditambah: ");
                scanf("%d", &addAmount);
                if (addAmount <= 0) {
                    printf(RED "Stok yang diminta invalid.\n" RESET);
                } else {
                    current->quantity += addAmount;
                    printf(GREEN "Stok barang berhasil ditambah.\n" RESET);
                    x = 2;
                }
                found = 1;
                break;
            }
            current = current->next;
        }

        if (!found) {
            printf("Menampilkan daftar barang yang mirip dengan \"%s\"\n", keyword);
            printf("\n%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
            printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");

            current = head;
            while (current != NULL) {
                strcpy(name, current->name);
                int c;
                for (c = 0; name[c]; c++) {
                    name[c] = tolower(name[c]);
                }

                strcpy(keylow, keyword);
                for (c = 0; keylow[c]; c++) {
                    keylow[c] = tolower(keylow[c]);
                }

                if (strstr(name, keylow) != NULL) {
                    printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                            current->year, current->price, current->quantity);
                }
                current = current->next;
            }
            printf("\nKetik 1 untuk mencari lagi, 2 untuk kembali ke menu: ");
            scanf("%d", &x);
        }
    } while (x != 2);
}

void reduceStock(Item *head) {
    if (head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }
    char keyword[MAX_STRING_LENGTH];
    int x = 0;
    
    do {
        printf("Masukkan nama barang yang akan dikurangi stoknya: ");
        scanf(" %[^\n]s", keyword); // Menggunakan format %[^\n]s untuk membaca spasi
        
        char name[MAX_STRING_LENGTH];
        char keylow[MAX_STRING_LENGTH];
        
        int found = 0;
        Item *current = head;
        while (current != NULL) {
            strcpy(name, current->name);
            int c;
			for (c = 0; name[c]; c++) {
                name[c] = tolower(name[c]);
            }

            strcpy(keylow, keyword);
            for (c = 0; keylow[c]; c++) {
                keylow[c] = tolower(keylow[c]);
            }

            if (strcmp(name, keylow) == 0) {
                int reduceAmount;
                printf("Masukkan jumlah stok yang akan dikurangi: ");
                scanf("%d", &reduceAmount);
                if (reduceAmount > current->quantity) {
                    printf(RED "Stok yang diminta melebihi jumlah yang tersedia.\n" RESET);
                } else {
                    current->quantity -= reduceAmount;
                    printf(GREEN "Stok barang berhasil dikurangi.\n" RESET);
                    x = 2;
                }
                found = 1;
                break;
            }
            current = current->next;
        }

        if (!found) {
            printf("Menampilkan daftar barang yang mirip dengan \"%s\"\n", keyword);
            printf("\n%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
            printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");

            current = head;
            while (current != NULL) {
                strcpy(name, current->name);
                int c;
				for (c = 0; name[c]; c++) {
                    name[c] = tolower(name[c]);
                }

                strcpy(keylow, keyword);
                for (c = 0; keylow[c]; c++) {
                    keylow[c] = tolower(keylow[c]);
                }

                if (strstr(name, keylow) != NULL) {
                    printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                            current->year, current->price, current->quantity);
                }
                current = current->next;
            }
            printf("\nKetik 1 untuk mencari lagi, 2 untuk kembali ke menu: ");
            scanf("%d", &x);
        }
    } while (x != 2);
}

void removeItem(Item **head) {
    if (*head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }

    char keyword[MAX_STRING_LENGTH];
    int x = 0;

    do {
        printf("Masukkan nama barang yang akan dihapus: ");
        scanf(" %[^\n]s", keyword); // Menggunakan format %[^\n]s untuk membaca spasi
        
        char name[MAX_STRING_LENGTH];
        char keylow[MAX_STRING_LENGTH];

        Item *prev = NULL;
        Item *current = *head;
        int found = 0;
        while (current != NULL) {
            strcpy(name, current->name);
            int c;
			for (c = 0; name[c]; c++) {
                name[c] = tolower(name[c]);
            }

            strcpy(keylow, keyword);
            for (c = 0; keylow[c]; c++) {
                keylow[c] = tolower(keylow[c]);
            }

            if (strcmp(name, keylow) == 0) {
                if (prev == NULL) {
                    *head = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                printf(GREEN "Barang berhasil dihapus dari inventory.\n" RESET);
                x = 2;
                found = 1;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found) {
            printf("Menampilkan daftar barang yang mirip dengan \"%s\"\n", keyword);
            printf("\n%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
            printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");

            current = *head;
            while (current != NULL) {
                strcpy(name, current->name);
                int c;
				for (c = 0; name[c]; c++) {
                    name[c] = tolower(name[c]);
                }

                strcpy(keylow, keyword);
                for (c = 0; keylow[c]; c++) {
                    keylow[c] = tolower(keylow[c]);
                }

                if (strstr(name, keylow) != NULL) {
                    printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                            current->year, current->price, current->quantity);
                }
                current = current->next;
            }
            printf("\nKetik 1 untuk mencari lagi, 2 untuk kembali ke menu: ");
            scanf("%d", &x);
        }
    } while (x != 2);
}

void updatePrice(Item *head) {
    if (head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }

    char keyword[MAX_STRING_LENGTH];
    int x = 0;

    do {
        printf("Masukkan nama barang yang akan diperbarui harganya: ");
        scanf(" %[^\n]s", keyword); // Menggunakan format %[^\n]s untuk membaca spasi

        char name[MAX_STRING_LENGTH];
        char keylow[MAX_STRING_LENGTH];

        int found = 0;
        Item *current = head;
        while (current != NULL) {
            strcpy(name, current->name);
            int c;
			for (c = 0; name[c]; c++) {
                name[c] = tolower(name[c]);
            }

            strcpy(keylow, keyword);
            for (c = 0; keylow[c]; c++) {
                keylow[c] = tolower(keylow[c]);
            }

            if (strcmp(name, keylow) == 0) {
                printf("Harga baru: Rp. ");
                scanf("%f", &current->price);
                printf(GREEN "Harga barang berhasil diperbarui.\n" RESET);
                x = 2;
                found = 1;
                break;
            }
            current = current->next;
        }

        if (!found) {
            printf("Menampilkan daftar barang yang mirip dengan \"%s\"\n", keyword);
            printf("\n%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
            printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");

            current = head;
            while (current != NULL) {
                strcpy(name, current->name);
                int c;
				for (c = 0; name[c]; c++) {
                    name[c] = tolower(name[c]);
                }

                strcpy(keylow, keyword);
                for (c = 0; keylow[c]; c++) {
                    keylow[c] = tolower(keylow[c]);
                }

                if (strstr(name, keylow) != NULL) {
                    printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                            current->year, current->price, current->quantity);
                }
                current = current->next;
            }
            printf("\nKetik 1 untuk mencari lagi, 2 untuk kembali ke menu: ");
            scanf("%d", &x);
        }
    } while (x != 2);
}

void searchItem(Item *head, char *keyword, int mode) {
    if (head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }

    char name[MAX_STRING_LENGTH];
    char type[MAX_STRING_LENGTH];
    char keylow[MAX_STRING_LENGTH];

    printf("\nHasil pencarian untuk \"%s\":\n", keyword);
    printf("%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
    printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");

    int found = 0;
    Item *current = head;
    while (current != NULL) {
        strcpy(name, current->name);
        int c;
		for (c = 0; name[c]; c++) {
            name[c] = tolower(name[c]);
        }
        
        strcpy(type, current->type);
		for (c = 0; type[c]; c++) {
            type[c] = tolower(type[c]);
        }

        strcpy(keylow, keyword);
        for (c = 0; keylow[c]; c++) {
            keylow[c] = tolower(keylow[c]);
        }

        if ((mode == 1 && strstr(name, keylow) != NULL)) {
            printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                    current->year, current->price, current->quantity);
            found = 1;
        } else if (mode == 2 && strstr(type, keylow) != NULL) {
        	printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", current->name, current->type,
                    current->year, current->price, current->quantity);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf(RED "Barang tidak ditemukan.\n" RESET);
    }
}

void searchItemCustomer(Item *head, char *keyword, int mode) {
    if (head == NULL) {
        printf(YELLOW "Inventaris kosong.\n" RESET);
        return;
    }
    char name[MAX_STRING_LENGTH];
    char type[MAX_STRING_LENGTH];
    char keylow[MAX_STRING_LENGTH];
    printf("\nHasil pencarian untuk \"%s\":\n", keyword);
    printf("%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
    printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");
    int found = 0;
    Item *current = head;
    int index = 1;
    Item *results[100]; // Array untuk menyimpan hasil pencarian
    while (current != NULL) {
        strcpy(name, current->name);
        int c;
        for (c = 0; name[c]; c++) {
            name[c] = tolower(name[c]);
        }     
        strcpy(type, current->type);
        for (c = 0; type[c]; c++) {
            type[c] = tolower(type[c]);
        }
        strcpy(keylow, keyword);
        for (c = 0; keylow[c]; c++) {
            keylow[c] = tolower(keylow[c]);
        }
        if ((mode == 1 && strstr(name, keylow) != NULL)) {
            printf("%d. %-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", index, current->name, current->type,
                    current->year, current->price, current->quantity);
            results[index - 1] = current;
            found = 1;
            index++;
        } else if (mode == 2 && strstr(type, keylow) != NULL) {
            printf("%d. %-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", index, current->name, current->type,
                    current->year, current->price, current->quantity);
            results[index - 1] = current;
            found = 1;
            index++;
        }
        current = current->next;
    }
    if (!found) {
        printf(RED "Barang tidak ditemukan.\n" RESET);
    } else {
        int choice, quantity;
        printf("Pilih nomor barang yang ingin Anda pilih: ");
        scanf("%d", &choice);
        if (choice > 0 && choice < index) {
            printf("Masukkan jumlah barang yang ingin Anda kurangkan: ");
            scanf("%d", &quantity);
            if (quantity <= results[choice - 1]->quantity) {
                results[choice - 1]->quantity -= quantity;
                printf(YELLOW "Jumlah barang berhasil dikurangi.\n" RESET);
            } else {
                printf(RED "Jumlah barang tidak mencukupi.\n" RESET);
            }
        } else {
            printf(RED "Pilihan tidak valid.\n" RESET);
        }
    }
}

int compareByName(const void *a, const void *b) {
    CartItem *itemA = (CartItem *)a;
    CartItem *itemB = (CartItem *)b;
    return strcmp(itemA->item->name, itemB->item->name);
}

int compareByType(const void *a, const void *b) {
    CartItem *itemA = (CartItem *)a;
    CartItem *itemB = (CartItem *)b;
    return strcmp(itemA->item->type, itemB->item->type);
}

void displayCartInventory(Cart *head, int sortOption) {
    if (head == NULL) {
        printf(YELLOW "Keranjang kosong.\n" RESET);
        return;
    }
    
    Cart *current = head;
    CartItem cartItems[100];
    int i, count = 0;
    
    while (current != NULL) {
        cartItems[count].item = current->item;
        cartItems[count].quantity = current->quantity;
        count++;
        current = current->next;
    }

    if (sortOption == 1) {
        qsort(cartItems, count, sizeof(CartItem), compareByName);
    } else if (sortOption == 2) {
        qsort(cartItems, count, sizeof(CartItem), compareByType);
    }

    printf("\nDaftar Barang di Keranjang:\n");
    printf("%-20s\t\t|%-10s\t|%-10s\t|%-10s\t\t|%-10s\t|\n", "Nama Barang", "Jenis", "Tahun", "Harga", "Jumlah");
    printf("--------------------------------|---------------|---------------|-----------------------|---------------|\n");
    for (i = 0; i < count; i++) {
        printf("%-20s\t\t|%-10s\t|%-10d\t|Rp. %-10.2f\t\t|%-10d\t|\n", cartItems[i].item->name, cartItems[i].item->type,
               cartItems[i].item->year, cartItems[i].item->price, cartItems[i].quantity);
    }
}

void freeInventory(Item *head) {
    Item *current = head;
    while (current != NULL) {
        Item *next = current->next;
        free(current);
        current = next;
    }
}

void saveFeedbackToFile(feedbackBox *feedback, int count) {
    FILE *file = fopen("feedback.txt", "w");
    if (file == NULL) {
        printf(YELLOW "Gagal membuka file.\n" RESET);
        return;
    }
	int i;
    for (i = 0; i < count; i++) {
        if(i == 0){
            feedback[i].number = 1;
        } else{
            feedback[i].number = feedback[i-1].number + 1; 
        }
        fprintf(file, "%s;%s;%d\n", feedback[i].sender, feedback[i].message, feedback[i].number);
    }

    fclose(file);
}

void loadFeedbackFromFile(feedbackBox *feedback, int *count) {
    FILE *file = fopen("feedback.txt", "r");
    if (file == NULL) {
        printf(YELLOW "File feedback tidak ditemukan.\n" RESET);
        return;
    }

    while ((*count < 100) && fscanf(file, "%[^;];%[^;];%d\n", feedback[*count].sender, feedback[*count].message, &feedback[*count].number) == 3) {
        (*count)++;
    }

    fclose(file);
}

void getFeedback(feedbackBox *feedback, int *count){
    printf("Masukkan saran bagi karyawan: ");
    scanf(" %[^\n]s", feedback[*count].message);
    printf("Masukkan nama anda (atau tulis - jika ingin anonymous): ");
    scanf(" %[^\n]s", feedback[*count].sender);
    (*count)++;
    printf("Terimakasih telah memberi feedback bagi kami!\n");
}

void displayFeedback(feedbackBox *feedback, int count){
    if(count == 0){
        printf("Kotak saran masih kosong.\n");
	} else {
		int i;
    	for(i = 0;i < count; i++){
		printf("\nPesan dari %s : ", feedback[i].sender);
		printf("%s \n", feedback[i].message);
		}
	}
}

void addToCart(Cart **cart, Item *item, int quantity) {
    Cart *newNode = (Cart *)malloc(sizeof(Cart));
    newNode->item = item;
    newNode->quantity = quantity;
    newNode->next = *cart;
    *cart = newNode;
}

void removeFromCart(Cart **cart, Item *item) {
    Cart *current = *cart;
    Cart *previous = NULL;
    while (current != NULL && current->item != item) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf(RED "Item tidak ditemukan di keranjang.\n" RESET);
        return;
    }
    if (previous == NULL) {
        *cart = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    printf(GREEN "Item berhasil dihapus dari keranjang.\n" RESET);
}

void warningStock(Item *head){
    int i = 0;
    Item *current = head;
    while (current != NULL) {
        if(current->quantity < 20){
            if(i != 1){
            printf(RED "\n\t   !!! WARNING !!!\n" RESET);
            printf(YELLOW "Stok barang berikut perlu diperbarui! : \n\n" RESET);
            printf("%-20s\t\t|%-10s\t|\n", "Nama Barang", "Jumlah");
            printf("--------------------------------|---------------|\n");
            i++;
            }
            printf("%-20s\t\t|%-10d\t|\n", current->name, current->quantity);
        }
        current = current->next;
    }
    printf("\n");
}
