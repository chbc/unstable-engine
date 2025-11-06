#include "SDLAPI.h"
#include "EngineValues.h"
#include "DefaultGameValues.h"
#include "GUIButtonComponent.h"
#include "Entity.h"
#include "Input.h"
#include "FileUtils.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include <windows.h>

namespace sre
{

void SDLAPI::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
		throw this->getError();

    int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw IMG_GetError();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	this->window = SDL_CreateWindow
	(
		EngineValues::APPLICATION_NAME.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT,
		flags
	);

	if (this->window == NULL)
		throw this->getError();

	std::string iconPath = DefaultGameValues::get<std::string>("APPLICATION_ICON");
	SDL_Surface* icon = IMG_Load(iconPath.c_str());
	if (icon)
	{
		SDL_SetWindowIcon(this->window, icon);
		SDL_FreeSurface(icon);
	}

	void *context = SDL_GL_CreateContext(this->window);

	if (context == NULL)
		throw this->getError();

	this->imGuiAPI = UPTR<ImGuiAPI>{ new ImGuiAPI };
	this->imGuiAPI->init(this->window, context);
}

void SDLAPI::onFrameBegin()
{
	this->imGuiAPI->onNewFrame();
}

void SDLAPI::swapBuffers()
{
	this->imGuiAPI->render();
	SDL_GL_SwapWindow(this->window);
}

void SDLAPI::setExecutionMode(EExecutionMode::Type mode)
{
	this->imGuiAPI->setExecutionMode(mode);
}

void SDLAPI::processInput(const std::vector<GUIButtonComponent*>& guiButtons)
{
	SDL_Event currentEvent;

	Input::clearTemporaryInput();
	while (SDL_PollEvent(&currentEvent))
	{
		this->imGuiAPI->processEvent(&currentEvent);
		this->processInput(guiButtons, currentEvent);
	}
}

unsigned int SDLAPI::getTicks()
{
	return SDL_GetTicks();
}

void SDLAPI::delay(unsigned int timeMS)
{
	SDL_Delay(timeMS);
}

void* SDLAPI::loadTexture(const std::string& filePath, uint32_t* outWidth, uint32_t* outHeight, uint8_t* outBpp)
{
	void* result = nullptr;
	std::string absolutePath = FileUtils::getContentAbsolutePath(filePath);
	SDL_Surface* surface = IMG_Load(absolutePath.c_str());

	if (surface == nullptr)
		throw "[SDLAPI] Can't load texture file: " + filePath;

	*outWidth = surface->w;
	*outHeight = surface->h;
	*outBpp = surface->format->BytesPerPixel;

	uint32_t size = surface->pitch * surface->h;
	result = malloc(sizeof(char) * size);
	memcpy(result, surface->pixels, size);

	SDL_FreeSurface(surface);

	return result;
}

void SDLAPI::saveTexture(void* pixels, const char* filePath, uint32_t width, uint32_t height)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, 24, width * 3, SDL_PIXELFORMAT_RGB24);
	
	if (IMG_SavePNG(surface, filePath) != 0)
	{
		throw "[SDLAPI] Couldn't save texture file: " + std::string{ filePath };
	}

	SDL_FreeSurface(surface);
}

void SDLAPI::log(const std::string& type, const std::string& message)
{
	SDL_Log("[%s]: %s", type.c_str(), message.c_str());
}

void SDLAPI::setMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(this->window, x, y);
}

void SDLAPI::showMouseCursor(bool value)
{
	SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
}

void SDLAPI::release()
{
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

void SDLAPI::processInput(const std::vector<GUIButtonComponent*>& guiButtons, SDL_Event& currentEvent)
{
	glm::vec2 position{ 0.0f };

	switch (currentEvent.type)
	{
		case SDL_QUIT:		Input::CloseButton = true; break;
		case SDL_KEYDOWN:	Input::addKey(static_cast<Key>(currentEvent.key.keysym.sym)); break;
		case SDL_KEYUP:		Input::removeKeyDown(static_cast<Key>(currentEvent.key.keysym.sym)); break;

		case SDL_MOUSEMOTION:
			Input::setMousePosition(currentEvent.motion.x, currentEvent.motion.y);
			Input::addMouseDeltaPosition(currentEvent.motion.xrel, currentEvent.motion.yrel);
			break;

		case SDL_MOUSEBUTTONDOWN:
			position = glm::vec2{ currentEvent.button.x, currentEvent.button.y };
			if (guiButtons.empty() || !this->checkButtonPress(guiButtons, position))
				Input::addMouseButton(static_cast<MouseButton>(currentEvent.button.button));
			break;

		case SDL_MOUSEBUTTONUP:
			Input::removeMouseButtonDown(static_cast<MouseButton>(currentEvent.button.button));
			break;

		case SDL_MOUSEWHEEL:
			Input::setMouseWheel(currentEvent.wheel.y);
			break;

		case SDL_DROPFILE:
		{
			FileDropEditorMessage message{ currentEvent.drop.file };
			MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
			messagesManager->notify<FileDropEditorMessage>(&message);
			break;
		}

		case SDL_CONTROLLERDEVICEADDED:
		{
			SDL_JoystickID id = currentEvent.cdevice.which;
			this->sdlControllers[id] = SDL_GameControllerOpen(id);
			Input::addController(id);

			SDL_Log("[MESSAGE] Controller added: (ID: %d)\n", id);
			break;
		}

		case SDL_CONTROLLERDEVICEREMOVED:
		{
			SDL_JoystickID id = currentEvent.cdevice.which;
			if (this->sdlControllers.count(id) > 0)
			{
				SDL_GameControllerClose(this->sdlControllers[id]);
				this->sdlControllers.erase(id);
				Input::removeController(id);

				SDL_Log("[MESSAGE] Controller disconnected: (ID: %d)\n", id);
			}
			break;
		}

		case SDL_CONTROLLERAXISMOTION:
		{
			ControllerInput* controller = Input::getController(currentEvent.caxis.which);
			glm::vec2& analogLeft = controller->analogLeft;
			glm::vec2& analogRight = controller->analogRight;
			glm::vec2& triggers = controller->triggers;

			int axis = currentEvent.caxis.axis;
			int value = currentEvent.caxis.value;

			switch (axis)
			{
				case SDL_CONTROLLER_AXIS_LEFTX:
					analogLeft.x = this->normalizeBidirectionalAxis(value);
					break;
				case SDL_CONTROLLER_AXIS_LEFTY:
					analogLeft.y = -this->normalizeBidirectionalAxis(value);
					break;
				case SDL_CONTROLLER_AXIS_RIGHTX:
					analogRight.x = this->normalizeBidirectionalAxis(value);
					break;
				case SDL_CONTROLLER_AXIS_RIGHTY:
					analogRight.y = -this->normalizeBidirectionalAxis(value);
					break;
				case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
					triggers.x = this->normalizeUnidirectionalAxis(value);
					break;
				case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
					triggers.y = this->normalizeUnidirectionalAxis(value);
					break;
				default: break;
			}

			break;
		}

		case SDL_CONTROLLERBUTTONDOWN:
		{
			ControllerInput* controller = Input::getController(currentEvent.cbutton.which);
			ControllerButton button = static_cast<ControllerButton>(currentEvent.cbutton.button);
			controller->addButtonPress(button);

			break;
		}

		case SDL_CONTROLLERBUTTONUP:
		{
			ControllerInput* controller = Input::getController(currentEvent.cbutton.which);
			ControllerButton button = static_cast<ControllerButton>(currentEvent.cbutton.button);
			controller->removeButtonDown(button);

			break;
		}

		break;

		default: break;
	}
}

bool SDLAPI::checkButtonPress(const std::vector<GUIButtonComponent*>& guiButtons, glm::vec2& pressPosition)
{
	pressPosition.x /= EngineValues::SCREEN_WIDTH;
	pressPosition.y /= EngineValues::SCREEN_HEIGHT;

	bool done = false;

	for (GUIButtonComponent* item : guiButtons)
	{
		bool pressed = false;
		if (!done && item->getEntity()->isEnabled() && item->isInside(pressPosition))
		{
			pressed = true;
			done = true;
		}

		item->setPressed(pressed);
	}

	return false;
}

std::string SDLAPI::getError()
{
	return "SDL Error: " + std::string(SDL_GetError());
}

void SDLAPI::releaseControllers()
{
	for (auto& item : this->sdlControllers)
	{
		SDL_GameControllerClose(item.second);
	}
	this->sdlControllers.clear();
}

float SDLAPI::normalizeBidirectionalAxis(int value)
{
	float result = 0.0f;

	if ((value > CONTROLLER_DEAD_ZONE) || (value < -CONTROLLER_DEAD_ZONE))
	{
		if (value >= 0)
		{
			result = static_cast<float>(value) / MAXSHORT;
		}
		else
		{
			result = static_cast<float>(value) / MINSHORT;
		}
	}

	return result;
}

float SDLAPI::normalizeUnidirectionalAxis(int value)
{
	float result = 0.0f;

	if ((value > CONTROLLER_DEAD_ZONE) || (value < -CONTROLLER_DEAD_ZONE))
	{
		result = static_cast<float>(value) / MAXSHORT;
	}

	return result;
}

bool SDLAPI::openFileDialog(const std::string& title, const char* filter, std::string& outFileName)
{
	return internalFileDialog(title, filter, false, outFileName);
}

bool SDLAPI::saveFileDialog(const std::string& title, const char* filter, std::string& outFileName)
{
	return internalFileDialog(title, filter, true, outFileName);
}

bool SDLAPI::internalFileDialog(const std::string& title, const char* filter, bool save, std::string& outFileName)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	bool result = false;

	if (save)
	{
		ofn.lpstrFile[0] = '\0';
		if (GetSaveFileName(&ofn))
		{
			outFileName = ofn.lpstrFile;
			result = true;
		}
	}
	else if (GetOpenFileName(&ofn))
	{
		outFileName = ofn.lpstrFile;
		result = true;
	}

	return result;
}

void SDLAPI::showMessageBox(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), nullptr);
}

void SDLAPI::showErrorMessageBox(const std::string& title, const std::string& message)
{
	SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), nullptr);
}

} // namespace
