
#
# Создает объектные файлы в src
# Кидает Main.exe в LIBS
# С помощью ссылки на Main.exe запускаем приложение 
#

all: compile link clean-obj

compile: Object.h
	g++ -I LIBS/include -c GameMain.cpp Object.cpp

#------------------ Имена -------------------------------------------------------------------
exe-name := Main # Исправить, также добавить ярлык
#--------------------------------------------------------------------------------------------------

#------------------ Пути линковки и компиляции	-------------------------------------------------------------------
exe-link := D:\WORKONIT\cpp_experience\untitled\UNTITLED\dll\GameMain
dll-link := D:\WORKONIT\cpp_experience\untitled\UNTITLED\dll\GameMain
#--------------------------------------------------------------------------------------------------

#------------------ Список объектных ------------------
obj-files := GameMain.o Object.o
#--------------------------------------------------------------------------------------------------


#------------------ Флаги и аргументы ------------------
link-settings := -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l libgcc_s_seh-1 -l libstdc++ -l libwinpthread
#--------------------------------------------------------------------------------------------------

link: 
	g++ -o $(exe-link) $(obj-files) -L LIBS/lib $(link-settings)

clean-obj:
	rm 	$(obj-files)