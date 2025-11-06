# Test Case'ler ve Test Sonuçları - Kullanım Kılavuzu

## 📁 TEST DOSYASI KONUMU

### Ana Test Dosyası
**Dosya Yolu:** `tests/test_recipes.cpp`

Bu dosyada **43 test case** bulunuyor ve tüm veri yapıları test ediliyor.

## 📊 TEST LİSTESİ

### 1. Recipe Tests (7 test)
- `RecipeTest.CreateRecipe` - Recipe oluşturma
- `RecipeTest.AddIngredient` - Ingredient ekleme
- `RecipeTest.SetInstructions` - Instructions ayarlama
- `RecipeTest.CompareByID` - ID'ye göre karşılaştırma
- `RecipeTest.CompareByCalories` - Kaloriye göre karşılaştırma
- `RecipeTest.CopyRecipe` - Recipe kopyalama
- `RecipeTest.BinaryFileOperations` - Binary dosya işlemleri

### 2. Linked List Tests (5 test)
- `LinkedListTest.CreateList` - Liste oluşturma
- `LinkedListTest.InsertHead` - Başa ekleme
- `LinkedListTest.InsertTail` - Sona ekleme
- `LinkedListTest.RemoveFromList` - Listeden silme
- `LinkedListTest.BinaryFileOperations` - Binary dosya işlemleri

### 3. XOR Linked List Tests (4 test)
- `XORLinkedListTest.CreateList` - Liste oluşturma
- `XORLinkedListTest.InsertOperations` - Ekleme işlemleri
- `XORLinkedListTest.BidirectionalTraversal` - Çift yönlü traversal
- `XORLinkedListTest.BinaryFileOperations` - Binary dosya işlemleri

### 4. Sparse Matrix Tests (4 test)
- `SparseMatrixTest.CreateMatrix` - Matrix oluşturma
- `SparseMatrixTest.AddEntry` - Entry ekleme
- `SparseMatrixTest.FindRecipesByIngredient` - Ingredient'e göre arama
- `SparseMatrixTest.BinaryFileOperations` - Binary dosya işlemleri

### 5. Stack Tests (4 test)
- `StackTest.CreateStack` - Stack oluşturma
- `StackTest.PushPop` - Push/Pop işlemleri
- `StackTest.Peek` - Peek işlemi
- `StackTest.BinaryFileOperations` - Binary dosya işlemleri

### 6. Queue Tests (4 test)
- `QueueTest.CreateQueue` - Queue oluşturma
- `QueueTest.EnqueueDequeue` - Enqueue/Dequeue işlemleri
- `QueueTest.Peek` - Peek işlemi
- `QueueTest.BinaryFileOperations` - Binary dosya işlemleri

### 7. Heap Tests (4 test)
- `HeapTest.CreateHeap` - Heap oluşturma
- `HeapTest.InsertExtractMin` - Insert/Extract Min işlemleri
- `HeapTest.HeapSort` - Heap sort algoritması
- `HeapTest.BinaryFileOperations` - Binary dosya işlemleri

### 8. Graph Tests (5 test)
- `GraphTest.CreateGraph` - Graph oluşturma
- `GraphTest.AddVertexEdge` - Vertex/Edge ekleme
- `GraphTest.BFSTraversal` - BFS traversal
- `GraphTest.DFSTraversal` - DFS traversal
- `GraphTest.CycleDetection` - Cycle detection
- `GraphTest.BinaryFileOperations` - Binary dosya işlemleri

### 9. Hash Table Tests (5 test)
- `HashTableTest.CreateHashTable` - Hash table oluşturma
- `HashTableTest.InsertSearch` - Insert/Search işlemleri
- `HashTableTest.Delete` - Delete işlemi
- `HashTableTest.CollisionHandling` - Collision handling
- `HashTableTest.BinaryFileOperations` - Binary dosya işlemleri

**Toplam: 43 test case**

## 🔍 TEST SONUÇLARINA NASIL BAKABİLİRSİNİZ?

### Yöntem 1: Test Dosyasını Doğrudan Okuma
```powershell
# Test dosyasını açın
notepad tests\test_recipes.cpp
# veya
code tests\test_recipes.cpp
```

### Yöntem 2: Test Sonuç Log Dosyası
**Dosya Yolu:** `build_win/Testing/Temporary/LastTest.log`

Bu dosyada tüm test sonuçları detaylı olarak kayıtlı:
- Hangi testler çalıştı
- Hangi testler geçti/başarısız oldu
- Her testin çalışma süresi

### Yöntem 3: HTML Test Sonuçları
**Dosya Yolu:** `docs/testresultswin/index.html`

Bu HTML dosyasını tarayıcıda açarak test sonuçlarını görsel olarak görebilirsiniz.

### Yöntem 4: Test Executable'ı Doğrudan Çalıştırma
```powershell
# Test executable'ını çalıştırın
.\build_win\build\Debug\recipe_tests.exe

# Veya Release versiyonu
.\build_win\build\Release\recipe_tests.exe
```

### Yöntem 5: CTest ile Test Sonuçlarını Görüntüleme
```powershell
cd build_win
ctest -C Debug --output-on-failure --verbose
```

## 📝 TEST DOSYASINI GÖRÜNTÜLEME

### Visual Studio Code ile:
```powershell
code tests\test_recipes.cpp
```

### Notepad ile:
```powershell
notepad tests\test_recipes.cpp
```

### Dosya İçeriğini Terminal'de Görüntüleme:
```powershell
Get-Content tests\test_recipes.cpp | more
```

## 🎯 TEST SONUÇLARI ÖZETİ

Son test çalıştırmasından:
- **Toplam Test:** 43
- **Başarılı:** 43
- **Başarısız:** 0
- **Başarı Oranı:** %100

## 📂 İLGİLİ DOSYALAR

1. **Test Kaynak Kodu:**
   - `tests/test_recipes.cpp` - Tüm test case'ler burada

2. **Test Sonuçları:**
   - `build_win/Testing/Temporary/LastTest.log` - Detaylı test log'u
   - `docs/testresultswin/index.html` - HTML test sonuçları

3. **Test Executable:**
   - `build_win/build/Debug/recipe_tests.exe` - Debug versiyonu
   - `build_win/build/Release/recipe_tests.exe` - Release versiyonu

## 🚀 TESTLERİ YENİDEN ÇALIŞTIRMA

### Tüm Testleri Çalıştırma:
```powershell
.\8-build-test-windows.bat
```

### Sadece Testleri Çalıştırma (build sonrası):
```powershell
cd build_win
ctest -C Debug --output-on-failure
```

### Belirli Bir Testi Çalıştırma:
```powershell
.\build_win\build\Debug\recipe_tests.exe --gtest_filter=RecipeTest.CreateRecipe
```

### Belirli Bir Test Grubunu Çalıştırma:
```powershell
.\build_win\build\Debug\recipe_tests.exe --gtest_filter=RecipeTest.*
.\build_win\build\Debug\recipe_tests.exe --gtest_filter=LinkedListTest.*
```

## 📊 TEST İSTATİSTİKLERİ

- **Toplam Test Case:** 43
- **Test Grupları:** 9 (Recipe, LinkedList, XORLinkedList, SparseMatrix, Stack, Queue, Heap, Graph, HashTable)
- **Binary File Testleri:** Her veri yapısı için 1 test (toplam 9)
- **Temel İşlem Testleri:** 34 test
- **Test Süresi:** ~1-2 saniye (tüm testler)

## ✅ SONUÇ

Tüm test case'ler `tests/test_recipes.cpp` dosyasında bulunuyor ve başarıyla çalışıyor!

