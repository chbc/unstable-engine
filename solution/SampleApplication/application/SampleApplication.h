#pragma once

#include <RenderEngine.h>

using namespace sre;

class SampleApplication : public RenderEngine
{
public:
	~SampleApplication() { }	
protected:
	void onInit() override;
};
