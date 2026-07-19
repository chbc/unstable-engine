$BuildDir = "build"
$BinDir = "bin"
$VcpkgToolchain = "E:/Projetos/UnstableEngine/referencias/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake"

Write-Host "--- Limpando ambiente ---" -ForegroundColor Cyan
if (Test-Path $BuildDir) { Remove-Item -Recurse -Force $BuildDir }
if (Test-Path $BinDir) { Remove-Item -Recurse -Force $BinDir }

New-Item -ItemType Directory -Path $BuildDir

Write-Host "--- Iniciando configuração com CMake ---" -ForegroundColor Cyan

cmake -S . -B $BuildDir `
      -DCMAKE_TOOLCHAIN_FILE="$VcpkgToolchain" `
      -DCMAKE_BUILD_TYPE=Debug

Write-Host "--- Iniciando compilação ---" -ForegroundColor Cyan

cmake --build $BuildDir --config Debug --verbose

Write-Host "--- Processo concluído com sucesso! ---" -ForegroundColor Green