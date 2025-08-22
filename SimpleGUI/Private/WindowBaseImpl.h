#pragma once
#include <include/core/SkImageInfo.h>
#include <include/core/SkSurface.h>
#include <include/core/SkColorSpace.h>

class Element;
class WindowBaseImpl
{
public:
	WindowBaseImpl(const int& w, const int& h);
	~WindowBaseImpl();
	void resize(const int& w, const int& h);
	void paintElement(Element* ele);
	const SkPixmap getPix();
private:
	sk_sp<SkSurface> surface;
};

