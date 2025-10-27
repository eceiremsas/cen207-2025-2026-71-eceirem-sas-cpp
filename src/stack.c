/**
 * @file stack.c
 * @brief Stack implementasyonu - Geri alma (undo) için LIFO yapısı
 */

#include "stack.h"  // Stack header

// Boş stack oluştur
Stack* stack_create(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));  // Bellek ayır
    if (stack == NULL) {
        printf("HATA: Stack olusturulamadi!\n");
        return NULL;
    }
    stack->top = -1;  // Stack boş - top = -1 (index -1 demek boş demek)
    return stack;
}

// Stack'e işlem ekle (push)
int stack_push(Stack* stack, OperationType type, Recipe* recipe) {
    if (stack == NULL) {  // Stack kontrolü
        return 0;
    }
    
    if (stack_is_full(stack)) {  // Stack dolu mu?
        printf("UYARI: Undo stack dolu - en eski islem siliniyor.\n");
        // Circular davranış - en eski işlemi sil
        for (int i = 0; i < UNDO_STACK_SIZE - 1; i++) {
            stack->operations[i] = stack->operations[i + 1];  // Kaydır
        }
        stack->top = UNDO_STACK_SIZE - 2;  // Top'u ayarla
    }
    
    stack->top++;  // Top'u bir artır (yeni eleman için yer aç)
    stack->operations[stack->top].type = type;  // İşlem tipini kaydet
    stack->operations[stack->top].recipe = recipe_copy(recipe);  // Tarif kopyasını sakla
    
    return 1;
}

// Stack'ten işlem çıkar (pop)
StackOperation* stack_pop(Stack* stack) {
    if (stack == NULL || stack_is_empty(stack)) {  // Boş kontrolü
        return NULL;
    }
    
    // En üstteki işlemi döndür ve top'u azalt
    StackOperation* op = &stack->operations[stack->top];
    stack->top--;  // Top'u azalt (bir eleman çıktı)
    return op;
}

// Stack'in tepesine bak (peek)
StackOperation* stack_peek(Stack* stack) {
    if (stack == NULL || stack_is_empty(stack)) {
        return NULL;
    }
    return &stack->operations[stack->top];  // En üstteki işlemi döndür (ama çıkarma)
}

// Stack boş mu?
int stack_is_empty(Stack* stack) {
    return (stack == NULL || stack->top == -1);  // Top -1 ise boş
}

// Stack dolu mu?
int stack_is_full(Stack* stack) {
    return (stack != NULL && stack->top == UNDO_STACK_SIZE - 1);  // Top maksimuma ulaştı mı?
}

// Stack boyutu
int stack_size(Stack* stack) {
    return (stack != NULL) ? (stack->top + 1) : 0;  // Top+1 = eleman sayısı
}

// Stack'i temizle
void stack_destroy(Stack* stack) {
    if (stack == NULL) {
        return;
    }
    
    // Tüm kopyalanmış tarifleri sil
    for (int i = 0; i <= stack->top; i++) {
        recipe_destroy(stack->operations[i].recipe);  // Her tarifin kopyasını sil
    }
    
    free(stack);  // Stack'i sil
}
