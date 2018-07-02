
## ローカルに開発とテスト環境を作る

1. このリポジトリを `fork` します。
1. `Fork` したリポジトリをローカルに `clone` します。
1. クローンしたリポジトリにカレントディレクトリを移します。
1. 自分の環境の PHP バージョンを確認します。
1. `.travis.yml` に自分の PHP バージョンを追記します。
1. `composer.lock` ファイルを削除します。（`$ rm composer.lock`）
1. `composer` コマンドが使えるのを確認します。（`$ composer --version`）
    - `composer.phar` をダウンロードして `$ php path/to/composer.phar --version` でも OK。
1. 開発環境をインストールします。
    - `$ composer install`
1. `vendor` ディレクトリが出来たのを確認し、PHPUnit のバージョンを確認します。
    - `$ vendor/bin/phpunit --version`

## テストを実行する

1. `tests` ディレクトリ内のテストを実行する。
    - `$ vendor/bin/phpunit tests`
    - 「OK, but incomplete, skipped, or risky tests!」と出れば OK。<br>記述中の「..I」は、３つのテストのうち２つがパスして１つをスキップしたことを意味します。

