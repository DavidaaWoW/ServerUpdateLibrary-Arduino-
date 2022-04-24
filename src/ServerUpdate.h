#ifndef SERVERUPDATE_H
#define SERVERUPDATE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ctime>

class ServerUpdate
{
public:
	ServerUpdate(String, String, double);
	~ServerUpdate();
	bool setType(String);
	bool setAddress(String);
	bool setTime(double);
	String getType();
	String getAddress();
	double getTime();
	void update();


private:
	String type;
	double time;
	String address;
	static void update_started();
	static void update_finished();
	static void update_progress(int, int);
	static void update_error(int);

};

#endif