#include "WindowBaseImpl.h"


WindowBaseImpl::WindowBaseImpl(const int& w, const int& h)
{
    SkImageInfo info = SkImageInfo::MakeN32Premul(w, h);
    surface = SkSurfaces::Raster(info);
}

WindowBaseImpl::~WindowBaseImpl()
{
}
void WindowBaseImpl::resize(const int& w, const int& h)
{
    surface.reset(nullptr);
    SkImageInfo info = SkImageInfo::MakeN32Premul(w, h);
    surface = SkSurfaces::Raster(info);
}

const SkPixmap WindowBaseImpl::getPix()
{
    SkPixmap pix;
    surface->peekPixels(&pix);
    return pix;
}
