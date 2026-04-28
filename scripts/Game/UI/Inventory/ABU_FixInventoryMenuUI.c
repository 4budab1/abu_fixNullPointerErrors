modded class SCR_InventoryMenuUI
{
	override void MoveBetweenFromVicinity()
	{
		if (!m_pSelectedSlotUI || !m_pSelectedSlotUI.GetInventoryItemComponent() || !m_pSelectedSlotUI.GetInventoryItemComponent().GetOwner())
			return;
		super.MoveBetweenFromVicinity();
	}
}
