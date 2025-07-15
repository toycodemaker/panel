#ifndef IMRUN_H_
#define IMRUM_H_

#include "imgui.h"
#include <functional>

//简单封装一下imgui
//方便使用
//掩盖SDL后端的东西
//imgui永远的神

class ImRun final
{
public:
    using RunFunc = std::function<void(bool *)>;
	using InitFunc = std::function<void(void)>;
private:
    RunFunc func;
	InitFunc ifunc;
	InitFunc dfunc;
    bool flag{true};

public:
    ImRun(const RunFunc &fnc,const InitFunc& func=[]{},const InitFunc& dfunc=[]{});
    int run();
};

#endif
