param (
    [string]$projectDir,
    [string]$outputDir,
    [string]$validatorPath
)

# Get all .vert and .frag files recursively from the shaders directory
$shaderFiles = Get-ChildItem -Path $projectDir -Recurse -Include *.vert,*.frag

foreach ($shaderFile in $shaderFiles) {
    # Determine the output directory for this shader
    $relativePath = $shaderFile.FullName.Substring($projectDir.Length)
    $outputFileDir = Join-Path -Path $outputDir -ChildPath $relativePath
    $outputFileDir = $outputFileDir + ".spv"

    # Ensure the output directory exists
    $outputFileDirectory = [System.IO.Path]::GetDirectoryName($outputFileDir)
    if (-not (Test-Path -Path $outputFileDirectory)) {
        New-Item -ItemType Directory -Path $outputFileDirectory | Out-Null
    }

    # Compile the shader
    & $validatorPath -V $shaderFile.FullName -o $outputFileDir
}
