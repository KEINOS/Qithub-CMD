<?php

include_once('vendor/autoload.php');
//include_once('src/Functions.php');

use PHPUnit\Framework\TestCase;

trait QithubSetup
{
    public function setUp()
    {
       // Warning も確実にエラーとして扱うようにする
        set_error_handler(function ($errno, $errstr, $errfile, $errline) {
            $msg  = 'Error #' . $errno . ': ';
            $msg .= $errstr . " on line " . $errline . " in file " . $errfile;
            throw new RuntimeException($msg);
        });
    }    
}

class StringInsertionTest extends TestCase
{
    use QithubSetup;

    public function testIsSame()
    {
        $message = 'Hello, World!';
        $result  = Qithub\fn\return_message($message);

        $this->assertSame($message, $result);
    }

    public function testIsString()
    {
        $message = 'Hello, World!';
        $result  = Qithub\fn\return_message($message);

        $this->assertTrue(is_string($result));
    }
}
