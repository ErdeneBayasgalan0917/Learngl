# Prompt the user for the filename and store it in a variable
$fileName = Read-Host "Enter the file name you want to find"

# Search for the file using the user's input
Write-Host "Searching for '$fileName' on drive C:..." -ForegroundColor Yellow
Get-ChildItem -Path C:\ -Filter $fileName -Recurse -ErrorAction SilentlyContinue
Write-Host "Search complete." -ForegroundColor Green