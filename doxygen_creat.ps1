$readmePath = "readme.md"
$backupPath = "readme.md.bak"

# -----------------------
# 工具检查函数
# -----------------------

function Check-Doxygen {
    try {
        $version = & doxygen --version 2>$null
        if (-not $version) { throw }
        Write-Host "✔ Doxygen found: version $version"
        return $true
    } catch {
        Write-Warning "❌ Doxygen 未找到，请访问 https://www.doxygen.nl/download.html 下载并安装。"
        return $false
    }
}

function Check-Graphviz {
    try {
        $dotVersion = & dot -V 2>&1
        if (-not $dotVersion) { throw }
        Write-Host "✔ Graphviz (dot) found: $dotVersion"
        return $true
    } catch {
        Write-Warning "❌ Graphviz 未找到，请访问 https://graphviz.org/download/ 下载并安装。"
        return $false
    }
}

# -----------------------
# 主流程开始
# -----------------------

# 检查工具
$hasDoxygen = Check-Doxygen
$hasGraphviz = Check-Graphviz

if (-not ($hasDoxygen -and $hasGraphviz)) {
    Write-Error "🚫 请先安装缺失的工具后再运行本脚本。"
    exit 1
}

# 检查 README 是否存在
if (-Not (Test-Path $readmePath)) {
    Write-Error "❌ $readmePath not found."
    exit 1
}

# 1. 备份原文件
Copy-Item -Path $readmePath -Destination $backupPath -Force
Write-Host "📁 readme.md backup created."

# 2. 替换所有代码块为 @verbatim 块
try {
    $content = Get-Content $readmePath -Raw

    # 使用正则匹配所有 ```lang\n...\n``` 代码块（支持所有语言）
    $pattern = '(?ms)```[^\n]*\n(.*?)```'
    $converted = [regex]::Replace($content, $pattern, {
        param($m)
        "@verbatim`n" + $m.Groups[1].Value.TrimEnd() + "`n@endverbatim"
    })

    Set-Content -Path $readmePath -Value $converted -Encoding UTF8
    Write-Host "🔧 Code blocks converted to @verbatim."

    # 3. 执行 doxygen.exe
    & doxygen.exe .\Doxyfile
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ Doxygen executed successfully."
    } else {
        Write-Warning "⚠️ Doxygen exited with code $LASTEXITCODE"
    }
}
finally {
    # 4. 还原 readme.md
    Move-Item -Path $backupPath -Destination $readmePath -Force
    Write-Host "🔄 readme.md restored to original."
}
