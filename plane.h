#ifndef PLANE_H_
#define PLANE_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "implot.h"
#include "data_input.h"
#include "data_buffer.h"
class PlanePrinter { public: struct Info{
		std::string name{"no name"};
		std::string x_name{"no name"};
		std::string y_name{"no name"};
	};

	PlanePrinter(const Info&plane_info_,const Buffer& buffer_):buffer(buffer_)
	{
		plane_info = plane_info_;
	}

	void draw(){
		auto[x_data,y_data,len] = buffer.get_buffer();
		if (if_show && ImPlot::BeginPlot(plane_info.name.c_str())) {
			ImPlot::SetupAxes(plane_info.x_name.c_str(),plane_info.y_name.c_str());
			ImPlot::PlotLine(plane_info.name.c_str(),x_data,y_data, len);
			ImPlot::EndPlot();
		}
	}

	PlanePrinter(const PlanePrinter&)=delete;
	PlanePrinter(PlanePrinter&&)=delete;
	PlanePrinter& operator=(const PlanePrinter&)=delete;
	PlanePrinter& operator=(PlanePrinter&&)=delete;

	friend class PlaneManage;
private:
	Info plane_info;
	const Buffer& buffer;
	bool if_show{true};
};

class Plane
{
public:
	using PlaneInfo  = PlanePrinter::Info;
	Plane(PlanePrinter::Info info, std::unique_ptr<Caculate> caculator_):caculator(std::move(caculator_)),
	plane_printer(info,buffer){plane_info = info;}

	void input_value(float value){
		auto [x,y] = caculator->input_value(value);
		buffer.input_data(x,y);
	}

	void show(){
		plane_printer.draw();
	}

	std::string get_name(){
		return plane_info.name;
	}

	Plane(const Plane&)=delete;
	Plane(Plane&&)=delete;
	Plane& operator=(const Plane&)=delete;
	Plane& operator=(Plane&&)=delete;

	friend class PlaneManage;
private:
	PlaneInfo plane_info;
	std::unique_ptr<Caculate> caculator;
	Buffer buffer;
	PlanePrinter plane_printer;
	float value_now;
};

//这个将会生成一个图形界面来管理是否显示Plane
//会持有glane的指针但是没有所有权
class PlaneManage
{
public:
	struct Plane{
		std::string name;
		PlanePrinter* plane;

		Plane(::Plane& plane_):name(plane_.get_name()),plane(&plane_.plane_printer){}
	};

	PlaneManage(std::vector<Plane> planes_):planes(planes_){}
	void manage_if_show(bool& if_show){ 
		if (if_show){ ImGui::Begin("check which plane should display",&if_show);
			for (auto& i:planes){
				ImGui::Checkbox(i.name.c_str(),&i.plane->if_show);
			}
			ImGui::End();
		}
	}

	PlaneManage(const PlaneManage&)=delete;
	PlaneManage(PlaneManage&&)=delete;
	PlaneManage& operator=(const PlaneManage&)=delete;
	PlaneManage& operator=(PlaneManage&&)=delete;
private:
	std::vector<Plane> planes;
};

#endif
