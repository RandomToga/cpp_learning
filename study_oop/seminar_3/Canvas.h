#pragma once
#include <windows.h>
#include <vector>
#include <iostream>

using namespace std;

class shape {
public:
    virtual ~shape() = default;
    virtual void show(HDC hdc) = 0;
};

class point : public shape {
public:
    int x, y;
    COLORREF color;
    point(int x, int y, COLORREF c = RGB(255, 255, 255)) : x(x), y(y), color(c) {};
    void show(HDC hdc) override;
};

class rectangle : public shape {
    point top_left;
    point bottom_right;
    COLORREF color;
    COLORREF background_color;
    bool filled;
public:
    rectangle(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0)
        : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {};
    void show(HDC hdc) override;
};

class line : public shape {
    point start, end;
    COLORREF color;
public:
    line(int x1, int y1, int x2, int y2, COLORREF c);
    void show(HDC hdc) override;
};

class ellipse : public shape {
    point top_left, bottom_right;
    COLORREF color, background_color;
    bool filled;
public:
    ellipse(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0);
    void show(HDC hdc) override;
};

class polygon : public shape {
    std::vector<point> points;
    COLORREF color, background_color;
    bool filled;
public:
    polygon(const std::vector<point>& pts, COLORREF c, bool filled = false, COLORREF bc = 0);
    void show(HDC hdc) override;
};

class canvas {
    std::vector<shape*> figures;
    HWND hWnd;
    HDC hdc;
public:
    canvas();
    ~canvas();
    void add(shape* s);
    void clear();
    void show();
};