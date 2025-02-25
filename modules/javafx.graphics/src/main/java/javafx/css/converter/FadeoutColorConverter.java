/*
 * Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
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

package javafx.css.converter;

import javafx.css.Size;
import javafx.css.StyleConverter;
import javafx.css.ParsedValue;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

/**
 * Fade out (transparentize) a Color from a Color and a transparency value
 */
public final class FadeoutColorConverter extends StyleConverter<ParsedValue[], Color> {

    // lazy, thread-safe instatiation
    private static class Holder {
        static final FadeoutColorConverter INSTANCE = new FadeoutColorConverter();
    }

    public static FadeoutColorConverter getInstance() {
        return Holder.INSTANCE;
    }

    private FadeoutColorConverter() {
        super();
    }

    @Override
    public Color convert(ParsedValue<ParsedValue[], Color> value, Font font) {
        ParsedValue[] values = value.getValue();
        final Color color = (Color) values[0].convert(font);
        final Size transparency = (Size) values[1].convert(font);
        return new Color(color.getRed(), color.getBlue(), color.getGreen(),
                color.getOpacity() * (1 - transparency.pixels(font)));
    }

    @Override
    public String toString() {
        return "FadeoutColorConverter";
    }
}
