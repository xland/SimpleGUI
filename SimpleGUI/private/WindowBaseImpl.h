#pragma once
#include <include/core/SkImageInfo.h>
#include <include/core/SkSurface.h>
#include <include/core/SkColorSpace.h>
class WindowBaseImpl
{
public:
	WindowBaseImpl(const int& w, const int& h);
	~WindowBaseImpl();
	void resize(const int& w, const int& h);
private:
	sk_sp<SkSurface> surface;
};

