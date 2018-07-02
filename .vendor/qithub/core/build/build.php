<?php
// define
const NAME_FILE_BOX  = 'box.phar';
const NAME_FILE_CONF = 'box.json';
const NAME_FILE_MAIN = 'index.php';
const NAME_DIR_CURNT = '.';
const NAME_DIR_PARNT = '..';
const NAME_DIR_SRC   = 'src';
const DIR_SEP        = DIRECTORY_SEPARATOR;
const PATH_DIR_CURNT = NAME_DIR_CURNT . DIR_SEP;
const PATH_DIR_PARNT = NAME_DIR_PARNT . DIR_SEP;
const PATH_DIR_SRC   = PATH_DIR_PARNT . NAME_DIR_SRC . DIR_SEP;
const PATH_FILE_BOX  = PATH_DIR_CURNT . NAME_FILE_BOX;
const PATH_FILE_CONF = PATH_DIR_CURNT . NAME_FILE_CONF;
const PATH_FILE_MAIN = PATH_DIR_SRC   . NAME_FILE_MAIN;

// check dependencies
$with = "with";
switch(true){
    case (! file_exists(PATH_FILE_BOX)):
        echo "You need '{$with(PATH_FILE_BOX)}' to build the app." . PHP_EOL;
        echo 'Run `install.php` to get the latest `box.phar`.' . PHP_EOL;
        die;
    case (! is_dir(PATH_DIR_SRC)):
        echo "You need '{$with(PATH_DIR_SRC)}' to build the app." . PHP_EOL;
        die;
    case (! file_exists(PATH_FILE_MAIN)):
        echo "You need '{$with(PATH_FILE_MAIN)}' to build the app." . PHP_EOL;
        die;
    default:
        break;    
}

// create command
$cmd = PATH_FILE_BOX . " build -c " . PATH_FILE_CONF;

// run command
$result = `$cmd`;

// echo result
echo $result . "Done." . PHP_EOL;

function with($string)
{
    return (string) $string;
}
