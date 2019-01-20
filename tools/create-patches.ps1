$spath = Split-Path $MyInvocation.MyCommand.Path
Push-Location $spath

Write-Host "$spath"

foreach ($d in Get-ChildItem -Directory "..\external\") {
    $patchPath = "patches\" + $d.Name + ".patch"

    Write-Host "Creating patch for $($d.FullName)"

    Push-Location $d.FullName

    cmd /c "git diff > $($spath + "\" + $patchPath)"

    Pop-Location
}

Pop-Location