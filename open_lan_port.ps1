# open_lan_port.ps1
# 开放本机 45680 入站 TCP 端口，供 PC 端作为联机主机时被安卓/其他 PC 客户端访问。
# 需要管理员权限：未提权时自动以管理员身份重启。
# 幂等：若规则已存在则直接报告状态，不重复创建。

$RuleName = 'PokeEmerald LAN 45680'
$Port = '45680'
$Exe = Join-Path $PSScriptRoot 'lanrun\pokeemerald.exe'

if (-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole(
        [Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Start-Process powershell -Verb RunAs -ArgumentList (
        '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File', ('"{0}"' -f $PSCommandPath)
    )
    Write-Host '已请求管理员权限，请在 UAC 弹窗中允许后查看结果。'
    exit
}

$existing = Get-NetFirewallRule -DisplayName $RuleName -ErrorAction SilentlyContinue
if ($existing) {
    Write-Host ("规则已存在: '{0}'  Enabled={1}  Action={2}  Direction={3}" -f `
        $existing.DisplayName, $existing.Enabled, $existing.Action, $existing.Direction)
} else {
    $params = [ordered]@{
        DisplayName = $RuleName
        Direction   = 'Inbound'
        Action      = 'Allow'
        Protocol    = 'TCP'
        LocalPort   = $Port
        Profile     = @('Domain', 'Private', 'Public')
    }
    if (Test-Path -LiteralPath $Exe) {
        $params.Program = $Exe   # 精确到 lanrun\pokeemerald.exe，减少不必要放行
    }
    New-NetFirewallRule @params | Out-Null
    $made = Get-NetFirewallRule -DisplayName $RuleName
    Write-Host ("已创建入站放行规则: '{0}'  TCP/{1}  Enabled={2}  Action={3}" -f `
        $made.DisplayName, $Port, $made.Enabled, $made.Action)
    if (-not $params.Contains('Program')) {
        Write-Host '  提示：未找到 lanrun\pokeemerald.exe，已按端口 45680 放行（范围更广）。'
    }
}