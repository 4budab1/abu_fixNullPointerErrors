modded class PS_AlivePlayerList
{
	override void FactionButtonClicked(SCR_ButtonBaseComponent playerButton)
	{
		m_wAlivePlayersListScroll.SetSliderPos(0, 0);
		PS_AliveFactionButton aliveFactionButton = PS_AliveFactionButton.Cast(playerButton);
		if (!aliveFactionButton)
			return;
		SCR_Faction faction = aliveFactionButton.GetFaction();
		if (!faction)
			return;

		if (m_aSelectedFactions.Contains(faction))
			m_aSelectedFactions.RemoveItem(faction);
		else
			m_aSelectedFactions.Insert(faction);

		foreach (SCR_AIGroup aiGroup, PS_AlivePlayerGroup alivePlayerGroup : m_aAlivePlayerGroups)
		{
			if (!aiGroup)
				continue;
			SCR_Faction goupFaction = SCR_Faction.Cast(aiGroup.GetFaction());
			bool factionSelected = (goupFaction && m_aSelectedFactions.Contains(goupFaction));
			alivePlayerGroup.GetRootWidget().SetVisible(factionSelected);
		}
	}
}
