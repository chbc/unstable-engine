#include "AEditorProperty.h"

bool sre::AEditorProperty::isSaved()
{
    return this->saved;
}

void sre::AEditorProperty::setSaved()
{
    if (!this->saved)
    {
        this->saved = true;
        this->title.pop_back();
    }
}

void sre::AEditorProperty::onValueChanged()
{
    if (this->saved)
    {
        this->saved = false;
        this->title.push_back('*');
    }

    this->onValueChangedCallback();
}
