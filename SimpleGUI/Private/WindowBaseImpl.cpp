#include <include/core/SkCanvas.h>
#include <include/encode/SkPngEncoder.h>
#include <include/core/SkStream.h>

#include "../Element.h"
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

void WindowBaseImpl::paintElement(Element* ele)
{
    auto canvas = surface->getCanvas(); //todo 不要每次重绘都全量绘制
    canvas->clear(0x000000);
    ele->paint(canvas);

    //SkPixmap pixmap;
    //surface->peekPixels(&pixmap);
    //SkFILEWStream stream("allen1.png");
    //SkPngEncoder::Encode(&stream, pixmap, {});
    //stream.flush();
}

const SkPixmap WindowBaseImpl::getPix()
{
    SkPixmap pix;
    surface->peekPixels(&pix);
    return pix;
}
