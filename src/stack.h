
#ifndef STACK_H  // Include guard başlangıcı
#define STACK_H  // STACK_H makrosunu tanımla

#include "recipe.h"  // Recipe veri yapısı için

#define UNDO_STACK_SIZE 50


typedef enum {
    OP_ADD,     // Tarif ekleme işlemi
    OP_EDIT,    // Tarif düzenleme işlemi
    OP_DELETE   // Tarif silme işlemi
} OperationType;

typedef struct {
    int type;       // OP_ADD, OP_DELETE, OP_EDIT gibi
    Recipe* recipe;
} StackOperation;



typedef struct {
    StackOperation operations[UNDO_STACK_SIZE];  // İşlemleri tutan dizi (maksimum 10 işlem)
    int top;                                       // Stack'in en üst elemanının index'i (-1 ise stack boş)
} Stack;

Stack* stack_create(void);


int stack_push(Stack* stack, OperationType type, Recipe* recipe);

StackOperation* stack_pop(Stack* stack);

StackOperation* stack_peek(Stack* stack);

int stack_is_empty(Stack* stack);

int stack_is_full(Stack* stack);

int stack_size(Stack* stack);

void stack_destroy(Stack* stack);

#endif // STACK_H - Include guard sonu
