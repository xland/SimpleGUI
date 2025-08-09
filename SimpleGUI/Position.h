#pragma once
class Position
{
public:
	Position() = delete;
	Position(const int& x = 0,const int& y = 0);
	~Position();
public:
	int x, y;
private:
};

