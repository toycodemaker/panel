#include <vector>
#include<string>
#include "imrun.h"

const char* info[2]{
	"Great I like C++ too!",
	"No you can`t like Rust!C++ is better"
};

int main(int, char**){
	std::vector<int> message;
	bool close_able = true;
	int count = 0;

	//创建一个窗口
    auto func =[&](bool* flag){
		bool f{true};
       ImGui::Begin("a simple ImGUI window",&f);
       ImGui::Text("which lauguage below you like?");
       
       if(ImGui::Button("C++")){
		   message.push_back(0);
       }
       ImGui::SameLine(0.0f,1.0f);
       if(ImGui::Button("Rust")){
		   message.push_back(1);
		   close_able = false;
       }

		//显示信息
		//从message
		for (auto i:message){
			ImGui::Text(info[i]);
		}

		

		//点了Rust之后又打算关闭窗口
		//不能关闭
		//创建一个新窗口
		if (!f){
			if (close_able) *flag = false;
			else count++;
		}
        ImGui::End();
        for (int i=0;i<count;i++){
            std::string name = "a message window";
            name += std::to_string(i+1);

            ImGui::Begin(name.c_str(),&f);
            ImGui::Text("NO!NO!NO! you can`t close it!");
            ImGui::End();
			//想关窗口
			
        }
      
    };

    ImRun imr(func);
    imr.run();
    return 0;
}
