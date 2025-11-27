#pragma once

#include "LitRendererNoLightsState.h"

namespace sre
{

class AGraphicsWrapper;

class LitRendererLightsState : public LitRendererNoLightsState
{
private:
    void preDraw(AGraphicsWrapper *graphicsWrapper) override;
    void postDraw(AGraphicsWrapper *graphicsWrapper) override;
};

} // namespace
