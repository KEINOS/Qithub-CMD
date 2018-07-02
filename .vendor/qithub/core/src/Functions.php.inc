<?php
namespace Qithub\fn;

function return_message($message)
{
    return (string) $message;
}

function isPhar()
{
    return strlen(\Phar::running()) > 0 ? true : false;
}

function isJson($string)
{
    if (! is_string($string)) {
        return false;
    }

    $json = json_decode($string);

    return ( (json_last_error() === JSON_ERROR_NONE) && (is_array($json)));
}
