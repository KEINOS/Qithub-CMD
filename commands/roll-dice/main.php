<?php
/**
 * 指定したサイコロを振った結果を返すスクリプト
 *
 * @copyright Qithub Organization All Rights Reserved
 * @license CC-BY-SA-4.0
 * @author
 *     @hidao80 (https://github.com/hidao80)
 * @collaborators
 *     @KEINOS (https://github.com/KEINOS)
 * @link https://github.com/Qithub-BOT/
 * @php version >=5.5.9-1
 */

require("functions.php.inc");

/* =====================================================================
    Main
   ===================================================================== */
// 処理結果（`result`キー）のデフォルト
$result_status = 'OK';

// UTF-8, TIMEZONEを日本仕様に設定
set_utf8_ja('Asia/Tokyo');

// スクリプトの引数を取得
$api_requests = get_api_input_as_array();

if (isset($api_requests['args']) && ! empty($api_requests['args'])) {
    // プラグインの引数を取得（リクエスト内の`args`値）
    $arg_raw   = $api_requests['args'];
    $arg_array = explode(' ', $arg_raw);

    // ダイスコードを取得（`args`より最初の引数）
    $dice_code = $arg_array[0];

    // emoji 出力のオプション取得（`args`より`--use_emoji`の有無）
    $use_emoji = in_array('--use_emoji', $arg_array);

    // メッセージの作成（RAW）
    $result_msg_raw = roll_dice($dice_code, $use_emoji);
    $result_msg     = json_encode($result_msg_raw, JSON_PRETTY_PRINT);
} else {
    $result_status = 'OK';
    $result_msg    =<<<EOL
roll-dice: empty subcommand.
Run 'roll-dice --help' for usage.

EOL;
}

// API準拠の出力結果作成
$msg_api = [
    'result' => $result_status,
    'value'  => $result_msg,
];

// Qithubエンコード
$msg_enc = json_encode($msg_api);
$msg_enc = urlencode($msg_enc);

// プラグインの処理結果を出力
echo $msg_enc;

die();
