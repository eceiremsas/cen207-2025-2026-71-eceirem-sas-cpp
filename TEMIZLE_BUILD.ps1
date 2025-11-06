# PowerShell script to clean build directories

Write-Host "Cleaning build directories..." -ForegroundColor Yellow

if (Test-Path "build_win") {
    Remove-Item -Path "build_win" -Recurse -Force
    Write-Host "build_win deleted" -ForegroundColor Green
} else {
    Write-Host "build_win does not exist" -ForegroundColor Gray
}

if (Test-Path "build") {
    Remove-Item -Path "build" -Recurse -Force
    Write-Host "build deleted" -ForegroundColor Green
} else {
    Write-Host "build does not exist" -ForegroundColor Gray
}

Write-Host "Cleanup completed!" -ForegroundColor Green

