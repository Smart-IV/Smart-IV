# Antigravity Sync Script
param (
    [string]$Branch = "$(git branch --show-current)"
)

Write-Host "🔄 Starting Antigravity Sync for branch: $Branch..." -ForegroundColor Cyan

# 1. Pull Latest Changes
Write-Host "📥 Fetching updates..." -ForegroundColor Yellow
git pull origin main
git pull origin $Branch

# 2. Stage and Commit
Write-Host "📝 Staging changes..." -ForegroundColor Yellow
git add .
$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
git commit -m "antigravity: sync state @ $timestamp"

# 3. Push to Branch
Write-Host "📤 Pushing to $Branch..." -ForegroundColor Yellow
git push origin $Branch

Write-Host "✅ Sync Complete!" -ForegroundColor Green
