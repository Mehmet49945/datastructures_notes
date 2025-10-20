// Bağlı Liste Basa-Sona Ekleme, Silme, Yazdirma
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next; // işaretçi 
};

// Prototipler
struct Node* newNode(int newData);
void inputHead(struct Node **head, int newData);
void inputTail(struct Node **head, int newData);
void inputAfter(struct Node* prevNode, int newData);
void deleteNode(struct Node **head, int key);
void displayList(const struct Node *head);
int  menu();

struct Node* newNode(int newData){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = newData;
    node->next = NULL;
    return node;
}

void inputHead(struct Node** head, int newData){
    struct Node* n = newNode(newData);
    n->next = *head;
    *head = n;
}

// araya ekle
void inputAfter(struct Node* prevNode, int newData) {
    // 1. düğüm null ise ekleme yapılmaz
    if(prevNode == NULL ) {
        printf("Onceki dugum NULL olamaz.\n");
        return;
    }

    // yeni düğüm oluştur
    struct Node* n = newNode(newData);

    // yeni düğümün next'i, önceki düğümün next'ini göstersin
    n->next = prevNode->next;

    // Önceki düğümün next'i yeni düğümü göstersin
    prevNode->next = n;
}

void inputTail(struct Node** head, int newData){
    struct Node* n = newNode(newData);

    // Liste boşsa
    if (*head == NULL) {
        *head = n;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = n;
}

void deleteNode(struct Node** head, int key){
    if (*head == NULL) return;

    // head silme
    if ((*head)->data == key){
        struct Node* del = *head;
        *head = (*head)->next;
        free(del);
        return;
    }

    // ortadan-sondan silme
    struct Node* prev = *head;
    struct Node* curr = (*head)->next;

    while (curr != NULL && curr->data != key){
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return;

    prev->next = curr->next;
    free(curr);
}

void displayList(const struct Node* head){
    printf("\nLinked list: ");
    const struct Node* temp = head;
    while (temp){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n\n");
}

int menu(){
    int choice;
    printf("|~~~~~|~ Menu ~|~~~~~|\n");
    printf("1. Basa Ekle\n");
    printf("2. Sona Ekle\n");
     printf("3. Araya Ekle (Deger Sonrasina)\n");
    printf("4. Dugum Sil\n");
    printf("5. Listeyi Goster\n");
    printf("6. Cikis\n");
    printf("Secim yapin: ");
    
    // scanf ve hata kontrolü
    if (scanf("%d", &choice) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    return choice;
}

int main(){
    struct Node* head = NULL;

    for(;;){
        int m = menu();
        switch (m){
        case 1: {
            int x;
            printf("Eklenecek veri: ");
            scanf("%d", &x);
            inputHead(&head, x);
            break;
        }
        case 2: {
            int x;
            printf("Eklenecek veri: ");
            scanf("%d", &x);
            inputTail(&head, x);
            break;
        }
        case 3: { // Araya Ekle
            int m, key;
            printf("Hangi degerden sonra eklenecek: ");
            scanf("%d", &key);
            
            // Anahtar değere sahip düğümü bul
            struct Node* temp = head;
            while (temp != NULL && temp->data != key) {
                temp = temp->next;
            }

            if (temp != NULL) {
                printf("Eklenecek yeni veri: ");
                scanf("%d", &m);
                inputAfter(temp, m); // Yeni fonksiyonu çağırma
            } else {
                printf("%d degerine sahip dugum bulunamadi. Ekleme yapilamadi.\n", key);
            }
            break;
        case 4: {
            int k;
            printf("Silinecek veri: ");
            scanf("%d", &k);
            deleteNode(&head, k);
            break;
        }
        case 5:
            displayList(head);
            break;
        case 6:
            printf("Cikis yapildi...\n");
            return 0;
        default:
            printf("Gecersiz secim.\n");
        }
    }
}
}