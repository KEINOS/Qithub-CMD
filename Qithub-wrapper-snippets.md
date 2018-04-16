# Qithub API の各種言語のラッパーのスニペット一覧

本体スクリプト（`Qithub-BOT/scripts/index.php`。以下、本体スクリプト）から受け取るデータと、その処理結果を表示するための仕様に準拠したユーザー関数の各種言語のスニペット一覧です。

基本的には、Qithub プラグインの API に準拠していれば各自で実装して構いません。

---

# プラグイン・スニペット

## PHP

```functions.php
<?php
/**
 *  おうむ返しのサンプル・プラグイン.
 * =====================================================================
 * Usage : 受け取ったデータをそのままJSONで返します。
 * Require : none
 * Return value: json string
 */

// Input
$input_array = get_api_input_as_array();

// 処理のサンプル
$contents_array  = $input_array;
$contents_string = json_encode( $contents_array );

// 処理のステータス
$status = 'OK';

// Output
print_output_as_api( $status, $contents_string );

die;

/*
========================================================================
  入力系関数
========================================================================
*/

/**
 * get_api_input_as_array function.
 * ---------------------------------------------------------------------
 * 本体スクリプトからのコマンドライン実行により Qiita API 準拠で受け取っ
 * た Qithub エンコードデータを PHP 配列に変換する。
 *
 * @access public
 * @return array
 * @ver 20180113
 */
function get_api_input_as_array()
{
    return json_decode(get_api_input_as_json(), JSON_OBJECT_AS_ARRAY);
}

/**
 * get_api_input_as_json function.
 * ---------------------------------------------------------------------
 * 本体スクリプトからのコマンドライン実行により Qiita API 準拠で受け取っ
 * た Qithub エンコードデータを JSON 文字列に変換する。
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
 * ---------------------------------------------------------------------
 * 標準入力の第１引数返す。（Qithub API 準拠）
 *
 * @access public
 * @return string
 * @ver 20180113
 */
function get_stdin_first_arg()
{
    // CLIからの引数を取得
    global $argv;

    // 引数１は必須
    if (empty($argv[1])) {
        print_output_as_api('NG', 'Argument is empty.');
    }

    return trim($argv[1]);
}

/*
========================================================================
  出力系関数
========================================================================
*/

/**
 * print_output_as_api function.
 * ---------------------------------------------------------------------
 * 処理結果を Qithub の スクリプト間 API に準拠して標準出力する
 * 
 * @access public
 * @param  string $status    "OK" or "NG" or エラーコードの文字列
 * @param  string $contents  処理結果
 * @return string
 * @ver 20180113
 */
function print_output_as_api($status, $contents)
{
    $status = (string) $status;
    $status = trim( $status );
    $status = ( 'ok' == $status ) ? 'OK' : $status;

    $contents = (string) $contents;

    $array = [
        'result' => $status,
        'value'  => $contents,
    ];

    echo encode_array_to_api($array);
    
    die;
}

/*
========================================================================
  エンコード系関数
========================================================================
*/

/**
 * encode_array_to_api function.
 * ---------------------------------------------------------------------
 * PHP 配列を Qithub エンコードに変換する。
 *
 * @param  array  $array 
 * @return string              Qithub エンコード文字列
 * @ver 20180113
 * @link https://github.com/Qithub-BOT/scripts/issues/16
 */
function encode_array_to_api($array)
{
    $json_raw = json_encode($array);
    $json_enc = urlencode($json_raw);

    return $json_enc;
}

```

---


