#include "data_buffer.h"
#include <iostream>

Buffer::Buffer()
{
	begin_time = std::chrono::system_clock::now();
	for (auto&i:x_data) i=0;
	for (auto&i:y_data) i=0;
}

void Buffer::input_data(float x,float y)
{
	auto move_front = [](std::array<float,length>& a){
		auto i1 = a.begin();
		auto i2 = i1+1;
		while (i2!=a.end()){
			*i1 = *i2;
			++i1;
			++i2;
		}
	};

	auto set_last = [](std::array<float,length>& a, float value){
		auto i = a.end();
		--i;
		*i = value;
	};

	move_front(x_data);
	set_last(x_data,x);
	move_front(y_data);
	set_last(y_data,y);

}

std::tuple<const float*,const float*,std::size_t> Buffer::get_buffer() const
{
	return std::make_tuple(x_data.data(),y_data.data(),length);
}
