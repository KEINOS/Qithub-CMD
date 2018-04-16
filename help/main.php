<?php
/* ============================================
 *   help plugin
 * ============================================
 * Usage : 呼び出されたら Qithub のヘルプを返すだけのプラグイン
 * Require : none
 * Return value: json string
 */

require('functions.php.inc');

$text_help =<<<EOF
Qithub の BOT のコマンドの基本的な使い方を説明中。


`help` コマンドで使えるオプションは `@qithub:help --help` とダイレクト%%
・トゥートしてください。


EOF;

$text_help = str_replace("%%\n", '', $text_help);

$text_option =<<<EOF
Usage: help [options]

[options]
  extension   list of extensions and program language available.


EOF;

// Input
$request = get_api_input_as_array();

if (isset($request['args']) && ! empty($request['args'])) {
    $args    = explode(' ', trim($request['args']));
    $arg_1st = $args[0];
    $result  = '';
    switch ($arg_1st) {
        case 'extension':
        case 'extensions':
            $result = "Here comes a list of extensions. 利用可能な拡張子一覧を表示予定。";
            break;
        case '--help':
            $result = $text_option;
            break;
        default:
            $arg_1st = sanitize_toot_string($arg_1st);
            $result = "help: no help topics match '${arg_1st}'.  Try ':${arg_1st} --help'.";
    }
} else {
    $result = $text_help;
}

// Output
$status = 'OK';

print_output_as_api($status, $result);
