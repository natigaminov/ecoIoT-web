# ecoiot_server

Серверная часть проекта EcoIoT. Принимает POST запросы от датчика и записывает данные в БД. Доступ пользователя к БД осуществляется через специальный веб-интерфейс

Состоит из трех docker-контейнеров:
 - ecoiot_postgresql - СУБД PostgreSQL 14.4
 - ecoiot_postgresql_adminer - веб-интерфейс Adminer
 - ecoiot_server - FastAPI сервер с автодокой и интерактивными API (Swagger)

## Внешние зависимости
 - Docker-compose >= 1.27 (желательно 1.29)
 - Docker >= 20.10.12
 - Python 3.9 (для отладки)
 - Ubuntu >= 18.04

## Установка
Для установки внешней зависимости docker-compose запустите скрипт:
```bash
bash prerequisites.sh
```
Остальные внешние зависимости разрешайте в частном порядке

Для установки внутренних зависимостей при отладке используйте команду:
```bash
pip install -r requirements.txt
```

## Запуск:
Перед запуском обязательно переименуйте или скопируйте файл `.env.example` в `.env`
и в нем укажите необходимые значения переменных:
 - `dbms_admin_login` - логин админа для СУБД
 - `dbms_admin_pwd` - пароль админа для СУБД
 - `dbms_host` - адрес хоста СУБД, для отладки значение `localhost`, для деплоя `postgresql`, т.к. при деплое сервисы соединяются по внутренней сети docker
 - `gases_database_name` - имя БД для газовых значений датчиков
 - `api_access_token` - токен доступа к API (эндпоинтам)

После чего для деплоя введите:
```bash
docker-compose up -d
```
Для отладки закомментируйте в файле `docker-compose.yaml` сервис `ecoiot_server` и добавьте проброс портов в сервис `postgresql`,
также в файле `.env` укажите у переменной `dbms_host` значение `localhost`, после чего выполните команду:
```bash
docker-compose up -d
```
При этом поднимутся только сервисы с СУБД и веб-интерфейсом для нее.

Сам веб-сервер отдельно запустите командой:
```bash
python -m app
```

## Как работает
При деплое все сервисы ждут, пока не поднимется сервис с СУБД, после чего сервис `ecoiot_server` подключается к СУБД, создает новые БД и заливает в них
миграции. Далее он генерирует из созданных БД модели для ORM `SQLAlchemy`. К этому времени на веб-сервере поднимаются API и уже можно слать на них запросы. Запросы к API валидируются через `pydantic` и в случае некорректного формата данных выбрасывается ошибка валидации в ответе на запрос. Роуты группируются в роутеры по соответствующим БД. Более подробную информацию об API можно увидеть в автодоке `Swagger` по адресу `localhost:8090/docs`

## Документация API
Для просмотра и интерактивного использования API перейдите по адресу `localhost:8090/docs`, 
там можно увидеть описание входных значений, ответов эндпоинтов и прочее, также можно использовать API в интерактивном режиме.
В дополнение есть другой вид интерфейса документации Swagger по адресу `localhost:8090/redoc`, но в нем отсутствует интерактивный режим

## Доступ к СУБД
Для просмотра и прочего взаимодействия с СУБД перейдите по адресу `localhost:8085` в веб-интейрфейс Adminer,
где нужно будет ввести логин и пароль из файла `.env`

## Добавление новой БД
Если понадобится добавить новую БД, то нужно проделать следующие действия:

1. В файле `.env` укажите переменную и значение названия новой БД, например:
```bash
waters_database_name=waters
```
2. После чего в файле `app/settings.py` добавить такое же поле и тип в класс `Settings`.
Именно через этот класс осуществляется доступ к переменным в `.env` через `pydantic`
3. В папке `app/libs/postgresql` создать папку с названием новой БД и добавить туда файл миграций с расширением `.sql` (сайт, где можно удобно составить БД и экспортировать в миграции https://dbdiagram.io)
4. Затем в файле `app/main` в список `databases` добавить объект класса `DataBase` с параметрами новой БД, после чего в папке новой БД рядом с файлом миграций появится файл `models.py` с моделями для `SQLAlchemy`
5. Модифицируйте методы репозитория `MeasureRepository` (`app/repositories/measure.py`) в соответствии с новой БД или создайте новый репозиторий по его подобию
6. После чего создайте новый роутер в папке `routers` для новой БД по подобию уже имеющегося
