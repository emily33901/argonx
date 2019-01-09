$mypath = Split-Path $MyInvocation.MyCommand.Path

Push-Location

Set-Location $mypath

$tools_dir = $pwd.Path

Set-Location "..\external\SteamKit\Resources\Protobufs"

$cur_dir = $pwd

foreach($d in Get-ChildItem -Directory) {
    $protos = New-Object System.Collections.ArrayList

    foreach($proto in Get-ChildItem -Path $d.FullName) {
        if($proto.Extension -like "*.proto") {
            [void] $protos.Add($proto)
        }
    }

    Write-Host $d
    if ($d.Name -eq "steam") {
        $quote = '"'

        $full_names = $protos | % {"$($quote)$($_.FullName)$($quote)"}

        # Write-Host "$($tools_dir)/../protogen/$($d.Name)/"

        New-Item -ItemType directory -Path "$($tools_dir)/../protogen/$($d.Name)/" -ErrorAction SilentlyContinue

        Write-Host "~~~~~~~~~"
        Write-Host $protos
        Write-Host "====="
        Write-Host $cur_dir
        Write-Host "====="
        Write-Host $d.Name
        Write-Host "====="
        Write-Host "====="

        # protoc -I="$($d.FullName)" -I="steam" --cpp_out="$($quote)$($tools_dir)/../protogen/$($quote)" $($full_names)

        foreach($f in $protos) {
            Push-Location
        
            Write-Host ">> $($f)"

            Set-Location $d

            protoc -I="." -I=".." -I="../steam" --cpp_out="$($quote)$($tools_dir)/../protogen/$($quote)" "$($f)"

            Pop-Location
        }
    }
}

Pop-Location