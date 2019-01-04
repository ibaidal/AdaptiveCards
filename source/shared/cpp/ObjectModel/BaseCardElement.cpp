#include "pch.h"
#include "BaseCardElement.h"
#include "AdaptiveCardParseException.h"
#include "ParseUtil.h"
#include "ElementParserRegistration.h"
#include "ShowCardAction.h"
#include "OpenUrlAction.h"
#include "SubmitAction.h"

using namespace AdaptiveSharedNamespace;

BaseCardElement::BaseCardElement(CardElementType type, Spacing spacing, bool separator, HeightType height) :
    m_type(type), m_spacing(spacing),
    m_height(height), m_separator(separator), m_isVisible(true)
{
    SetTypeString(CardElementTypeToString(type));
    PopulateKnownPropertiesSet();
}

BaseCardElement::BaseCardElement(CardElementType type) :
    m_type(type), m_spacing(Spacing::Default), m_separator(false),
    m_height(HeightType::Auto), m_isVisible(true)
{
    SetTypeString(CardElementTypeToString(type));
    PopulateKnownPropertiesSet();
}

void BaseCardElement::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Separator),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Spacing)});
}

bool BaseCardElement::GetSeparator() const
{
    return m_separator;
}

void BaseCardElement::SetSeparator(const bool value)
{
    m_separator = value;
}

Spacing BaseCardElement::GetSpacing() const
{
    return m_spacing;
}

void BaseCardElement::SetSpacing(const Spacing value)
{
    m_spacing = value;
}

HeightType BaseCardElement::GetHeight() const
{
    return m_height;
}

void BaseCardElement::SetHeight(const HeightType value)
{
    m_height = value;
}

bool BaseCardElement::GetIsVisible() const
{
    return m_isVisible;
}

void BaseCardElement::SetIsVisible(const bool value)
{
    m_isVisible = value;
}

const CardElementType BaseCardElement::GetElementType() const
{
    return m_type;
}

Json::Value BaseCardElement::SerializeToJsonValue() const
{
    Json::Value root = BaseElement::SerializeToJsonValue();

    if (m_height != HeightType::Auto)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height)] = HeightTypeToString(GetHeight());
    }

    if (m_spacing != Spacing::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Spacing)] = SpacingToString(m_spacing);
    }

    if (m_separator)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Separator)] = true;
    }

    if (!m_isVisible)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsVisible)] = false;
    }

    //SerializeFallbackAndRequires(root);

    return root;
}

Json::Value BaseCardElement::SerializeSelectAction(const std::shared_ptr<BaseActionElement> selectAction)
{
    if (selectAction != nullptr)
    {
        return selectAction->SerializeToJsonValue();
    }
    return Json::Value();
}

void BaseCardElement::ParseJsonObject(AdaptiveSharedNamespace::ParseContext& context, const Json::Value& json, std::shared_ptr<BaseElement>& element)
{
    const std::string typeString = ParseUtil::GetTypeAsString(json);
    std::shared_ptr<BaseCardElementParser> parser = context.elementParserRegistration->GetParser(typeString);

    if (parser == nullptr)
    {
        parser = context.elementParserRegistration->GetParser("Unknown");
    }

    auto parsedElement = parser->Deserialize(context, json);
    if (parsedElement != nullptr)
    {
        element = parsedElement;
        return;
    }

    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Unable to parse element of type " + typeString);
}
