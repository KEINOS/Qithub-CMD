<?php
namespace qithub\cmd\tests;

/* [FUNCTIONS] ============================================================== */


/* ---------------------------------------------------------------------- [E] */

function echoEOL($msg)
{
    echo $msg, PHP_EOL;
    flushNow();
}

/* ---------------------------------------------------------------------- [F] */

function flushNow()
{
    @ob_flush();
    @flush();
}

/* ---------------------------------------------------------------------- [G] */

function getPortRandom()
{
    return getPortRandomForMac();
}

function getPortRandomForMac($port_min = 50000, $port_max = 65535)
{
    $cmd   = 'lsof -i -P | grep -i "listen" 2>&1';
    $rows  = array_filter(explode(PHP_EOL, `$cmd`));
    $ports = array_map(
        function ($row) {
            $row  = str_replace(':', ' ', $row);
            $cols = explode(' ', $row);
            $cols = array_values(array_filter($cols));
            return (int) $cols[9];
        },
        $rows
    );

    while (true) {
        $port = rand($port_min, $port_max);
        if (false === array_search($port, $ports)) {
            break;
        }
    }
    return $port;
}

function getPortRandomForWin()
{
    $sock = socket_create_listen(0);
    socket_getsockname($sock, $addr, $port);
    socket_close($sock);

    return (int) $port;
}

/* ---------------------------------------------------------------------- [I] */

function isCLI()
{
    return PHP_SAPI === 'cli' || defined('STDIN');
}
