#include "stdafx.h"
#include "../include/matplotlibcpp.h"
#include "../include/PyInterface.h"

//#include <Python.h>
//#include "../include/PyInterface.h"
//
//int pyinitial()
//{
//	PyObject *modulename, *module, *dic, *func, *args, *rel, *list;
//	char *funcname1 = "sum";
//	//char *funcname2 = "strsplit";
//	int i;
// 	Py_ssize_t s;
// 	/* Python�������ĳ�ʼ��*/
// 	Py_Initialize();
// 	if (!Py_IsInitialized())
// 		return -1;
// 	/* ����Pythonģ��,�������Ƿ���ȷ���� */
// 	modulename = Py_BuildValue("s", "pytest");
//	module = PyImport_Import(modulename);
//	if (!module)
//		return -1;
	/* ���ģ���к�������������Ч�� */
//	dic = PyModule_GetDict(module);
// 	if (!dic)
// 		return -1;
// 	/* ���sum������ַ����֤ */
// 	func = PyDict_GetItemString(dic, funcname1);
// 	if (!PyCallable_Check(func))
// 		return -1;
// 	/* �����б� */
// 	list = PyList_New(5);
// 	//printf("ʹ��Python�е�sum�������������֮��\n");
// 	for (i = 0; i < 5; i++)
// 	{
// 		//printf("%d\t", i);
// 		PyList_SetItem(list, i, Py_BuildValue("i", i));
// 	}
// 	//printf("\n");
// 	/* ����sum�����Ĳ���Ԫ��*/
// 	args = PyTuple_New(1);
// 	PyTuple_SetItem(args, 0, list);
// 	/* ����sum���� */
// 	PyObject_CallObject(func, args);
// 	/* ���strsplit������ַ����֤*/
// 	func = PyDict_GetItemString(dic, funcname2);
// 	if (!PyCallable_Check(func))
// 	{
// 		//printf("�����ҵ����� %s", funcname2);
// 		return -1;
// 	}
// 	/* ����strsplit�����Ĳ���Ԫ�� */
// 	args = PyTuple_New(2);
// 	//printf("ʹ��Python�еĺ����ָ������ַ���:\n");
// 	//printf("this is an example\n");
// 	PyTuple_SetItem(args, 0, Py_BuildValue("s", "this is an example"));
// 	PyTuple_SetItem(args, 1, Py_BuildValue("s", " "));
// 	/* ����strsplit��������÷���ֵ */
// 	rel = PyObject_CallObject(func, args);
// 	s = PyList_Size(rel);
// 	//printf("���������ʾ:\n");
// 	for (i = 0; i < s; i++)
// 	{
// 		//printf("%s\n", PyString_AsString(PyList_GetItem(rel, i)));
// 	}
	/* �ͷ���Դ */
// 	Py_DECREF(list);
// 	Py_DECREF(args);
//	Py_DECREF(module);
	/* ����Python������ */
//	Py_Finalize();
	//printf("���س����˳�����:\n");
//	getchar();
//	return 0;
//}

namespace plt = matplotlibcpp;
int test_base()
{
	plt::plot({ 1,3,2,4 });
	plt::show();
	return 1;
}