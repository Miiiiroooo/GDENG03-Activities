#pragma once
#include "AUITab.h"
#include "DirectXClasses/Texture.h"

class CreditsTab : public AUITab
{
public: 
	CreditsTab();
	~CreditsTab();

	void Render() override;

protected:
	void InitializeImGuiFlags() override;


private:
	Texture* dlsuLogo;
};