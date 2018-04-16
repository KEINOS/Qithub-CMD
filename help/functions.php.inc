<?php

/**
 * get_api_input_as_array function.
 * 標準入力より Qiita API 準拠で受け取った Qithub エンコードデータを PHP 配列で返す。
 *
 * @access public
 * @return array
 * @ver 20171220
 */
function get_api_input_as_array()
{
    return json_decode(get_api_input_as_json(), JSON_OBJECT_AS_ARRAY);
}

/**
 * get_api_input_as_json function.
 * 標準入力より Qiita API 準拠で受け取ったデータを Qithub エンコードデータを JSON文字列で返す。
 *
 * @access public
 * @return string JSON format string
 * @ver 20171220
 */
function get_api_input_as_json()
{
    return urldecode(get_stdin_first_arg());
}

/**
 * get_stdin_first_arg function.
 * 標準入力の第１引数返す。（Qithub API 準拠）
 *
 * @access public
 * @return string
 * @ver 20171220
 */
function get_stdin_first_arg()
{
    // CLIからの標準入力を取得
    global $argv;

    // 引数１は必須
    if (empty($argv[1])) {
        print_output_as_api('NG', 'Argument is empty.');
    }

    return trim($argv[1]);
}

/**
 * print_output_as_api function.
 * 処理結果を Qithub の スクリプト間 API に準拠して標準出力する
 *
 * @access public
 * @param  string $status    "OK" or "NG" の文字列
 * @param  string $contents  処理結果
 * @return string
 */
function print_output_as_api($status, $contents)
{
    $status = (string) $status;
    $status = trim($status);
    $status = ( 'ok' == $status ) ? 'OK' : $status;

    $contents = (string) $contents;

    $array = [
        'result' => $status,
        'value'  => $contents,
    ];

    echo encode_array_to_api($array);
    die();
}

/**
 * encode_array_to_api function.
 * PHP 配列を Qithub エンコードに変換する。
 *
 * @param  array  $array
 * @return string              Qithub エンコード文字列
 * @link https://github.com/Qithub-BOT/scripts/issues/16
 */
function encode_array_to_api($array)
{
    $json_raw = json_encode($array);
    $json_enc = urlencode($json_raw);

    return $json_enc;
}


function sanitize_toot_string($string)
{
    return urlencode($string);
}
