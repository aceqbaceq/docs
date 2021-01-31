в папке main-files лежат все необхдоимые файлы чтобы все заработало
в папке different-hlam лежат разные файлы которые были использованы при подоготовке проекта

--

pagecache_switch_snapshots.sh - это самый главный файл он переключает снэпшоты
pagecache_start_after_reboot.sh - этот скрипт монтирует оверлей раздел после перезарузки компа и запускает самбу
pagecache-start.service - это systemd служба которая срабатывает при старте компа и вызывает pagecache_start_after_reboot.sh
pagecache_freespace_check.sh - это скрипт который надо поместить в cron и он проверяет сколько осталось свободного места на разделе
    и если ниже порогового то вызывает  pagecache_switch_snapshots.sh который переключает снэпшот
smb.conf - конф файл самбы до кучи так как ради нее все и выстраивается
--

в crontab надо вставить строчку

* * * * * /usr/local/bin/pagecache_freespace_check.sh >/dev/null 2>&1

скрипт будет запускаться каждую минуту

--
