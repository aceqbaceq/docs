
$ docs
назначение репозитория -> for different notes



По дефолту git pull и git push сейчас качает через https, надо переделать чтобы связь была по ssh.
Для этого:
    - генерируем ключ
      $ ssh-keygen -t ed25519 -C "aceqbaceq@gmail.com"
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
      ведь у нас логин aceqbaceq в веб морде, плюс мы неуказали ssh ключ. По поводу ключа - при попытке аутентификации ssh клиент будет пробовать в качестве ключа
      все ключи которые лежат в папке ~/.ssh/* путем их перебора. С ключом разобрались. По поводу логина git под которым мы по ssh стучимся на github. Дело в том что
      как выглядит процесс добавления ssh юзера на удаленном сервере. На удаленном сервере мы идем в папку /home/имя_юзера/.ssh/authorized_keys  и в этот файл 
      добавляем наш публичный ключ либо руками через copy/paste либо через команду ssh-copy-id имя_юзера@remote_host. в итоге файл authorized_keys будет иметь
      вид
	$ cat authorized_keys 
	ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAINa9Cne2PSkLOruVDWdHyj6eKFLswfLFtyeIJf/jppen aceqbaceq@gmail.com

      после этого мы можем стучаться на удаленый сервер через ssh имя_юзера@remote_host
      отсюда вытекает то что если мы на удаленном сервере можем добавить наш публичный ключ к любому линукс юзеру на удаленном хосте, может дбавить сразу к куче 
      юзеров 
	/home/vasya/.ssh/authorized_keys
	/home/petya/.ssh/authorized_keys
	/home/klava/.ssh/authorized_keys
      и значит мы сможем входить с нашим ключом под любым юзером vasya, petya, klava
	ssh vasya@IP
	ssh petya@IP
	ssh klava@IP
      тоесть от нашего ключа ничего независит все зависит в какую папку на удаленном сервере добавят наш ключ.
      очевидно что когда мы регистрируемся на сайте гитхаб то наш публичный ключ добавляют в папку /home/git/.ssh/authorized_keys
      поэтому мы можем стучаться на сайт гитхаба по ssh от имени юзера git. а то что у нас в веб морде гитхаба используется логин aceqbaceq а не git это совсем другая история.
      потому что логин для службы ssh и логин для http службы это совершенно разные назависимые логины.(хотя по интуитивной логике кажется что если мы на веб входим под логином
      aceqbaceq то и для ssh входа тоже должен использовтся логин aceqbaceq). если попробовать войти как ssh aceqbaceq@github.com то он пошлет, что совершенно однзначно докзывает
      что гитхаб добалвяет наш публичный ключ именно для линукс юзера git и это все зависит от архитекторов гитхаба а не с нашей стороны. публичный ключ таким образом играет роль
      пароля а какой логин это нам надо самим знать исходя как это настроено на удаленном сервере. получается что на удаленный сервер мы можем зайти под неким логином под разными
      публичными ключами это как бы как по аналогии что можно было бы зайти на комп под одним логином и одновременно несколкьими паролями. прикол. 
      и тут следубщий еще прикол совершенно логично что все кто ломится на гитхаб по ssh они все ходят под логином git то есть ssh git@github.com - это уже понятно. все их публичные
      ключи добавлены в файл /home/git/.ssh/authorized_keys. вопрос в другом что когда мы вошли то гитхаб распознает что вошел под юзером git человек с публичным ключом aceqbaceq
      а именно:
      $ ssh -T git@github.com
        Hi aceqbaceq! You've successfully authenticated, but GitHub does not provide shell access

      как же гитхаб это делает ?








пропишем удаленный репозиторий как дефолтовый на нашем компе

$ git remote add origin git@github.com:aceqbaceq/docs.git

$ git push -u origin master

теперь нам ненадо прописывать полный путь к удаленному репозиторию 
а юзать просто git push, а именно для записи в репозиторий

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
