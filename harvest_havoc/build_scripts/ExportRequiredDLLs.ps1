param (
    [Parameter(Mandatory=$true)]
    [string]$destDir
)

# Paths to the DLL files
$vulkanDllPath = Join-Path -Path $env:SystemRoot -ChildPath "System32\vulkan-1.dll"
$sdl2DllPath = Join-Path -Path $env:SDL2_DIR -ChildPath "Bin\SDL2.dll"
$runtimeDllPaths = @(
    "$env:SystemRoot\System32\msvcp140.dll",
    "$env:SystemRoot\System32\vcruntime140.dll",
    "$env:SystemRoot\System32\vcruntime140_1.dll"
)

# All DLL file paths
$dllPaths = @($vulkanDllPath, $sdl2DllPath) + $runtimeDllPaths

# Copy each DLL file to the destination directory
foreach ($dllPath in $dllPaths) {
    if (Test-Path -Path $dllPath) {
        $dllFile = Split-Path -Path $dllPath -Leaf
        $destPath = Join-Path -Path $destDir -ChildPath $dllFile
        Copy-Item -Path $dllPath -Destination $destPath -Force
        Write-Host "Copied $dllFile to $destDir"
    }
    else {
        Write-Host "WARNING: $dllPath not found"
    }
}
