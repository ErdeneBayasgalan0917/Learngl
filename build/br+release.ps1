# Build and run Release version (no cmake setup)
cmake --build . --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
$exe = Get-ChildItem -Path . -Filter "learngl_release.exe" -Recurse | Select-Object -First 1
if ($exe) { & $exe.FullName } else { Write-Error "Release executable not found." }