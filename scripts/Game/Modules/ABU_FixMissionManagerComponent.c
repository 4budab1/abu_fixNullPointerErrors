modded class DRG_MissionManagerComponent
{
	override void CreateDescription()
	{
		if (m_MissionDescription)
			return;

		ResourceName startLayout = "{41DAF7B7061DC0BC}UI/MissionDescription/DescriptionEditable.layout";
		Resource descResource = Resource.Load("{3136BE42592F3B1B}PrefabsEditable/MissionDescription/EditableMissionDescription.et");
		m_MissionDescription = PS_MissionDescription.Cast(GetGame().SpawnEntityPrefab(descResource));
		if (!m_MissionDescription)
			return;

		m_MissionDescription.SetTitle("#drg_Modules_MissionParams");
		m_MissionDescription.SetVisibleForEmptyFaction(true);
		m_MissionDescription.RegisterToDescriptionManager();
		m_MissionDescription.SetLayout(startLayout);

		m_MissionDescription.SetShowForAnyFaction(true);
		m_MissionDescription.SetOrder(200);
	}

	static override void FillDescription()
	{
		if (!s_Instance)
			return;

		s_Instance.CreateDescription();

		string description = "";

		foreach (DRG_MissionModuleComponent module : s_Instance.m_MissionModules)
		{
			if (module)
				module.FillDescription(description);
		}

		if (s_Instance.m_MissionDescription)
			s_Instance.m_MissionDescription.SetTextData(description);
	}
}
