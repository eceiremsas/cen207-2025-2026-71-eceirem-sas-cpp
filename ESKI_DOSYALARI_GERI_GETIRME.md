# Eski Dosyaları Geri Getirme Rehberi

Bu rehber, Git kullanarak silinmiş veya değiştirilmiş dosyaları nasıl geri getirebileceğinizi açıklar.

## 1. Silinmiş Bir Dosyayı Geri Getirme

### Yöntem 1: Belirli Bir Commit'ten Dosya Geri Getirme

Eğer dosyanın hangi commit'te olduğunu biliyorsanız:

```powershell
# Önce dosyanın geçmişini bulun
git log --all --full-history -- "dosya_adi.html"

# Belirli bir commit'ten dosyayı geri getirin
git checkout <commit-hash> -- dosya_adi.html

# Örnek: index.html dosyasını geri getirmek için
git checkout 2fb04e6 -- index.html
```

### Yöntem 2: Dosyanın Son Versiyonunu Geri Getirme

```powershell
# Dosyanın son commit'teki halini geri getir
git checkout HEAD -- index.html

# Veya main branch'inden
git checkout main -- index.html
```

### Yöntem 3: Silinen Dosyaları Bulma ve Geri Getirme

```powershell
# Tüm commit geçmişinde silinen dosyaları bul
git log --all --full-history --diff-filter=D --summary

# Belirli bir dosyayı arayın
git log --all --full-history --diff-filter=D --summary | Select-String -Pattern "index.html"

# Dosyayı bulduktan sonra, o commit'ten geri getirin
git checkout <commit-hash>^ -- index.html
```

## 2. Tüm Silinen Dosyaları Geri Getirme

```powershell
# Son commit'teki tüm dosyaları geri getir
git checkout HEAD -- .

# Veya belirli bir commit'teki tüm dosyaları
git checkout <commit-hash> -- .
```

## 3. Dosya Geçmişini İnceleme

```powershell
# Bir dosyanın tüm geçmişini görüntüle
git log --all --full-history -- "index.html"

# Dosyanın değişikliklerini görüntüle
git log -p --all -- "index.html"

# Dosyanın belirli bir commit'teki içeriğini görüntüle
git show <commit-hash>:index.html
```

## 4. Mevcut Projeniz İçin Örnek Komutlar

Projenizdeki commit'ler:
- `6914c8d` - Revert "loaded"
- `30026ca` - deleted unnecessary files
- `2fb04e6` - loaded
- `659a7a0` - Initial commit

### index.html dosyasını geri getirmek için:

```powershell
# 1. Önce dosyanın var olup olmadığını kontrol edin
git log --all --full-history -- "*index.html"

# 2. Eğer bulunursa, o commit'ten geri getirin
# Örnek: "loaded" commit'inden geri getirmek için
git checkout 2fb04e6 -- index.html

# 3. Değişiklikleri commit edin
git add index.html
git commit -m "index.html dosyasını geri getirdim"
```

## 5. Windows Dosya Geçmişi Kullanma (Git Yoksa)

Eğer Git yoksa ve dosya yakın zamanda silindiyse:

1. **Geri Dönüşüm Kutusu**: Windows Geri Dönüşüm Kutusu'nu kontrol edin
2. **Dosya Geçmişi**: 
   - Dosya Gezgini'nde proje klasörüne sağ tıklayın
   - "Önceki sürümleri geri yükle" seçeneğini seçin
   - Windows'un otomatik yedeklerinden geri yükleyin

## 6. Pratik Örnek: index.html Dosyasını Bulma ve Geri Getirme

```powershell
# Proje dizinine gidin
cd "C:\Users\ACER\Desktop\yenii\cen207-2025-2026-71-eceirem-sas-cpp"

# Tüm commit'lerde index.html'i arayın
git log --all --full-history --oneline -- "*index.html"

# Eğer sonuç varsa, o commit hash'ini kullanarak geri getirin
# Örnek: commit hash 2fb04e6 ise
git checkout 2fb04e6 -- index.html

# Dosyanın geri geldiğini kontrol edin
ls index.html

# Değişiklikleri stage'e ekleyin
git add index.html

# Commit edin
git commit -m "index.html dosyasını geri getirdim"
```

## Önemli Notlar

- `git checkout` komutu dosyayı working directory'ye geri getirir, otomatik olarak commit etmez
- Değişiklikleri kaydetmek için `git add` ve `git commit` yapmanız gerekir
- Eğer dosya hiç commit edilmediyse, Git geçmişinde bulunamaz
- `.gitignore` dosyasında olan dosyalar Git tarafından takip edilmez

## Yardımcı Komutlar

```powershell
# Tüm branch'leri görüntüle
git branch -a

# Tüm commit'leri görüntüle
git log --oneline --all --graph

# Silinen tüm dosyaları listele
git log --all --full-history --diff-filter=D --summary

# Belirli bir commit'teki tüm dosyaları listele
git ls-tree -r --name-only <commit-hash>
```

