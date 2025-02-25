/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
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

#pragma once

#include "MarkedBlock.h"
#include "MarkedSpace.h"
#include <wtf/text/CString.h>

namespace JSC {

// The idea of subspaces is that you can provide some custom behavior for your objects if you
// allocate them from a custom Subspace in which you override some of the virtual methods. This
// class is the baseclass of Subspaces and it provides a reasonable default implementation, where
// sweeping assumes immortal structure. The common ways of overriding this are:
//
// - Provide customized destructor behavior. You can change how the destructor is called. You can
//   also specialize the destructor call in the loop.
//
// - Use the Subspace as a quick way to iterate all of the objects in that subspace.
class Subspace {
    WTF_MAKE_NONCOPYABLE(Subspace);
    WTF_MAKE_FAST_ALLOCATED;
public:
    JS_EXPORT_PRIVATE Subspace(CString name, Heap&, AllocatorAttributes);
    JS_EXPORT_PRIVATE virtual ~Subspace();

    const char *name() const { return m_name.data(); }
    MarkedSpace& space() const { return m_space; }

    const AllocatorAttributes& attributes() const { return m_attributes; }

    // The purpose of overriding this is to specialize the sweep for your destructors. This won't
    // be called for no-destructor blocks. This must call MarkedBlock::finishSweepKnowingSubspace.
    virtual FreeList finishSweep(MarkedBlock::Handle&, MarkedBlock::Handle::SweepMode);

    // These get called for large objects.
    virtual void destroy(VM&, JSCell*);

    MarkedAllocator* tryAllocatorFor(size_t);
    MarkedAllocator* allocatorFor(size_t);

    JS_EXPORT_PRIVATE void* allocate(size_t);
    JS_EXPORT_PRIVATE void* allocate(GCDeferralContext*, size_t);

    JS_EXPORT_PRIVATE void* tryAllocate(size_t);
    JS_EXPORT_PRIVATE void* tryAllocate(GCDeferralContext*, size_t);

    template<typename Func>
    void forEachMarkedBlock(const Func&);

    template<typename Func>
    void forEachNotEmptyMarkedBlock(const Func&);

    template<typename Func>
    void forEachLargeAllocation(const Func&);

    template<typename Func>
    void forEachMarkedCell(const Func&);

    static ptrdiff_t offsetOfAllocatorForSizeStep() { return OBJECT_OFFSETOF(Subspace, m_allocatorForSizeStep); }

    MarkedAllocator** allocatorForSizeStep() { return &m_allocatorForSizeStep[0]; }

private:
    MarkedAllocator* allocatorForSlow(size_t);

    // These slow paths are concerned with large allocations and allocator creation.
    void* allocateSlow(GCDeferralContext*, size_t);
    void* tryAllocateSlow(GCDeferralContext*, size_t);

    MarkedSpace& m_space;

    CString m_name;
    AllocatorAttributes m_attributes;

    std::array<MarkedAllocator*, MarkedSpace::numSizeClasses> m_allocatorForSizeStep;
    MarkedAllocator* m_firstAllocator { nullptr };
    SentinelLinkedList<LargeAllocation, BasicRawSentinelNode<LargeAllocation>> m_largeAllocations;
};

ALWAYS_INLINE MarkedAllocator* Subspace::tryAllocatorFor(size_t size)
{
    if (size <= MarkedSpace::largeCutoff)
        return m_allocatorForSizeStep[MarkedSpace::sizeClassToIndex(size)];
    return nullptr;
}

ALWAYS_INLINE MarkedAllocator* Subspace::allocatorFor(size_t size)
{
    if (size <= MarkedSpace::largeCutoff) {
        if (MarkedAllocator* result = m_allocatorForSizeStep[MarkedSpace::sizeClassToIndex(size)])
            return result;
        return allocatorForSlow(size);
    }
    return nullptr;
}

} // namespace JSC

