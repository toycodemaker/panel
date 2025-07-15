#鸡刀的makefile
RUN = r
ORD = -Wall -Wformat -O3 -std=c++20 -fmodules-ts -g
LINK = -Wall -Wformat -lSDL2 -lGL
OBJ = main.o imrun.o imgui.o imgui_widgets.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_impl_sdl2.o imgui_impl_opengl2.o implot.o implot_items.o implot_demo.o data_buffer.o serialib.o
$(RUN):$(OBJ)
	g++ $(OBJ) -o $(RUN) $(LINK)
main.o:main.cpp
	g++ main.cpp -c $(ORD)
imrun.o:imrun.cpp
	g++ imrun.cpp -c $(ORD)
imgui.o:imgui.cpp
	g++ imgui.cpp -c $(ORD)
imgui_widgets.o:imgui_widgets.cpp
	g++ imgui_widgets.cpp -c $(ORD)
imgui_demo.o:imgui_demo.cpp
	g++ imgui_demo.cpp -c $(ORD)
imgui_draw.o:imgui_draw.cpp
	g++ imgui_draw.cpp -c $(ORD)
imgui_tables.o:imgui_tables.cpp
	g++ imgui_tables.cpp -c $(ORD)
imgui_impl_sdl2.o:imgui_impl_sdl2.cpp
	g++ imgui_impl_sdl2.cpp -c $(ORD)
imgui_impl_opengl2.o:imgui_impl_opengl2.cpp
	g++ imgui_impl_opengl2.cpp -c $(ORD)
implot.o:implot.cpp
	g++ implot.cpp -c $(ORD)
implot_items.o:implot_items.cpp
	g++ implot_items.cpp -c $(ORD)
implot_demo.o:implot.cpp
	g++ implot_demo.cpp -c $(ORD)
data_buffer.o:data_buffer.cpp
	g++ data_buffer.cpp -c $(ORD)
serialib.o:serialib.cpp
	g++ serialib.cpp -c $(ORD)
