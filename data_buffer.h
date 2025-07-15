//用来将收到的数据生成一个流畅的buffer
#ifndef DATA_BUFFER
#define DATA_BUFFER

#include <tuple>
#include <chrono>
#include <array>
#include <iostream>

class Buffer
{
public:
	static constexpr int length = 1024;

	Buffer();
	void input_data(float, float);
	std::tuple<const float*,const float*,std::size_t> get_buffer() const;
private:
	std::chrono::time_point<std::chrono::system_clock> begin_time;
	std::array<float,length> x_data;
	std::array<float,length> y_data;
};

struct ValueIn
{
	float U,K,E,l;
};

class Caculate
{
public:
	virtual std::tuple<float,float> input_value(float value)=0;
protected:
	float get_time(){
		static std::chrono::time_point<std::chrono::system_clock> begin_time = 
			std::chrono::system_clock::now();
		std::chrono::duration<float> d = std::chrono::system_clock::now() - begin_time;
		return d.count();
	}
};

class ShowWithTime:public Caculate
{
public:
	std::tuple<float,float> input_value(float value)override{
		return std::make_tuple(get_time(),value);
	}
};

class ShowEWithTime:public Caculate
{
public:
	ShowEWithTime(ValueIn values_){
		values = values_;
	}

	std::tuple<float,float> input_value(float value)override{
		return std::make_tuple(get_time(), value/values.U/values.K);
	}
private:
	ValueIn values;
};

class DerformationWithX:public Caculate
{
public:
	 DerformationWithX(ValueIn values_, float* voltage_){
		values = values_;
		voltage = voltage_;
	}

	 std::tuple<float,float> input_value(float value)override{
		 return std::make_tuple(value,*voltage/values.U/values.K*value);
	}

private:
	ValueIn values;
	float* voltage;
};

#endif
