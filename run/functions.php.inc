<?php
/**
 * Constants for `run` plugin
 * =====================================================================
 * @author KEINOS(https://github.com/KEINOS)
 */
const ONLY_FIRST_ARG   = 1;
const ENDPOINT_WANDBOX = 'https://wandbox.org/api/compile.json';

/**
 * Functions for `run` plugin
 * =====================================================================
 * @author KEINOS(https://github.com/KEINOS)
 */

function is_mode_debug()
{
    if (! defined('IS_MODE_DEBUG')) {
        $input_array   = get_api_input_as_array();
        $is_mode_debug = false;
        if(isset($input_array['mode']) && ! empty($input_array['mode'])){
            $is_mode_debug = ('debug'==$input_array['mode']);
        }
        defined('IS_MODE_DEBUG') or define('IS_MODE_DEBUG', $is_mode_debug);
    } else {
        return IS_MODE_DEBUG;
    }
}

function request_wandbox($data_json)
{
    // json形式のデータをpostするので必要
    $header = [
        'Content-Type: application/json',
    ];

    $context = stream_context_create([
        'http' => [
            'method'  => 'POST',
            'header'  => implode(PHP_EOL, $header),
            'content' => $data_json,
            'ignore_errors' => true
        ]
    ]);

    $response = file_get_contents(
        ENDPOINT_WANDBOX,
        false,
        $context
    );

    $result['header'] = $http_response_header;
    $result['result'] = json_decode($response, true);

    return $result;
}

function print_pretty($mix, $return = false)
{
    $result  = '';
    $result .= '<pre>';

    if (is_string($mix)) {
        $result .= htmlentities($mix);
    } else {
        $result .= htmlentities(print_r($mix, true));
    }
    $result .= '</pre>';

    if ($return) {
        return $result;
    } else {
        echo $result;
        return true;
    }
}

// https://singoro.net/note/mb_substr-mb_strpos/

function withdraw_code($toot)
{
    $toot             = trim((string) $toot);
    $result           = array();
    $exploded         = explode_multi([' ',PHP_EOL], $toot, 2);
    $program_lang     = trim($exploded[0]);
    $string           = $exploded[1];
    $delimiter        = '```'; //code block delimiter
    $num_appear_delim = mb_substr_count($string, $delimiter);
    $deft_name_file   = 'unknown';
    $is_block_closed  = ($num_appear_delim % 2) ? false : true;

    if (! $is_block_closed) {
        return false;
    }

    $lines     = explode(PHP_EOL, $string);
    $is_block  = false;
    $code      = '';
    $leftover  = '';
    $name_file = array();
    $cnt_block = 0;

    // fetch string while code block
    foreach ($lines as $key => $line) {
        if (has_delimiter($delimiter, $line)) {
            if ($is_block) {
                // closing block
                $result[] = [
                    'name' => $name_file,
                    'code' => $code,
                ];
            } else {
                // opening block
                $code      = ''; //reset stored code
                $name_file = fetch_filename($delimiter, $line);
                if (empty($name_file)) {
                    $name_file = (0 == $cnt_block)
                        ? 'main'
                        : $deft_name_file . $cnt_block;
                    $name_file .= ".${program_lang}";
                }
                $cnt_block++;
            }
            $is_block = ! $is_block; //switch block state
        } elseif ($is_block) {
            // store code line
            $code .= $line . PHP_EOL;
        } else {
            // store other than codes
            $tmp = trim($line);
            if (! empty($tmp)) {
                $leftover .= $tmp . PHP_EOL;
            }
        }
    }
    $result['prog_lang'] = $program_lang;
    $result['leftover']  = $leftover;

    return $result;
}

function has_delimiter($delimiter, $string)
{
    return (mb_substr_count($string, $delimiter));
}

function fetch_filename($delimiter, $string)
{
    $string = (string) $string;
    $result = str_replace($delimiter, '', $string);

    return trim($result);
}

/**
 * explode_multi function.
 *
 * Split a string by an array of string and limitable
 *
 * @access public
 * @param  array    $delimiters
 * @param  string   $string_raw
 * @param  integer  $limit (default: PHP_INT_MAX)
 * @return array
 */
function explode_multi($delimiters, $string_raw, $limit = PHP_INT_MAX)
{
    $string_tmp = (string) $string_raw;
    $string_rep = str_replace($delimiters, $delimiters[0], $string_raw);
    $exploded   = explode($delimiters[0], $string_rep, $limit);
    $result     = array();
    for ($key = 0; $key < ($limit-1); $key++) {
        $pattern    = $exploded[$key];
        $string_tmp = preg_replace("/${pattern}/", '', $string_tmp, 1);
        $result[]   = $pattern;
    }
    $result[] = trim($string_tmp);

    return $result;
}

/**
 *  get_name_compiler function.
 * ---------------------------------------------------------------------
 * Returns compiler name from program name.
 *
 * @access public
 * @param  string $program_lang
 * @return array
 */
function get_name_compiler($program_lang)
{
    $program_lang  = trim(strtolower((string) $program_lang));
    $list_compiler = get_list_compiler();
    if (array_key_exists($program_lang, $list_compiler)) {
        $result = $list_compiler[$program_lang];
    } else {
        $result = false;
    }

    return $result;
}


/**
 * get_list_compiler function.
 * ---------------------------------------------------------------------
 * Returns list of compilers available at Wandbox.
 *
 * @access public
 * @return array
 * @todo Compiler names list must be taken automatically rather than
 * hard coded.
 * @ref https://github.com/rhysd/wandbox-vim/blob/master/autoload/wandbox.vim
 */
function get_list_compiler()
{
    $wandbox_default_compiler = [
        'c'          => 'clang-head-c',
        'coffee'     => 'coffeescript-head',
        'cpp'        => 'clang-head',
        'crystal'    => 'crystal-head',
        'cs'         => 'mono-head',
        'd'          => 'dmd-head',
        'elixir'     => 'elixir-head',
        'erlang'     => 'erlang-head',
        'go'         => 'go-head',
        'groovy'     => 'groovy-head',
        'haskell'    => 'ghc-head',
        'java'       => 'openjdk-head',
        'javascript' => 'nodejs-head',
        'lazyk'      => 'lazyk',
        'lisp'       => 'sbcl-head',
        'lua'        => 'lua-5.3.4',
        'nim'        => 'nim-head',
        'ocaml'      => 'ocaml-head',
        'pascal'     => 'fpc-head',
        'perl'       => 'perl-5.25.10',
        'php'        => 'php-head',
        'pony'       => 'pony-head',
        'python'     => 'cpython-head',
        'rill'       => 'rill-head',
        'ruby'       => 'ruby-head',
        'rust'       => 'rust-head',
        'scala'      => 'scala-2.13.x',
        'sh'         => 'bash',
        'sql'        => 'sqlite-head',
        'swift'      => 'swift-head',
        'vim'        => 'vim-head',
    ];

    return $wandbox_default_compiler;
}

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
    $status = trim($status);
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
