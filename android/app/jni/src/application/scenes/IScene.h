#pragma once

// XXX class SampleApplication;

class IScene
{
public:
	virtual ~IScene() {};

	virtual void onInit(/* SampleApplication* application */) { }
};
