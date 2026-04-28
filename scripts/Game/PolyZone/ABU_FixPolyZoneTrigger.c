modded class PS_PolyZoneTrigger
{
	override bool ScriptedEntityFilterForQuery(IEntity ent)
	{
		if (!m_polyZone)
			return true;
		if (!m_polyZone.IsInsidePolygon(ent.GetOrigin()))
			return false;

		if (m_bAliveOnly || m_sFactionKey != "" || m_sGroupKey != "")
		{
			SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(ent);
			if (m_sGroupKey != "" && !character)
				return false;

			Vehicle vehicle = Vehicle.Cast(ent);
			SCR_DamageManagerComponent damageManager;
			FactionAffiliationComponent factionAffiliation;
			SCR_AIGroup aiGroup;

			if (vehicle)
			{
				damageManager = vehicle.GetDamageManager();
				factionAffiliation = vehicle.GetFactionAffiliation();
			}

			if (character)
			{
				damageManager = character.GetDamageManager();
				factionAffiliation = character.PS_GetFactionAffiliationComponent();
				aiGroup = character.PS_GetInitialAIGroup();
			}

			if (m_bAliveOnly)
			{
				SCR_DamageManagerComponent fallbackDamageManager = SCR_DamageManagerComponent.Cast(ent.FindComponent(SCR_DamageManagerComponent));
				if (fallbackDamageManager)
					damageManager = fallbackDamageManager;
				if (!damageManager || damageManager.GetState() == EDamageState.DESTROYED)
					return false;
			}

			if (m_sFactionKey != "")
			{
				if (!factionAffiliation)
					return false;
				Faction defaultFaction = factionAffiliation.GetDefaultAffiliatedFaction();
				if (!defaultFaction || defaultFaction.GetFactionKey() != m_sFactionKey)
					return false;
			}

			if (m_sGroupKey != "")
			{
				if (!aiGroup)
					return false;
				if (!aiGroup.GetName().Contains(m_sGroupKey))
					return false;
			}
		}

		return true;
	}
}
