## Rock paper scissors GUI App


## System Requirements

Linux platform with installed g++ and MySQL for database testing. For Debian/Ubuntu, you can install mysql-server and mysql-client.

	$ sudo apt-get install mysql-server mysql-client

You also need MySQL Development library, libmysqlcppconn-dev.

	$ sudo apt-get install libmysqlcppconn-dev

 For GTK+3.0 you have install the following
    $ sudo apt-get install libgtkmm-3.0-dev
    $ sudo apt-get install libgtkmm-3.0

## Database

For database testing, you can run database.sql script to execute database and table. Credentials used username : "root" password : "root"; File database/db.cpp.
For network please enter your internal IP in sockets/clientsocket.cpp. "192.x.x.x".

## Compiling & Linking

Before compiling, please change database configured based on your MySQL configuration and also the Network IP in clientsocket.cpp.

	$ g++ -Wall main.cpp sockets/serversocket.cpp sockets/clientsocket.cpp protocol/gameprotocol.cpp protocol/packetprotocol.cpp ui/gtkui.cpp pubsub/subject.cpp database/db.cpp  `pkg-config --cflags --libs gtkmm-3.0` -std=c++11 -I/usr/include/cppconn -L/usr/lib/mysql -lmysqlcppconn
    $ ./a.out




