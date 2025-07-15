#ifndef DATA_INPUT
#define DATA_INPUT

#include <cmath>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>
#include <functional>
#include "serialib.h"

class DataInput
{
	bool continue_run = true;
	float value = 0.0;
	std::unique_ptr<std::thread> thread;
	mutable std::mutex mtx;
	serialib serial;

	void read_value(){
		for(;continue_run;){
			serial.writeChar(88);
			serial.readBytes((char*)&value,4,2000);
			std::lock_guard<std::mutex> lock(mtx);
			std::cout << value << std::endl;
		}
	}
public:
	DataInput(const DataInput&)=delete;
	DataInput(const DataInput&&)=delete;
	DataInput& operator=(const DataInput&)=delete;
	DataInput& operator=(DataInput&&)=delete;

	DataInput(){
		char err;
		do{
			err = serial.openDevice("/dev/ttyUSB0",9600);
			std::cout << "try to open the serial" << std::endl;
		}while (err!=1);

		std::cout << "sucessful to open the serial" << std::endl;

		thread.reset(new std::thread{std::bind(&DataInput::read_value,this)});
	}

	float get(){
		std::lock_guard<std::mutex> lock(mtx);
		return value;
	}

	float check() const{
		std::lock_guard<std::mutex> lock(mtx);
		return value;
	}

	~DataInput(){
		continue_run = false;
		thread->join();
	}
};

#endif
