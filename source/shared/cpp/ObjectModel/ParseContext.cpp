#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveSharedNamespace
{
    ParseContext::ParseContext() :
        elementParserRegistration{std::make_shared<ElementParserRegistration>()},
        actionParserRegistration{std::make_shared<ActionParserRegistration>()},
        elementIds{std::make_shared<std::unordered_set<std::string>>()},
        warnings{},
        m_parentalContainerStyles{}
    {
    }

    ParseContext::ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration, std::shared_ptr<ActionParserRegistration> actionRegistration, std::shared_ptr<std::unordered_set<std::string>> ids) : warnings{}, m_parentalContainerStyles{}
    {
        elementParserRegistration = (elementRegistration) ? elementRegistration : std::make_shared<ElementParserRegistration>();
        actionParserRegistration = (actionRegistration) ? actionRegistration : std::make_shared<ActionParserRegistration>();
        elementIds = (ids) ? ids : std::make_shared<std::unordered_set<std::string>>();
    }

    ContainerStyle ParseContext::GetParentalContainerStyle() const
    {
        return (m_parentalContainerStyles.size())? m_parentalContainerStyles.back() : ContainerStyle::None;
    }

    void ParseContext::PushParentalContainerStyle(const ContainerStyle value)
    {
        m_parentalContainerStyles.push_back(value);
    }

    void ParseContext::PopParentalContainerStyle(void)
    {
        if(m_parentalContainerStyles.size())
        {
            m_parentalContainerStyles.pop_back();
        }
    }
}
