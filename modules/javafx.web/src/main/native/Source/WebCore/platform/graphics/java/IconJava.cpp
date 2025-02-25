/*
 * Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
 */
#include "config.h"

#include "GraphicsContext.h"
#include "GraphicsContextJava.h"
#include "Icon.h"
#include "IntRect.h"
#include <wtf/java/JavaEnv.h>
#include <wtf/java/JavaRef.h>
#include "NotImplemented.h"

#include <wtf/RefPtr.h>
#include <wtf/PassRefPtr.h>
#include <wtf/text/WTFString.h>

#include "PlatformContextJava.h"
#include "com_sun_webkit_graphics_GraphicsDecoder.h"


using namespace WebCore;

namespace WebCore {

Icon::Icon(const JLObject &jicon)
    : m_jicon(RQRef::create(jicon))
{
}

Icon::~Icon()
{
}

RefPtr<Icon> Icon::createIconForFiles(const Vector<String>&)
{
    notImplemented();
    return nullptr;
}

void Icon::paint(GraphicsContext& gc, const FloatRect& rect)
{
    gc.platformContext()->rq().freeSpace(16)
    << (jint)com_sun_webkit_graphics_GraphicsDecoder_DRAWICON
    << *m_jicon << (jint)rect.x() <<  (jint)rect.y();
}

} // namespace WebCore
