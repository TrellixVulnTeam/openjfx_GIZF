/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ProfilerJettisonReason.h"

#include <wtf/PrintStream.h>

namespace WTF {

using namespace JSC::Profiler;

void printInternal(PrintStream& out, JettisonReason reason)
{
    switch (reason) {
    case NotJettisoned:
        out.print("NotJettisoned");
        return;
    case JettisonDueToWeakReference:
        out.print("WeakReference");
        return;
    case JettisonDueToDebuggerBreakpoint:
        out.print("DebuggerBreakpoint");
        return;
    case JettisonDueToDebuggerStepping:
        out.print("DebuggerStepping");
        return;
    case JettisonDueToBaselineLoopReoptimizationTrigger:
        out.print("BaselineLoopReoptimizationTrigger");
        return;
    case JettisonDueToBaselineLoopReoptimizationTriggerOnOSREntryFail:
        out.print("BaselineLoopReoptimizationTriggerOnOSREntryFail");
        return;
    case JettisonDueToOSRExit:
        out.print("OSRExit");
        return;
    case JettisonDueToProfiledWatchpoint:
        out.print("ProfiledWatchpoint");
        return;
    case JettisonDueToUnprofiledWatchpoint:
        out.print("UnprofiledWatchpoint");
        return;
    case JettisonDueToOldAge:
        out.print("JettisonDueToOldAge");
        return;
    }
    RELEASE_ASSERT_NOT_REACHED();
}

} // namespace WTF

