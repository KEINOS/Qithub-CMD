<?php
namespace Qithub\Core;

include('Functions.php');
include('Classes.php');

$msg = 'Hello World!';

/* Function */
echo return_message($msg) . PHP_EOL;

/* Class */
echo MyClass::returnMessage($msg) . PHP_EOL;

$test = new MyClass();
$test->echoMessage($msg);
echo PHP_EOL;


/* Box Tips (Git info replacement) */
/* 以下は Box で Build すると自動的に置き換わります */
echo '@git_version@' . PHP_EOL;
echo '@git_commit_long@' . PHP_EOL;
echo '@git_commit_short@' . PHP_EOL;
echo '@git_tag@' . PHP_EOL;
echo '@date_build@' . PHP_EOL;

if (is_phar()) {
    echo 'Running via phar.' . PHP_EOL;
} else {
    echo 'Running PHP directly.' . PHP_EOL;
}
