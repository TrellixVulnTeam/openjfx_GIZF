/*
 * Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
*/

#include "config.h"

#include <WebCore/DeprecatedCSSOMPrimitiveValue.h>
#include <WebCore/DeprecatedCSSOMRect.h>
#include <WebCore/JSMainThreadExecState.h>

#include <wtf/RefPtr.h>
#include <wtf/GetPtr.h>

#include "JavaDOMUtils.h"
#include <wtf/java/JavaEnv.h>

using namespace WebCore;

extern "C" {

#define IMPL (static_cast<DeprecatedCSSOMRect*>(jlong_to_ptr(peer)))

JNIEXPORT void JNICALL Java_com_sun_webkit_dom_RectImpl_dispose(JNIEnv* env, jclass, jlong peer)
{
    IMPL->deref();
}


// Attributes
JNIEXPORT jlong JNICALL Java_com_sun_webkit_dom_RectImpl_getTopImpl(JNIEnv* env, jclass, jlong peer)
{
    WebCore::JSMainThreadNullState state;
    return JavaReturn<DeprecatedCSSOMPrimitiveValue>(env, WTF::getPtr(IMPL->top()));
}

JNIEXPORT jlong JNICALL Java_com_sun_webkit_dom_RectImpl_getRightImpl(JNIEnv* env, jclass, jlong peer)
{
    WebCore::JSMainThreadNullState state;
    return JavaReturn<DeprecatedCSSOMPrimitiveValue>(env, WTF::getPtr(IMPL->right()));
}

JNIEXPORT jlong JNICALL Java_com_sun_webkit_dom_RectImpl_getBottomImpl(JNIEnv* env, jclass, jlong peer)
{
    WebCore::JSMainThreadNullState state;
    return JavaReturn<DeprecatedCSSOMPrimitiveValue>(env, WTF::getPtr(IMPL->bottom()));
}

JNIEXPORT jlong JNICALL Java_com_sun_webkit_dom_RectImpl_getLeftImpl(JNIEnv* env, jclass, jlong peer)
{
    WebCore::JSMainThreadNullState state;
    return JavaReturn<DeprecatedCSSOMPrimitiveValue>(env, WTF::getPtr(IMPL->left()));
}

}
