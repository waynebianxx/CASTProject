#include "stdafx.h"
#include <string.h>
#include <cmath>
#include "../include/matplotlibcpp.h"
#include "../include/PyInterface.h"

int pyinitial()//no use now
{
	PyObject *modulename, *module, *dic, *func, *args, *rel, *list;
	char *funcname1 = "sum";
	char *funcname2 = "strsplit";
	int i;
 	Py_ssize_t s;
 	/* Python解释器的初始化*/
 	Py_Initialize();
 	if (!Py_IsInitialized())
 		return -1;
 	/* 导入Python模块,并检验是否正确导入 */
 	modulename = Py_BuildValue("s", "pytest");
	module = PyImport_Import(modulename);
	if (!module)
		return -1;
	/* 获得模块中函数并检验其有效性 */
	dic = PyModule_GetDict(module);
 	if (!dic)
 		return -1;
 	/* 获得sum函数地址并验证 */
 	func = PyDict_GetItemString(dic, funcname1);
 	if (!PyCallable_Check(func))
 		return -1;
 	/* 构建列表 */
 	list = PyList_New(5);
 	//printf("使用Python中的sum函数求解下列数之和\n");
 	for (i = 0; i < 5; i++)
 	{
 		//printf("%d\t", i);
 		PyList_SetItem(list, i, Py_BuildValue("i", i));
 	}
 	//printf("\n");
 	/* 构建sum函数的参数元组*/
 	args = PyTuple_New(1);
 	PyTuple_SetItem(args, 0, list);
 	/* 调用sum函数 */
 	PyObject_CallObject(func, args);
 	/* 获得strsplit函数地址并验证*/
 	func = PyDict_GetItemString(dic, funcname2);
 	if (!PyCallable_Check(func))
 	{
 		//printf("不能找到函数 %s", funcname2);
 		return -1;
 	}
 	/* 构建strsplit函数的参数元组 */
 	args = PyTuple_New(2);
 	//printf("使用Python中的函数分割以下字符串:\n");
 	//printf("this is an example\n");
 	PyTuple_SetItem(args, 0, Py_BuildValue("s", "this is an example"));
 	PyTuple_SetItem(args, 1, Py_BuildValue("s", " "));
 	/* 调用strsplit函数并获得返回值 */
 	rel = PyObject_CallObject(func, args);
 	s = PyList_Size(rel);
 	//printf("结果如下所示:\n");
 	for (i = 0; i < s; i++)
 	{
 		//printf("%s\n", PyString_AsString(PyList_GetItem(rel, i)));
 	}
	/* 释放资源 */
 	Py_DECREF(list);
 	Py_DECREF(args);
	Py_DECREF(module);
	/* 结束Python解释器 */
	Py_Finalize();
	printf("按回车键退出程序:\n");
	getchar();
	return 0;
}

namespace plt = matplotlibcpp;
int test_Alux(string plotname, string titlename)
{
	//temp testing the math function

	// Prepare data.
	int n = 5000;
	std::vector<double> x(n), y(n), z(n), w(n, 2);
	for (int i = 0; i < n; ++i) {
		x.at(i) = i * i;
		y.at(i) = sin(2 * 3.1415 *i / 360.0);
		z.at(i) = log(i);
	}

	// Set the size of output image = 1200x780 pixels
	//plt::figure_size(1200, 780);
	// Plot line from given x and y data. Color is selected automatically.
	plt::subplot(2, 2, 1);
	plt::plot(x, y, "b--");
	plt::title("Time Counter Curve");
	// Plot a red dashed line from given x and y data.
	plt::subplot(2, 2, 2);
	plt::plot(x, w, "r--");
	plt::title("Whole second time curve");
	// Plot a line whose name will show up as "log(x)" in the legend.
	plt::subplot(2, 2, 3);
	plt::plot(x, z, "y--");
	// Set x-axis to interval [0,1000000]
	plt::xlim(0, 1000 * 1000);
	plt::title("Clock frequency curve");
	plt::show();
	return 1;
}

void draw_plot(vector<float>& x, vector<float>& y, PLOT_COLOR pltcol)
{
	string strcolor;
	switch (pltcol)
	{
	case PLOT_BLUE:
		strcolor = "b--";
		break;
	case PLOT_GREEN:
		strcolor = "g--";
		break;
	case PLOT_RED:
		strcolor = "r--";
		break;
	case PLOT_CYAN:
		strcolor = "c--";
		break;
	case PLOT_MAGENTA:
		strcolor = "m--";
		break;
	case PLOT_YELLOW:
		strcolor = "y--";
		break;
	case PLOT_BLACK:
		strcolor = "k--";
		break;
	case PLOT_WHITE:
		strcolor = "w--";
		break;
	default:
		break;
	}
	plt::plot(x, y, strcolor.c_str());
	return;
}

void draw_plot(vector<float>& x, PLOT_COLOR pltcol)
{
	string strcolor;
	switch (pltcol)
	{
	case PLOT_BLUE:
		strcolor = "b--";
		break;
	case PLOT_GREEN:
		strcolor = "g--";
		break;
	case PLOT_RED:
		strcolor = "r--";
		break;
	case PLOT_CYAN:
		strcolor = "c--";
		break;
	case PLOT_MAGENTA:
		strcolor = "m--";
		break;
	case PLOT_YELLOW:
		strcolor = "y--";
		break;
	case PLOT_BLACK:
		strcolor = "k--";
		break;
	case PLOT_WHITE:
		strcolor = "w--";
		break;
	default:
		break;
	}
	plt::plot(x, strcolor.c_str());
	return;
}

void draw_multi_plot(vector<vector<float>>& vec_multi)
{
	int pltnum = vec_multi.size();
	PLOT_COLOR curPltCl;
	for (int i = 0; i != pltnum; ++i)
	{
		curPltCl = (PLOT_COLOR)(i % 7);
		draw_plot(vec_multi[i], curPltCl);
	}
	plt::show();
}