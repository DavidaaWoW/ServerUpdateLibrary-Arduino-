#include "ServerUpdate.h"

//Время в конструкторе умножается на 60000, чтобы в дальнейшем использовать минуты
ServerUpdate::ServerUpdate(String type, String address, double time = 0)
{
	this->type = type;
	this->time = time*60000;
	this->address = address;
}

bool ServerUpdate::setType(String type)
{
	this->type = type;
}

bool ServerUpdate::setAddress(String address)
{
	this->address = address;
}

bool ServerUpdate::setTime(double time)
{
	this->time = time*60000;
}

String ServerUpdate::getType()
{
	return this->type;
}

double ServerUpdate::getTime()
{
	return this->time;
}

//Выводим сообщение о начале обновления
void ServerUpdate::update_started() 
{
	Serial.println("Update started!");
	Serial.flush();
}

//Выводим сообщение об окончании обновления
void ServerUpdate::update_finished()
{
	Serial.println("Update finished!");
	Serial.flush();
}

//Выводим сообщение о прогрессе обновления
void ServerUpdate::update_progress(int cur, int total) 
{
	Serial.println("Update in progress!");
	Serial.flush();
}

//Выводим сообщение об ошибке обновления
void ServerUpdate::update_error(int err) 
{
	Serial.println("Update error!");
	Serial.flush();
}

void ServerUpdate::update()
{

    WiFiClient client;

    //Запускаем коллбеки выше в зависимости от статуса
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);

    //В переменную записываем результат обновления, в который передаём переменную клиента и адрес, с которого будет происходить неспосредственная загрузка
    t_httpUpdate_return ret = ESPhttpUpdate.update(client, address);

    //Модуль свич на результат обновления
    switch (ret) {
    case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        Serial.flush();
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        Serial.flush();
        break;

    case HTTP_UPDATE_OK:

        Serial.println("HTTP_UPDATE_OK");
        Serial.flush();
        break;
    }
}