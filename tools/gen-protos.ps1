$mypath = Split-Path $MyInvocation.MyCommand.Path

Set-Location $mypath

$tools_dir = $pwd

Set-Location "..\external\SteamKit\Resources\Protobufs"

$cur_dir = $pwd

foreach($d in Get-ChildItem -Recurse -Directory) {
    $protos = New-Object System.Collections.ArrayList

    foreach($proto in Get-ChildItem -Path $d.FullName) {
        if($proto.Extension -like "*.proto") {
            [void] $protos.Add($proto)
        }
    }

    $quote = '"'

    $full_names = $protos | % {"$($quote)$($_.FullName)$($quote)"}

    Write-Host "$($tools_dir)/../protogen/$($d.Name)/"

    New-Item -ItemType directory -Path "$($tools_dir)/../protogen/$($d.Name)/" -ErrorAction SilentlyContinue

    foreach($f in $full_names) {
        protoc -I="$($cur_dir)" -I="$($d.Name)" -I="steam" --cpp_out="$($quote)$($tools_dir)/../protogen/$($quote)" "$($f)"
    }
}