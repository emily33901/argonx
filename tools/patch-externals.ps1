$spath = Split-Path $MyInvocation.MyCommand.Path
Push-Location $spath

foreach ($d in Get-ChildItem -Directory "..\external\") {
    $patchPath = "patches\" + $d.Name + ".patch"

    if (Test-Path ($patchPath)) {
        $patchPath = Get-Item $patchPath
        # Write-Host $patchPath.FullName

        Push-Location $d.FullName
        Write-Host "Applying patch for $($d.FullName) from $($patchPath.FullName)"
        cmd /c "git apply $($patchPath.FullName)"
        Pop-Location
    }

}

Pop-Location