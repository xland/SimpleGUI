#pragma once
class Size
{
public:
	Size() = delete;
	Size(const int& w = 0, const int& h = 0);
	~Size();
public:
	int w, h;
private:
};

