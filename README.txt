

$ docs
назначение репозитория -> for different notes



По дефолту git pull и git push сейчас качает через https, надо переделать чтобы связь была по ssh.
Для этого:
    - генерируем ключ
      $ ssh-keygen -t ed25519 -C "aceqbaceq@github.com"
    - запускаем ssh-agent
      eval `ssh-agent -s`
    - добавляем ключ в агент
      ssh-add ~/.ssh/id_ed25519
    - копируем в буфер содержимое публичного ключа и вставляем на github.com в  profile-settings-ssh and gpg keys
      cat ~/.ssh/id_ed25519.pub
    - тестируем связь по ssh с github
      $ ssh -T git@github.com
        Hi aceqbaceq! You've successfully authenticated, but GitHub does not provide shell access

      тут возникает вопрос а как же происходит аутентификация получается мы стучимся на гитхаб под ssh логином git а как же это так 
      ведь у нас логин aceqbaceq в веб морде, плюс мы неуказали ssh ключ. ответ на эти вопросы тут = https://github.com/aceqbaceq/docs/blob/master/gitlab.txt а пока двигаем дальше.


по дефолту гит вбивает чтобы связт с репозиторием шла по https. 
это остой нам это ненадо потому что там надо вводить при коммитах логин и пароль
и это никак не автоматизировать. вместо этого надо поменять чтобы связт с репозиторием
при коммитах шла по ssh. и тогда мы можем использовать git-agent куда один раз вбиваем
пароль от публичного ключа и забываем о проблеме каждый раз вводить логин пароль 
при коммитах. для этого:
  - входим на компе в папку с репозиторием. и проверяем какой спсооб на даннй момент
    юзается при комитах для связи
    $ git remote -v
      origin  https://github.com/aceqbaceq/docs.git (fetch)
      origin  https://github.com/aceqbaceq/docs.git (push)

    как видно юзает метод https.
    заменяем его на метод ssh:
    $ git remote set-url origin git@github.com:aceqbaceq/docs.git

    проверяем что сработало:
    $ git remote -v
      origin  git@github.com:aceqbaceq/docs (fetch)
      origin  git@github.com:aceqbaceq/docs (push)


    теперь можно пушить:

    $ git add .

    $ git commit -m "comment smth here"

    $ git push

если все таки на git push оно ругается то пишем полный путь

$ git push git@github.com:aceqbaceq/docs.git master

если после этой команды мы получаем отлуп

Enter passphrase for key '/c/Users/a.v/.ssh/id_rsa':
git@github.com: Permission denied (publickey).
fatal: Could not read from remote repository.

это какойто дурацкий глюк. запускаем еще раз команду. система спросит пароль от ключа. и мы успешно запушим коммит.

для загрузки с github
$ git pull git://github.com/aceqbaceq/docs.git master


/
/
