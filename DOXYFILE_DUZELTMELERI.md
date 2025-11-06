# Doxyfile Düzeltmeleri

## ✅ Yapılan Düzeltmeler

### 1. DoxyfileLibWin
- **INPUT dizinleri güncellendi:**
  - Eski: `src/calculator`, `src/calculatorapp`, `src/utility`
  - Yeni: `include`, `src`
  
- **PROJECT_NAME güncellendi:**
  - Eski: "Calculator Windows Library API Documentation"
  - Yeni: "Recipe Windows Library API Documentation"
  
- **PROJECT_BRIEF güncellendi:**
  - Eski: "Calculator Libraries"
  - Yeni: "Recipe and Nutrition Tracker Libraries"

### 2. DoxyfileTestWin
- **INPUT dizinleri güncellendi:**
  - Eski: `src/tests/calculator`, `src/tests/utility`
  - Yeni: `tests`
  
- **PROJECT_NAME güncellendi:**
  - Eski: "Calculator Windows Library API Unit Test Documentation"
  - Yeni: "Recipe Windows Library API Unit Test Documentation"
  
- **PROJECT_BRIEF güncellendi:**
  - Eski: "Calculator Unit Tests"
  - Yeni: "Recipe Unit Tests"

### 3. 7-build-doc-windows.bat
- **Report başlıkları güncellendi:**
  - "Calculator Library" → "Recipe Library"
  - "Calculator Library Test" → "Recipe Library Test"

## 🚀 Şimdi Yapmanız Gerekenler

1. **Dokümantasyon script'ini tekrar çalıştırın:**
   ```powershell
   .\7-build-doc-windows.bat
   ```

2. **Artık hata almamalısınız** çünkü:
   - Doğru dizinler belirtildi (`include`, `src`, `tests`)
   - Eski "calculator" referansları kaldırıldı
   - Proje isimleri güncellendi

## 📝 Notlar

- Doxyfile dosyaları artık mevcut proje yapısına uygun
- Tüm "calculator" referansları "recipe" olarak değiştirildi
- Script'ler doğru dizinleri arıyor

