#include "Desk.h"
#include <fstream>

const GLfloat deskWidth = 5.0;
const GLfloat deskLength = 5.0;
const GLfloat deskHeight = 0.25;

void Desk::addEdges(GLfloat x, GLfloat y, GLfloat w, GLfloat l) {
	// false is by x
	edges.push_back(std::move(Edge(Point(x - w / 2, y - l / 2, 0), false)));
	edges.push_back(std::move(Edge(Point(x + w / 2, y - l / 2, 0), false)));
	edges.push_back(std::move(Edge(Point(x - w / 2, y - l / 2, 0), true)));
	edges.push_back(std::move(Edge(Point(x - w / 2, y + l / 2, 0), true)));
}

Desk::Desk(int level) : rects(4), tiles(10, std::vector<Tile>(10)) {
	rects[0] = std::move(Rect(deskWidth + deskHeight, 0.0, 0.0, deskHeight * 2, 2 * deskLength, deskHeight * 4));
	rects[1] = std::move(Rect(-(deskWidth + deskHeight), 0.0, 0.0, deskHeight * 2, 2 * deskLength, deskHeight * 4));
	rects[2] = std::move(Rect(0.0, deskLength + deskHeight, 0.0, 2 * deskWidth + deskHeight * 4, deskHeight * 2, deskHeight * 4));
	rects[3] = std::move(Rect(0.0, -(deskLength + deskHeight), 0.0, 2 * deskWidth + deskHeight * 4, deskHeight * 2, deskHeight * 4));
	addEdges(0.0, 0.0, 2 * deskWidth, 2 * deskLength);
	std::ifstream infile("terrain.dat");
	std::vector<std::vector<float>> temp(11, std::vector<float>(11, 0));
	for (auto i = 0; i < 11; i++) {
		for (auto j = 0; j < 11; j++) {
			float tmp = 0;
			infile >> tmp;
			temp[i][j] = tmp;
		}
	}
	for (auto i = 0; i < 10; i++) {
		for (auto j = 0; j < 10; j++) {
			Point lt = Point(i - 5, j - 5, temp[i][j]);
			Point rt = Point(i - 4, j - 5, temp[i + 1][j]);
			Point rb = Point(i - 4, j - 4, temp[i + 1][j + 1]);
			Point lb = Point(i - 5, j - 4, temp[i][j + 1]);

			tiles[i][j] = Tile(lt, rt, rb, lb);
		}
	}
}