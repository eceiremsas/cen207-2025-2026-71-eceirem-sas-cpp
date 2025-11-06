# index.html ve diğer eski dosyaları geri getirme scripti
# PowerShell scripti

Write-Host "=== Eski Dosyaları Geri Getirme Scripti ===" -ForegroundColor Green
Write-Host ""

# Proje dizinine git
$projectPath = "C:\Users\ACER\Desktop\yenii\cen207-2025-2026-71-eceirem-sas-cpp"
Set-Location $projectPath

Write-Host "1. Git commit geçmişinde index.html aranıyor..." -ForegroundColor Yellow
$htmlHistory = git log --all --full-history --oneline -- "*index.html"
if ($htmlHistory) {
    Write-Host "index.html bulundu!" -ForegroundColor Green
    Write-Host $htmlHistory
    Write-Host ""
    Write-Host "Dosyayı geri getirmek için şu komutu kullanın:" -ForegroundColor Cyan
    Write-Host "git checkout <commit-hash> -- index.html" -ForegroundColor White
} else {
    Write-Host "index.html Git geçmişinde bulunamadı." -ForegroundColor Red
    Write-Host ""
}

Write-Host "2. Tüm commit'lerde HTML dosyaları aranıyor..." -ForegroundColor Yellow
$allCommits = git log --oneline --all
foreach ($commit in $allCommits) {
    $hash = $commit.Split(' ')[0]
    $files = git ls-tree -r --name-only $hash | Select-String -Pattern "\.html$"
    if ($files) {
        Write-Host "Commit $hash içinde HTML dosyaları bulundu:" -ForegroundColor Green
        $files | ForEach-Object { Write-Host "  - $_" -ForegroundColor Cyan }
        Write-Host ""
    }
}

Write-Host "3. Silinen dosyalar listeleniyor..." -ForegroundColor Yellow
$deletedFiles = git log --all --full-history --diff-filter=D --summary | Select-String -Pattern "\.html"
if ($deletedFiles) {
    Write-Host "Silinen HTML dosyaları:" -ForegroundColor Yellow
    $deletedFiles
} else {
    Write-Host "Silinen HTML dosyası bulunamadı." -ForegroundColor Red
}

Write-Host ""
Write-Host "=== Manuel Geri Getirme Komutları ===" -ForegroundColor Green
Write-Host ""
Write-Host "Belirli bir commit'ten dosya geri getirmek için:" -ForegroundColor Cyan
Write-Host "  git checkout <commit-hash> -- <dosya-adi>" -ForegroundColor White
Write-Host ""
Write-Host "Örnek:" -ForegroundColor Cyan
Write-Host "  git checkout 2fb04e6 -- index.html" -ForegroundColor White
Write-Host ""
Write-Host "Tüm commit'leri görmek için:" -ForegroundColor Cyan
Write-Host "  git log --oneline --all" -ForegroundColor White
Write-Host ""
Write-Host "Bir dosyanın geçmişini görmek için:" -ForegroundColor Cyan
Write-Host "  git log --all --full-history -- <dosya-adi>" -ForegroundColor White

