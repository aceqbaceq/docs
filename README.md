
$ docs
for different docs


для записи в репозиторий
$ git add .
$ git commit -m "comment smth here"
$ git push git@github.com:aceqbaceq/docs.git master

если после этой команды мы получаем отлуп

Enter passphrase for key '/c/Users/a.v/.ssh/id_rsa':
git@github.com: Permission denied (publickey).
fatal: Could not read from remote repository.

это какойто дурацкий глюк. запускаем еще раз команду. система спросит пароль от ключа. и мы успешно запушим коммит.

для загрузки с github
$ git pull git://github.com/aceqbaceq/docs.git master


