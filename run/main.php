<?php
/**
 *  仮想実行プラグイン.
 * =====================================================================
 * トゥート内のコード・ブロックを指定言語で実行し、その結果を返します。
 *
 * 実行はオンライン・コンパイラ「Wandbox」の API を利用しています。
 *
 * @author KEINOS(https://github.com/KEINOS)
 */

require_once('functions.php.inc');

// プラグイン引数
$input_array = get_api_input_as_array();

// 初期設定
$name_plugin   = $input_array['plugin_name'];
$args          = $input_array['args'];
$elements      = withdraw_code($args); //Withdraw code and prog name.
$lang_program  = $elements['prog_lang'];
$name_compiler = get_name_compiler($lang_program);

// リクエストのオブジェクト作成
$request_array = [
    'code'     => $elements[0]['code'],
    'options'  => 'warning',
    'compiler' => $name_compiler,
    'compiler-option-raw' => '',
];
$request_json = json_encode($request_array, JSON_PRETTY_PRINT);

// 処理実行（Wandboxにリクエスト）
$result_wandbox = request_wandbox($request_json);

// 処理結果（レスポンス内容）の設定（Qithubプロトコル）
$status = ( 0 == $result_wandbox['result']['status'] ) ? 'OK' : 'NG';
$contents_string = $result_wandbox['result']['program_message'];

// デバッグ・モード時の付加情報
if (is_mode_debug()) {
    $result['value']          = $contents_string;
    $result['elements']       = $elements;
    $result['request_json']   = $request_json;
    $result['result_wandbox'] = $result_wandbox;

    $contents_string = json_encode($result, JSON_PRETTY_PRINT);

    $contents_string = print_pretty($contents_string, true);
}

// 処理結果の表示（Qithubエンコード）
print_output_as_api($status, $contents_string);
