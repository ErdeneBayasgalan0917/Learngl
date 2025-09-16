Write-Host "Adding changes..."
git add .

# Check if there are staged changes
$changes = git diff --cached --name-only
if (-not $changes) {
    Write-Host "No changes to commit."
    exit
}

# Get current date and time
$datetime = Get-Date -Format "yyyy-MM-dd HH:mm:ss"

# Prompt user for a custom message
$customMsg = Read-Host "Enter a commit message (optional)"

# Combine date/time and user message
if ($customMsg) {
    $commitMsg = "$datetime - $customMsg"
} else {
    $commitMsg = "$datetime - Auto commit"
}

Write-Host "Committing..."
$commitResult = git commit -m "$commitMsg"
if ($LASTEXITCODE -ne 0) {
    Write-Host "Commit failed."
    Write-Host $commitResult
    exit 1
}

Write-Host "Pushing to remote repo"
$pushResult = git push -u origin master
if ($LASTEXITCODE -ne 0) {
    Write-Host "Push failed."
    Write-Host $pushResult
    exit 1
}