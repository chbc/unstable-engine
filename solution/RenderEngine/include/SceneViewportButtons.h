#pragma once

#include <glm/vec2.hpp>

namespace sre
{

class SceneViewportButtons
{
private:
	const char* orientationComboItems[2] = { "Local", "Global" };
	int currentOrientationItem = 0;
	bool backfaceCullingEnabled = true;

public:
	void drawContent(const glm::vec2& windowPos, const glm::vec2& windowSize);

private:
	void drawOrientationItem();
	void drawBackfaceCullingItem();
	void notifyOrientationChanged();
	void refreshBackfaceCulling();
};

} // namespace
