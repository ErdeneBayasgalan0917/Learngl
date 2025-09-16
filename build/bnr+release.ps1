# Build and run Release version
cmake .. -DCMAKE_BUILD_TYPE=Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build . --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$exe = Get-ChildItem -Path . -Filter "learngl_release.exe" -Recurse | Select-Object -First 1
if ($exe) { & $exe.FullName } else { Write-Error "Release executable not found." }