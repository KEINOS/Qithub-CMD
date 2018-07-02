<?php
/**
 * box.phar installer.
 *
 * Installs box.phar on behalf of the original installer.
 * If you feel insecure about the code below, you better download the
 * installer and install it your own.
 */

$url_installer = 'https://raw.githubusercontent.com/KEINOS/Phar_Box3_installer/Box3_installer/installer.php';

if (! file_exists('./box.phar')) {
    eval(trim(file_get_contents($url_installer), '<?php'));
} else {
    echo `php ./box.phar update`;
}
