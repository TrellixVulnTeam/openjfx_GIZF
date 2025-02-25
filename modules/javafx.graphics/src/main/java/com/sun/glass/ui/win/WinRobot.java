/*
 * Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
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
package com.sun.glass.ui.win;

import javafx.scene.input.KeyCode;
import javafx.scene.input.MouseButton;
import javafx.scene.paint.Color;
import javafx.scene.robot.Robot;

import com.sun.glass.ui.Application;
import com.sun.glass.ui.GlassRobot;

/**
 * MS Windows platform implementation class for Robot.
 */
final class WinRobot extends Robot {

    @Override protected void create() {
        // no-op
    }
    @Override protected void destroy() {
        // no-op
    }

    native protected void _keyPress(int code);
    @Override public void keyPress(KeyCode code) {
        Application.checkEventThread();
        _keyPress(code.getCode());
    }

    native protected void _keyRelease(int code);
    @Override public void keyRelease(KeyCode code) {
        Application.checkEventThread();
        _keyRelease(code.getCode());
    }


    native protected void _mouseMove(int x, int y);
    @Override public void mouseMove(int x, int y) {
        Application.checkEventThread();
        _mouseMove(x, y);
    }

    native protected void _mousePress(int buttons);
    @Override public void mousePress(MouseButton button) {
        Application.checkEventThread();
        _mousePress(GlassRobot.convertToRobotMouseButton(button));
    }

    @Override
    public void mousePress(MouseButton... buttons) {
        Application.checkEventThread();
        _mousePress(GlassRobot.convertToRobotMouseButton(buttons));
    }

    native protected void _mouseRelease(int buttons);
    @Override public void mouseRelease(MouseButton button) {
        Application.checkEventThread();
        _mouseRelease(GlassRobot.convertToRobotMouseButton(button));
    }

    @Override
    public void mouseRelease(MouseButton... buttons) {
        Application.checkEventThread();
        _mouseRelease(GlassRobot.convertToRobotMouseButton(buttons));
    }

    native protected void _mouseWheel(int wheelAmt);
    @Override protected void mouseWheel(int wheelAmt) {
        Application.checkEventThread();
        _mouseWheel(wheelAmt);
    }

    native protected int _getMouseX();
    @Override public int getMouseX() {
        Application.checkEventThread();
        return _getMouseX();
    }

    native protected int _getMouseY();
    @Override public int getMouseY() {
        Application.checkEventThread();
        return _getMouseY();
    }

    native protected int _getPixelColor(int x, int y);
    @Override public Color getPixelColor(int x, int y) {
        Application.checkEventThread();
        return GlassRobot.convertFromIntArgb(_getPixelColor(x, y));
    }

    @Override native protected void getScreenCapture(int x, int y, int width, int height, int[] data);
}
