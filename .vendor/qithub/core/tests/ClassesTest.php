<?php

include_once('vendor/autoload.php');
include_once('src/Functions.php');
include_once('src/Classes.php');

use PHPUnit\Framework\TestCase;

class ClassesTest extends TestCase
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

    /*
     * テストを行うメソッド名は「test*」（*はクラス名）
     */
    public function testMyClass()
    {
        $message = 'Hello, World!';

        $result = \Qithub\Core\MyClass::returnMessage($message);
        $this->assertTrue($result === $message);

        $test    = new \Qithub\Core\MyClass();
        $result  = $test->returnMessage($message);

        $this->assertTrue($result === $message);
    }

    public function tearDown()
    {
        restore_error_handler();
    }
}
