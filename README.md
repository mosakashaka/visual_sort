# 排序算法的练习

图像化展示排序过程，图形库用的[SDL](https://www.libsdl.org/)。

文字显示使用的[SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/)。

需要预先下载安装，编译的时候依赖头文件和库文件。

## 使用

通过VSCODE编译运行，编译器用的Mingw64。配置需要相应修改

1. c_cpp_properties.json：`includePath`、`compilerPath`
2. launch.json: `miDebuggerPath`
3. tasks.json: `command`、`args`

在vscode命令行（F1）中，选择Task:Run build task，编译生成的可执行程序在main.exe下。

## 效果

![截图](https://raw.githubusercontent.com/mosakashaka/visual_sort/master/sample.gif)