<?php
namespace qithub\cmd\tests;


echo 'Now fetching unused port ... PORT: ';
$port = getPortRandom();
echoEOL($port);

$cmd  = "open -n -a 'Google Chrome' --args -incognito 'http://localhost:{$port}'";
$cmd .= " && php -S localhost:{$port} {$name_file_base}";
echo 'RUN: ', $cmd, PHP_EOL, PHP_EOL;
echoEOL(`$cmd`);
