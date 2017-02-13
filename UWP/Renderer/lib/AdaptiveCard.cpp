#include "pch.h"
#include "AdaptiveCard.h"

#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveCard::RuntimeClassInitialize()
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
        if (m_items == nullptr)
        {
            return E_FAIL;
        }
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::get_ElementType(ElementType* /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::Render(IUIElement** element)
    {
        *element = nullptr;
        return S_OK;
    }
}}