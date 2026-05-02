modded class SCR_CampaignBuildingBudgetEditorComponent
{
	override int GetCurrentBudgetValue(EEditableEntityBudget type)
	{
		if (!m_CampaignBuildingComponent)
			return -1;

		return super.GetCurrentBudgetValue(type);
	}
}
