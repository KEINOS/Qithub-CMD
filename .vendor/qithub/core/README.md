[![Build Status](https://travis-ci.org/Qithub-BOT/Qithub-CORE.svg?branch=master)](https://travis-ci.org/Qithub-BOT/Qithub-CORE)

## Qithub-CORE とは

`Qithub-CORE` は `Composer` でインストール可能な PHP ライブラリです。

主に `Qithub-BOT` を構成する `Qithub-API` や `Qithub-CMD` などのクラスの継承元となる親クラスと、共通する関数を提供しています。

## `composer.json` の記述例

自分の PHP アプリで Qithub-CORE ライブラリを使いたい場合は、自分のプロジェクトの `composer.json` に以下の内容を追記してください。

```
{
    "repositories": [
        {
            "type": "vcs",
            "url": "git@github.com:Qithub-BOT/Qithub-CORE.git"
        }
    ],
    "require": {
        "qithub/core": "master@dev"
    }
}
```

**Note:** Qithub-BOT 関連の PHP ライブラリは GitHub のリポジトリで提供しています。そのため composer のデフォルトの検索先のリポジトリである **Packagist からはインストールできない**ので、 "composer.json" の "repositories" 要素に GitHub のリポジトリを追加する必要があります。

## Qithub-CORE のインストール

`composer.json` に上記内容を記載したのち、`$ composer install` を実行すると、`vendor/qithub/core/` ディレクトリに、このリポジトリの内容（ライブラリ）がインストールされます。

以降は `$ composer update` を実行するだけで、Qithub-CORE リポジトリ（の`master`ブランチ）の最新版がダウンロードされます。

## Qithub-CORE の依存関係

Qihub-CORE 自体は依存ライブラリの必要のない Pure PHP で書かれており、PHP 5.6 以上で動作することを目標としています。

このライブラリのパッケージ（composer.json）にある依存情報（"require-dev"要素）は、Qithub-CORE の開発でユニット・テストに使われるためのもので、本体そのものの動作には影響ありません。

## ライブラリの利用方法

検証中

## ディレクトリ構成

```
Qithub-CORE/
	┣━ README.md （このファイル）
	┣━ .git/ （このリポジトリの git 情報）
	┣━ .gitignore/ （git 同期で除外するファイル／ディレクトリを指定）
	┣━ .travis.yum （Travis CI の設定ファイル。テスト・チェック）
	┣━ sideci.yum （Side CI の設定ファイル。構文チェック）
	┣━ composer.json （PHPUnit インストール用 Composer 設定ファイル）
	┣━ composer.lock （検証時の Composer 環境再現ファイル）
	┣━ src/ （メインとなるソースコード）
	┃	┣━ index.php
	┃	┣━ Functions.php （ユーザ関数一覧）
	┃	┗━ Classes.php （クラス一覧）
	┗━ test/ （Travis CI で実行するテスト）
		┣━ FunctionsTest.php
		┗━ ClassesTest.php
```

## Qithub-CORE の開発に参加する

Qithub-CORE ライブラリを利用する側でなく、改善・開発・リファクタに参加したい場合は、このリポジトリを `clone` して `PR` してください。

まだ `git` や GitHub でのコラボレーションに慣れていない方は、具体的な参加方法を Qithub-ORG の wiki に記載しますので、遠慮なく試してみてください。

## 検証環境

以下の環境で動作した PHP スクリプトを Travis CI で PHPUnit テストを通します。

- macOS High Sierra(OSX 10.13.4)
    - PHP 7.1.14 (cli)

- PHPUnit v.5.7.27 via Composer
    - PHP 5.6, 7.0, 7.1 コンパチは PHPUnit 5 であるため
