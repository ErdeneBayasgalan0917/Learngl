# Build and run Debug version
cmake .. -DCMAKE_BUILD_TYPE=Debug
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build . --config Debug
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$exe = Get-ChildItem -Path . -Filter "learngl_debug.exe" -Recurse | Select-Object -First 1
if ($exe) { & $exe.FullName } else { Write-Error "Debug executable not found." }