#include "imrun.h"
#include "implot.h"
#include "data_input.h"
#include "data_buffer.h"
#include "plane.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

template <typename T,typename ...T2>
Plane generate_plane(Plane::PlaneInfo info,T2 ...values)
{
	return Plane{info,std::make_unique<T>(std::forward<T2>(values)...)};
}

ValueIn get_values()
{
	auto input = [](const char* msg){
		std::cout << "please enter the value of ";
		std::cout << msg << ":";
		float value;
		std::cin >> value;
		return value;
	};
	ValueIn values;
	values.l = input("l");
	values.E = input("E");
	values.K = input("K");
	values.U = input("U");

	return values;
}

void handle_derformation(Plane& der){
	float x=0.0;
	for (int i=0;i<Buffer::length;i++){
		der.input_value(x);
		x += 0.1;
	}
}

int main(int, char**){
	auto values = get_values();
	DataInput input;
	auto plane = generate_plane<ShowWithTime>({"voltage","t/s","U/v"});
	float voltage=0;
	auto derformation = generate_plane<DerformationWithX>(
			{"deformation","x","y"},values,&voltage);
	auto e_plane = generate_plane<ShowEWithTime>({"E","t/s","y"},values);
	PlaneManage manager({plane,derformation,e_plane});

	bool show_plane{false};
    auto func =[&](bool* flag){
		ImGui::Begin("Hei You",flag);
		ImGui::Checkbox("If Show the select window?",&show_plane);

		voltage = input.get();
		plane.input_value(voltage);
		e_plane.input_value(voltage);
		handle_derformation(derformation);
		plane.show();
		derformation.show();
		e_plane.show();

		ImGui::Text("Voltage: %f",voltage);
		ImGui::Text("ImGui version:%s", ImGui::GetVersion());
		ImGui::End();

		manager.manage_if_show(show_plane);

    };

	auto init_plot = []{
		ImPlot::CreateContext();
		ImPlotInputMap& input_map = ImPlot::GetInputMap();
		input_map.ZoomRate = 0.1f;
	};

	auto out_plot = []{
		ImPlot::DestroyContext();
	};
    ImRun imr(func,init_plot,out_plot);
    imr.run();
}
