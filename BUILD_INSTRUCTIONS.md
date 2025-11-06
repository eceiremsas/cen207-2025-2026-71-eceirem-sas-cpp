# Build ve Test Talimatları

## 1. Projeyi Build Etme

### Windows için:
```powershell
# Build klasörü oluştur
mkdir build
cd build

# CMake yapılandırması
cmake ..

# Projeyi derle
cmake --build . --config Release
```

### Linux/WSL için:
```bash
mkdir build
cd build
cmake ..
make
```

## 2. Testleri Çalıştırma

```bash
cd build
ctest --verbose
```

veya doğrudan:
```bash
cd build
./recipe_tests
```

## 3. Uygulamayı Çalıştırma

```bash
cd build
./recipeapp
```

## 4. Doxygen Dokümantasyonu Oluşturma

```bash
cd build
cmake --build . --target doxygen_docs
```

Dokümantasyon `build/docs` klasöründe oluşacaktır.

## 5. Potansiyel Sorunlar ve Çözümleri

### Sorun: GoogleTest bulunamıyor
**Çözüm**: CMake otomatik olarak indirecektir. İnternet bağlantınızı kontrol edin.

### Sorun: C++ derleyici bulunamıyor
**Çözüm**: 
- Windows: Visual Studio Community Edition kurulu olmalı
- Linux: `sudo apt-get install build-essential`

### Sorun: Doxygen bulunamıyor
**Çözüm**: Doxygen opsiyoneldir, dokümantasyon olmadan da build edilebilir.

## 6. Coverage Raporları (Opsiyonel)

Coverage raporları için OpenCppCoverage (Windows) veya gcov (Linux) kullanılabilir.

