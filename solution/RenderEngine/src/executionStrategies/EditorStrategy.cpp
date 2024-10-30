#include "EditorStrategy.h"
#include "RenderEngine.h"
#include "MultimediaManager.h"
#include "WorldEditor.h"

namespace sre
{
EditorStrategy::EditorStrategy()
{
    this->worldEditor = UPTR<WorldEditor>(new WorldEditor{ this->scenesManager });
}

void EditorStrategy::init(RenderEngine* controller)
{
    this->worldEditor->init();
    this->multimediaManager->setEditorMode(true);
}

void EditorStrategy::update(RenderEngine* controller, float elapsedTime)
{
    AExecutionStrategy::update(controller, elapsedTime);
    this->worldEditor->onUpdate(elapsedTime);
}

void EditorStrategy::render(RenderEngine* controller)
{
    AExecutionStrategy::render(controller);
    this->worldEditor->onEditorGUI();
    controller->onEditorGUI();
}

void EditorStrategy::release()
{
    this->worldEditor->release();
}

} // namespace sre
