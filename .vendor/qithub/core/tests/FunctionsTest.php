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

trait DataProvider
{
    static function provideDataJson()
    {
        return [
            [ true , '[{"user_id":13,"username":"stack"},{"user_id":14,"username":"over"}]' ],
            [ true , json_encode(array('hoge'))],
            [ false, json_encode('hoge')],
            [ false, '{background-color:yellow;color:#000;padding:10px;width:650px;}' ],
            [ false, '0123456' ],
            [ false, 12345 ],
        ];
    }
}

class ValidationJsonStringTest extends TestCase
{
    use QithubSetup;
    use DataProvider;

    /**
     * @dataProvider provideDataJson
     */
    public function testIsJson($expect, $json)
    {
        $result = \Qithub\fn\isJson($json);
        $this->assertSame($expect, $result);
    }

}

class SampleTest extends TestCase
{
    use QithubSetup;

    public function testReturnMessage()
    {
        $message = 'Hello, World!';
        $result  = Qithub\fn\return_message($message);

        $this->assertTrue(is_string($result));
    }
}
