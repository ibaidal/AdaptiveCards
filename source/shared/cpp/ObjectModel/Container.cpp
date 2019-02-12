#include "pch.h"
#include "Container.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

Container::Container() :
    BaseCardElement(CardElementType::Container), CollectionTypeElement()
{
    PopulateKnownPropertiesSet();
}

const std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems() const
{
    return m_items;
}

std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems()
{
    return m_items;
}

std::shared_ptr<BaseActionElement> Container::GetSelectAction() const
{
    return m_selectAction;
}

void Container::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

void Container::SetLanguage(const std::string& value)
{
    PropagateLanguage(value, m_items);
}

Json::Value Container::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (GetStyle() != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());
    }

    if (GetVerticalContentAlignment() != VerticalContentAlignment::Top)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment)] =
            VerticalContentAlignmentToString(GetVerticalContentAlignment());
    }

    std::string const& itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : m_items)
    {
        root[itemsPropertyName].append(cardElement->SerializeToJsonValue());
    }

    if (m_selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] =
            BaseCardElement::SerializeSelectAction(m_selectAction);
    }

    return root;
}

std::shared_ptr<BaseCardElement> ContainerParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = BaseCardElement::Deserialize<Container>(value);

    container->SetStyle(ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

    container->SetVerticalContentAlignment(ParseUtil::GetEnumValue<VerticalContentAlignment>(
        value, AdaptiveCardSchemaKey::VerticalContentAlignment, VerticalContentAlignment::Top, VerticalContentAlignmentFromString));

    // we walk parse tree using dfs, so we need to save current style,
    // before we walk back up to a parent.
    auto style = context.GetParentalContainerStyle();
    context.SetParentalContainerStyle(container->GetStyle());

    // we set padding when parental style is different from child's
    container->SetPadding(style != container->GetStyle());

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection(context, value, AdaptiveCardSchemaKey::Items, false);
    container->m_items = std::move(cardElements);

    // since we are doing dfs, we have to restore the style before we back up
    context.SetParentalContainerStyle(style);

    // Parse optional selectAction
    container->SetSelectAction(ParseUtil::GetAction(context, value, AdaptiveCardSchemaKey::SelectAction, false));

    return container;
}

std::shared_ptr<BaseCardElement> ContainerParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ContainerParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void Container::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items)});
}

void Container::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto items = GetItems();
    for (auto item : items)
    {
        item->GetResourceInformation(resourceInfo);
    }
    return;
}
