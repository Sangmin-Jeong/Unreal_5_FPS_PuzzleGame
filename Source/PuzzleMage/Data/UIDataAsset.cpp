// Puzzle Mage by Arctic Moose Games


#include "UIDataAsset.h"

UTexture2D* UUIDataAsset::GetIcon(EIconType IconType) const
{
	switch (IconType)
	{
		case Select:
			return SelectIcon.LoadSynchronous();
		case Back:
			return BackIcon.LoadSynchronous();
		case TabLeft:
			return TabLeftIcon.LoadSynchronous();
		case TabRight:
			return TabRightIcon.LoadSynchronous();
		default:
			return nullptr;
	}
}

UTexture2D* UUIDataAsset::GetControlSchemeImage() const
{
	return ControlSchemeImage.LoadSynchronous();
}
