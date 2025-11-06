# Linker Hatası Çözümü

## 🔴 Sorun
```
error LNK2038: 'RuntimeLibrary' için uyuşmazlık algılandı: 
MTd_StaticDebug üzerinde 'MDd_DynamicDebug' değeri 'test_recipes.obj' değeri ile eşleşmiyor
```

## ✅ Çözüm
CMakeLists.txt dosyasına C++ runtime library ayarları eklendi.

### Yapılan Değişiklikler:

1. **C++ Compiler Flags Eklendi:**
   ```cmake
   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
   ```

2. **Test Executable için Runtime Library Ayarı:**
   ```cmake
   if(MSVC)
       target_compile_options(recipe_tests PRIVATE
           $<$<CONFIG:Debug>:/MTd>
           $<$<CONFIG:Release>:/MT>
       )
   endif()
   ```

## 🚀 Şimdi Yapmanız Gerekenler

### 1. Build Klasörünü Temizleyin
```bash
# Eski build'i silin
rd /S /Q build_win
```

### 2. Yeniden Build Edin
```bash
8-build-test-windows.bat
```

Veya manuel:
```bash
mkdir build_win
cd build_win
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Debug
```

### 3. Testleri Çalıştırın
```bash
cd build_win
ctest -C Debug --output-on-failure
```

## 📝 Açıklama

**Sorun:** 
- C kodu `/MTd` (Multi-threaded Debug Static) kullanıyordu
- C++ test kodu `/MDd` (Multi-threaded Debug DLL) kullanıyordu
- Bu iki farklı runtime library birbirleriyle uyumlu değil

**Çözüm:**
- C++ kodunu da `/MTd` kullanacak şekilde ayarladık
- Artık hem C hem C++ kodu aynı static runtime library kullanıyor
- Bu sayede linker hatası çözüldü

## ⚠️ Not
Eğer hala hata alırsanız:
1. Build klasörünü tamamen silin
2. Yeniden configure edin
3. Build edin

GoogleTest'in de aynı runtime library kullanması gerekiyor. Eğer GoogleTest farklı bir runtime library ile derlenmişse, onu da yeniden derlemeniz gerekebilir.

