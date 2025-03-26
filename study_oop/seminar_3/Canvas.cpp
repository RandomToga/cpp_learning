#include "Canvas.h"
#include <windows.h>
#include <iostream>


// Реализация point
void point::show(HDC hdc) {
    SetPixel(hdc, x, y, color);
}

// Реализация rectangle
void rectangle::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    SetDCBrushColor(hdc, background_color);
    SelectObject(hdc, filled ? GetStockObject(DC_BRUSH) : GetStockObject(NULL_BRUSH));
    Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

// Line implementation
line::line(int x1, int y1, int x2, int y2, COLORREF c)
    : start(x1, y1), end(x2, y2), color(c) {
}

void line::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    MoveToEx(hdc, start.x, start.y, NULL);
    LineTo(hdc, end.x, end.y);
}

// Ellipse implementation
ellipse::ellipse(int x1, int y1, int x2, int y2, COLORREF c, bool filled, COLORREF bc)
    : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {
}

void ellipse::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    SetDCBrushColor(hdc, background_color);
    SelectObject(hdc, filled ? GetStockObject(DC_BRUSH) : GetStockObject(NULL_BRUSH));
    Ellipse(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}


// Polygon implementation
polygon::polygon(const std::vector<point>& pts, COLORREF c, bool filled, COLORREF bc)
    : points(pts), color(c), background_color(bc), filled(filled) {
}

void polygon::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    SetDCBrushColor(hdc, background_color);
    SelectObject(hdc, filled ? GetStockObject(DC_BRUSH) : GetStockObject(NULL_BRUSH));

    std::vector<POINT> win_points;
    for (const auto& p : points) {
        win_points.push_back({ p.x, p.y });
    }
    Polygon(hdc, win_points.data(), win_points.size());
}

// Реализация canvas
canvas::canvas() {
    hWnd = GetConsoleWindow();
    hdc = GetDC(hWnd);
}

canvas::~canvas() {
    ReleaseDC(hWnd, hdc);
    for (auto figure : figures) {
        delete figure;
    }
}

void canvas::add(shape* s) {
    if (s) figures.push_back(s);
}

void canvas::clear() {
    for (auto figure : figures) {
        delete figure;
    }
    figures.clear();
}

void canvas::show() {
    for (auto figure : figures) {
        figure->show(hdc);
    }
}