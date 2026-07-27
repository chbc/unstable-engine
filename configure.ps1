$BuildDir = "build"
$BinDir = "bin"
$VcpkgToolchain = "E:/Projetos/UnstableEngine/referencias/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake"

if (Test-Path $BuildDir) { Remove-Item -Recurse -Force $BuildDir }
if (Test-Path $BinDir) { Remove-Item -Recurse -Force $BinDir }

New-Item -ItemType Directory -Path $BuildDir

cmake -S . -B $BuildDir `
      -DCMAKE_TOOLCHAIN_FILE="$VcpkgToolchain" `
