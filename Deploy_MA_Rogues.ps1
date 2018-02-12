## DEPLOY MCAFEE AGENT TO ROGUES USING PSEXEC ##
## USE WHEN EPO SERVER FAILS TO DEPLOY AGENT  ##

# Put all rogue system into rogues.txt
$src = Get-Content "res/systems.txt"
#log files
$date = get-date -Format ddMMMyyyy_hhmm
New-Item -type file "out/error_$date.log" -Force | Out-Null
$errs = "out/error_$date.log"
#framepackage
$payload = "C:\scripts\res\framepkg.exe"

#reset error buffers
$error[0] = $null
$err = $null

#clear screen
CLS
# loop through each system in the $src var
foreach ($sys in $src){
    #ping system to ensure alive
    $con = Test-Connection -ComputerName $sys -Count 1 -Quiet
    # if alive continue, else go to next system
    if ($con -eq $true){#online
        #psexec to remotely install mcafee agent
        Write-Host "$sys Online" -ForegroundColor Green
        copy -Force $payload "\\$sys\C$\Windows\Temp"
        psexec \\$sys -d -s "C:\Windows\Temp\framepkg.exe"
        if ($error[0] -match "started"){}
        elseif ($error[0] -ne $null){
            $err = $error[0]
            Write-Host "ERRORS: $err" -ForegroundColor Red
            Add-Content $errs "##------START ERROR TRACE ON $sys------##"
            Add-Content $errs "ERRORS: $err"
            Add-Content $errs "/----------------------------------------------/"
         }
    }else{#offline
        Write-host "$sys Unavailable" -ForegroundColor Red
        Add-Content $errs "OFFLINE: $sys"
    }
}
if ((Get-Item $errs).Length -eq 0){
    del $errs -Force -ErrorAction SilentlyContinue
}
