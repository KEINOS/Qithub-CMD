<?php
namespace Qithub\fn;

function return_message($message)
{
    return (string) $message;
}

function is_phar()
{
    return strlen(\Phar::running()) > 0 ? true : false;
}
