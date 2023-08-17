Перед использование приложений необходимо создать и настроить базу данных
Команды для настройки базы данных необходимо ввеасти в терминале в приведенном ниже порядке
1) sudo mysql;
2) create database nameDB; создать БД где - nameDB имя создаваемой БД(указать свое)
3) CREATE USER 'user'@'localhost' IDENTIFIED BY 'password'; - Создать пользователя БД где user и password - логин и пароль пользователя(указать свои)
4) GRANT SELECT,UPDATE,INSERT ON nameDB . * TO 'user'@'localhost'; - дать права пользователю user к БД nameBD
5) use nameDB; - выбрать БД
6) create table if not exists users (u_id int auto_increment primary key, login varchar(255), password varchar(255)); - создать таблицу users
7) create table if not exists chats (c_id int auto_increment primary key, user1 varchar(255), user2 varchar(255)); - создать таблицу chats
8) create table if not exists messages (m_id int auto_increment primary key, c_id int, author varchar(255), message varchar(1000)); - создать таблицу messages
База данных создана настроена и готова к работе. Запустить приложение сервер и ввести запрашиваемые данные(Имя БД, логин и пароль пользователя, созданных ранее)
Нажать запустить сервер. Запустить приложение клиент 
