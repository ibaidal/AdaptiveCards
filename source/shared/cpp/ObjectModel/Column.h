#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "CollectionTypeElement.h"

namespace AdaptiveSharedNamespace
{
    class BaseActionElement;

    class Column : public BaseCardElement, public CollectionTypeElement
    {
    public:
        Column();

        std::string Serialize() const override;
        Json::Value SerializeToJsonValue() const override;

        static std::shared_ptr<Column> Deserialize(ParseContext& context, const Json::Value& root);

        static std::shared_ptr<Column> DeserializeFromString(ParseContext& context, const std::string& jsonString);

        std::string GetWidth() const;
        void SetWidth(const std::string& value);

        // explicit width takes precedence over relative width
        int GetPixelWidth() const;
        void SetPixelWidth(const int value);

        std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
        const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        void SetLanguage(const std::string& language);

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet() override;
        void SetWidth(const std::string& value,
                      std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>* warnings);

        std::string m_width;
        unsigned int m_pixelWidth;
        std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>> m_items;
        std::shared_ptr<BaseActionElement> m_selectAction;
    };
}
