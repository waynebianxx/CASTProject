#pragma once
#include <vector>
#include <string>
using namespace std;
typedef enum {
	PLOT_BLUE = 0,
	PLOT_GREEN = 1,
	PLOT_RED = 2,
	PLOT_CYAN = 3,
	PLOT_MAGENTA = 4,
	PLOT_YELLOW = 5,
	PLOT_BLACK = 6,
	PLOT_WHITE = 7
}PLOT_COLOR;
int test_Alux(string plotname, string titlename);
void draw_plot(vector<float>& x, vector<float>& y, PLOT_COLOR pltcol=PLOT_BLUE);
void draw_plot(vector<float>& x, PLOT_COLOR pltcol = PLOT_BLUE);
void draw_multi_plot(vector<vector<float>>& vec_multi);