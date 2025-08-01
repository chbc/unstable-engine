#include "EditorStrategy.h"
#include "RenderEngine.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "WorldEditor.h"
#include "Input.h"

namespace sre
{
EditorStrategy::EditorStrategy()
{
    this->worldEditor = UPTR<WorldEditor>(new WorldEditor{ this->scenesManager });
}

void EditorStrategy::init(RenderEngine* controller)
{
    AExecutionStrategy::init(controller);

    this->worldEditor->init();
    this->multimediaManager->setExecutionMode(EExecutionMode::EDITOR);
    this->renderManager->setExecutionMode(EExecutionMode::EDITOR);

    controller->onInitEditor();
}

void EditorStrategy::update(RenderEngine* controller, float elapsedTime)
{
    AExecutionStrategy::update(controller, elapsedTime);
    this->worldEditor->onUpdate(elapsedTime);

#ifdef DEBUG
    if (Input::isKeyJustPressed(KEY_HOME))
        controller->changeStrategy(EExecutionMode::APPLICATION);
#endif
}

void EditorStrategy::render(RenderEngine* controller)
{
    AExecutionStrategy::render(controller);

    this->renderManager->renderGuizmos();
    this->renderManager->unbindFrameBuffer();
    
    bool guiDrawn = this->worldEditor->onEditorGUI();
    controller->onEditorGUI();

    if (guiDrawn)
    {
        this->worldEditor->onGUIEnd();
    }
}

void EditorStrategy::cleanUp()
{
    AExecutionStrategy::cleanUp();
    this->worldEditor->cleanUp();
}

void EditorStrategy::release()
{
    AExecutionStrategy::release();
    this->worldEditor->release();
}

} // namespace sre
