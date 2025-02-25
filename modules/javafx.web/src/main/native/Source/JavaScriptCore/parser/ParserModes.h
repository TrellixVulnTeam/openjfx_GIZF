/*
 * Copyright (C) 2012-2013, 2015-2016 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "ConstructAbility.h"
#include "Identifier.h"

namespace JSC {

enum class JSParserStrictMode { NotStrict, Strict };
enum class JSParserBuiltinMode { NotBuiltin, Builtin };
enum class JSParserScriptMode { Classic, Module };
enum class JSParserCodeType { Program, Function, Module };

enum class ConstructorKind { None, Base, Extends };
enum class SuperBinding { Needed, NotNeeded };

enum DebuggerMode { DebuggerOff, DebuggerOn };

enum class FunctionMode { FunctionExpression, FunctionDeclaration, MethodDefinition };

enum class SourceParseMode : uint16_t {
    NormalFunctionMode            = 0b0000000000000001,
    GeneratorBodyMode             = 0b0000000000000010,
    GeneratorWrapperFunctionMode  = 0b0000000000000100,
    GetterMode                    = 0b0000000000001000,
    SetterMode                    = 0b0000000000010000,
    MethodMode                    = 0b0000000000100000,
    ArrowFunctionMode             = 0b0000000001000000,
    AsyncFunctionBodyMode         = 0b0000000010000000,
    AsyncArrowFunctionBodyMode    = 0b0000000100000000,
    AsyncFunctionMode             = 0b0000001000000000,
    AsyncMethodMode               = 0b0000010000000000,
    AsyncArrowFunctionMode        = 0b0000100000000000,
    ProgramMode                   = 0b0001000000000000,
    ModuleAnalyzeMode             = 0b0010000000000000,
    ModuleEvaluateMode            = 0b0100000000000000,
};

class SourceParseModeSet {
public:
    template<typename... Modes>
    SourceParseModeSet(Modes... args)
        : m_mask(mergeSourceParseModes(args...))
    {
    }

    ALWAYS_INLINE bool contains(SourceParseMode mode)
    {
        return static_cast<unsigned>(mode) & m_mask;
    }

private:
    ALWAYS_INLINE static unsigned mergeSourceParseModes(SourceParseMode mode)
    {
        return static_cast<unsigned>(mode);
    }

    template<typename... Rest>
    ALWAYS_INLINE static unsigned mergeSourceParseModes(SourceParseMode mode, Rest... rest)
    {
        return static_cast<unsigned>(mode) | mergeSourceParseModes(rest...);
    }

    const unsigned m_mask;
};

ALWAYS_INLINE bool isFunctionParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::NormalFunctionMode,
        SourceParseMode::GeneratorBodyMode,
        SourceParseMode::GeneratorWrapperFunctionMode,
        SourceParseMode::GetterMode,
        SourceParseMode::SetterMode,
        SourceParseMode::MethodMode,
        SourceParseMode::ArrowFunctionMode,
        SourceParseMode::AsyncFunctionBodyMode,
        SourceParseMode::AsyncFunctionMode,
        SourceParseMode::AsyncMethodMode,
        SourceParseMode::AsyncArrowFunctionMode,
        SourceParseMode::AsyncArrowFunctionBodyMode).contains(parseMode);
}

ALWAYS_INLINE bool isAsyncFunctionParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::AsyncFunctionBodyMode,
        SourceParseMode::AsyncFunctionMode,
        SourceParseMode::AsyncMethodMode,
        SourceParseMode::AsyncArrowFunctionMode,
        SourceParseMode::AsyncArrowFunctionBodyMode).contains(parseMode);
}

ALWAYS_INLINE bool isAsyncArrowFunctionParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::AsyncArrowFunctionMode,
        SourceParseMode::AsyncArrowFunctionBodyMode).contains(parseMode);
}

ALWAYS_INLINE bool isAsyncFunctionWrapperParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::AsyncArrowFunctionMode,
        SourceParseMode::AsyncFunctionMode,
        SourceParseMode::AsyncMethodMode).contains(parseMode);
}

ALWAYS_INLINE bool isAsyncFunctionBodyParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::AsyncFunctionBodyMode,
        SourceParseMode::AsyncArrowFunctionBodyMode).contains(parseMode);
}

ALWAYS_INLINE bool isMethodParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        // FIXME: GeneratorWrapperFunctionMode is not guaranteed to be a method.
        SourceParseMode::GeneratorWrapperFunctionMode,
        SourceParseMode::GetterMode,
        SourceParseMode::SetterMode,
        SourceParseMode::MethodMode,
        SourceParseMode::AsyncMethodMode).contains(parseMode);
}

ALWAYS_INLINE bool isGeneratorOrAsyncFunctionBodyParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::GeneratorBodyMode,
        SourceParseMode::AsyncFunctionBodyMode,
        SourceParseMode::AsyncArrowFunctionBodyMode).contains(parseMode);
}

ALWAYS_INLINE bool isGeneratorOrAsyncFunctionWrapperParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::GeneratorWrapperFunctionMode,
        SourceParseMode::AsyncFunctionMode,
        SourceParseMode::AsyncArrowFunctionMode,
        SourceParseMode::AsyncMethodMode).contains(parseMode);
}

ALWAYS_INLINE bool isArrowFunctionParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::ArrowFunctionMode,
        SourceParseMode::AsyncArrowFunctionMode,
        SourceParseMode::AsyncArrowFunctionBodyMode).contains(parseMode);
}


ALWAYS_INLINE bool isModuleParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(
        SourceParseMode::ModuleAnalyzeMode,
        SourceParseMode::ModuleEvaluateMode).contains(parseMode);
}

ALWAYS_INLINE bool isProgramParseMode(SourceParseMode parseMode)
{
    return SourceParseModeSet(SourceParseMode::ProgramMode).contains(parseMode);
}

ALWAYS_INLINE ConstructAbility constructAbilityForParseMode(SourceParseMode parseMode)
{
    if (parseMode == SourceParseMode::NormalFunctionMode)
        return ConstructAbility::CanConstruct;

    return ConstructAbility::CannotConstruct;
}

inline bool functionNameIsInScope(const Identifier& name, FunctionMode functionMode)
{
    if (name.isNull())
        return false;

    if (functionMode != FunctionMode::FunctionExpression)
        return false;

    return true;
}

inline bool functionNameScopeIsDynamic(bool usesEval, bool isStrictMode)
{
    // If non-strict eval is in play, a function gets a separate object in the scope chain for its name.
    // This enables eval to declare and then delete a name that shadows the function's name.

    if (!usesEval)
        return false;

    if (isStrictMode)
        return false;

    return true;
}

typedef uint16_t CodeFeatures;

const CodeFeatures NoFeatures =                       0;
const CodeFeatures EvalFeature =                 1 << 0;
const CodeFeatures ArgumentsFeature =            1 << 1;
const CodeFeatures WithFeature =                 1 << 2;
const CodeFeatures ThisFeature =                 1 << 3;
const CodeFeatures StrictModeFeature =           1 << 4;
const CodeFeatures ShadowsArgumentsFeature =     1 << 5;
const CodeFeatures ArrowFunctionFeature =        1 << 6;
const CodeFeatures ArrowFunctionContextFeature = 1 << 7;
const CodeFeatures SuperCallFeature =            1 << 8;
const CodeFeatures SuperPropertyFeature =        1 << 9;
const CodeFeatures NewTargetFeature =            1 << 10;

const CodeFeatures AllFeatures = EvalFeature | ArgumentsFeature | WithFeature | ThisFeature | StrictModeFeature | ShadowsArgumentsFeature | ArrowFunctionFeature | ArrowFunctionContextFeature |
    SuperCallFeature | SuperPropertyFeature | NewTargetFeature;

typedef uint8_t InnerArrowFunctionCodeFeatures;

const InnerArrowFunctionCodeFeatures NoInnerArrowFunctionFeatures =                0;
const InnerArrowFunctionCodeFeatures EvalInnerArrowFunctionFeature =          1 << 0;
const InnerArrowFunctionCodeFeatures ArgumentsInnerArrowFunctionFeature =     1 << 1;
const InnerArrowFunctionCodeFeatures ThisInnerArrowFunctionFeature =          1 << 2;
const InnerArrowFunctionCodeFeatures SuperCallInnerArrowFunctionFeature =     1 << 3;
const InnerArrowFunctionCodeFeatures SuperPropertyInnerArrowFunctionFeature = 1 << 4;
const InnerArrowFunctionCodeFeatures NewTargetInnerArrowFunctionFeature =     1 << 5;

const InnerArrowFunctionCodeFeatures AllInnerArrowFunctionCodeFeatures = EvalInnerArrowFunctionFeature | ArgumentsInnerArrowFunctionFeature | ThisInnerArrowFunctionFeature | SuperCallInnerArrowFunctionFeature | SuperPropertyInnerArrowFunctionFeature | NewTargetInnerArrowFunctionFeature;
} // namespace JSC
