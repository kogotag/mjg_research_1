# Исследовательская работа по механике жидкости и газа на тему вихревых методов рассчёта
Этот репозиторий используется для передачи кода программы преподавателю и вскоре будет закрыт.

## Использование .env файла для настройки программы
Для удобства я использую .env файл в папке программы, в котором указываются настройки. Этого файла по умолчанию нет в репозитории, см. следующий пункт. Текущие параметры настройки:
* DATA_PATH — путь к папке, содержащий файл с данными. Если этот параметр отсутствует, то программа использует свою папку.
* DATA_FILENAME — название файла с данными.

## Как настроить .env
В папке с программой находится файл образец .env.example. Его можно скопировать и переименовать в .env, затем изменить необходимые настройки.

**Внимание!** Без корректного .env файла, программа не будет работать.
