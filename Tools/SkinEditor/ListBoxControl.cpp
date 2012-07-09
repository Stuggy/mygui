/*!
	@file
	@author		Albert Semenov
	@date		07/2012
*/
#include "Precompiled.h"
#include "ListBoxControl.h"

namespace tools
{
	ListBoxControl::ListBoxControl(MyGUI::Widget* _parent) :
		wraps::BaseItemBox<ListBoxItemControl>(_parent)
	{
		assignWidget(mContextMenu, "ContextMenu", false);

		mContextMenu->setVisible(false);
		mContextMenu->eventMenuCtrlAccept += MyGUI::newDelegate(this, &ListBoxControl::notifyMenuCtrlAccept);

		getItemBox()->eventNotifyItem += MyGUI::newDelegate(this, &ListBoxControl::notifyNotifyItem);
		getItemBox()->eventChangeItemPosition += MyGUI::newDelegate(this, &ListBoxControl::notifyChangeItemPosition);
		getItemBox()->eventStartDrag += MyGUI::newDelegate(this, &ListBoxControl::notifyStartDrag);
		getItemBox()->eventRequestDrop += MyGUI::newDelegate(this, &ListBoxControl::notifyRequestDrop);
		getItemBox()->eventDropResult += MyGUI::newDelegate(this, &ListBoxControl::notifyDropResult);
	}

	ListBoxControl::~ListBoxControl()
	{
		mContextMenu->eventMenuCtrlAccept -= MyGUI::newDelegate(this, &ListBoxControl::notifyMenuCtrlAccept);

		getItemBox()->eventNotifyItem -= MyGUI::newDelegate(this, &ListBoxControl::notifyNotifyItem);
		getItemBox()->eventChangeItemPosition -= MyGUI::newDelegate(this, &ListBoxControl::notifyChangeItemPosition);
		getItemBox()->eventStartDrag -= MyGUI::newDelegate(this, &ListBoxControl::notifyStartDrag);
		getItemBox()->eventRequestDrop -= MyGUI::newDelegate(this, &ListBoxControl::notifyRequestDrop);
		getItemBox()->eventDropResult -= MyGUI::newDelegate(this, &ListBoxControl::notifyDropResult);
	}

	void ListBoxControl::setIndexSelected(size_t _value)
	{
		getItemBox()->setIndexSelected(_value);
	}

	void ListBoxControl::removeAllItems()
	{
		getItemBox()->removeAllItems();
	}

	size_t ListBoxControl::getItemCount() const
	{
		return getItemBox()->getItemCount();
	}

	void ListBoxControl::notifyChangeItemPosition(MyGUI::ItemBox* _sender, size_t _index)
	{
		DataType data = nullptr;

		if (_index != MyGUI::ITEM_NONE)
			data = *getItemBox()->getItemDataAt<DataType>(_index);

		eventChangeItemPosition(this, data);
	}

	void ListBoxControl::redrawAllItems()
	{
		getItemBox()->redrawAllItems();
	}

	size_t ListBoxControl::getIndexData(DataType _data) const
	{
		for (size_t index = 0; index < getItemBox()->getItemCount(); index ++)
		{
			if (*getItemBox()->getItemDataAt<DataType>(index) == _data)
				return index;
		}

		return MyGUI::ITEM_NONE;
	}

	void ListBoxControl::removeItem(DataType _data)
	{
		size_t index = getIndexData(_data);
		getItemBox()->removeItemAt(index);
	}

	void ListBoxControl::setItemSelected(DataType _data)
	{
		size_t index = getIndexData(_data);
		getItemBox()->setIndexSelected(index);
	}

	void ListBoxControl::notifyStartDrag(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool& _result)
	{
		_result = true;
	}

	void ListBoxControl::notifyRequestDrop(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool& _result)
	{
		_result = _info.receiver == _info.sender;
	}

	void ListBoxControl::notifyDropResult(MyGUI::DDContainer* _sender, const MyGUI::DDItemInfo& _info, bool _result)
	{
		if (_result)
		{
			if (_info.sender_index != _info.receiver_index)
				eventRelocationItem(this, _info.sender_index, _info.receiver_index);
		}
	}

	void ListBoxControl::removeItemAt(size_t _index)
	{
		getItemBox()->removeItemAt(_index);
	}

	void ListBoxControl::setItemAt(size_t _index, DataType _data)
	{
		getItemBox()->setItemDataAt(_index, _data);
	}

	void ListBoxControl::notifyMenuCtrlAccept(MyGUI::MenuControl* _sender, MyGUI::MenuItem* _item)
	{
		eventCommand(this, _item->getItemId());
	}

	void ListBoxControl::notifyNotifyItem(MyGUI::ItemBox* _sender, const MyGUI::IBNotifyItemData& _info)
	{
		if (_info.notify == MyGUI::IBNotifyItemData::MouseReleased)
		{
			if (_info.id == MyGUI::MouseButton::Right)
			{
				if (mContextMenu->getItemCount() != 0)
				{
					mContextMenu->setPosition(MyGUI::InputManager::getInstance().getLastPressedPosition(MyGUI::MouseButton::Right));
					mContextMenu->setVisibleSmooth(true);
				}
			}
		}
	}
}