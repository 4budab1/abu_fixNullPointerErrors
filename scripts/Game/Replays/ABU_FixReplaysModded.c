modded class SCR_EditableVehicleComponent
{
	override void RegisterToReplay(IEntity owner)
	{
		Vehicle vehicle = Vehicle.Cast(owner);
		if (!vehicle)
			return;

		RplComponent rpl = RplComponent.Cast(owner.FindComponent(RplComponent));
		if (!rpl)
			return;

		SCR_VehicleFactionAffiliationComponent factionComponent = SCR_VehicleFactionAffiliationComponent.Cast(owner.FindComponent(SCR_VehicleFactionAffiliationComponent));
		if (!factionComponent)
			return;

		Faction faction = factionComponent.GetDefaultAffiliatedFaction();
		FactionKey factionKey = "";
		if (faction)
			factionKey = faction.GetFactionKey();

		SCR_UIInfo uIInfo = GetInfo();
		string name = "";
		if (uIInfo)
			name = uIInfo.GetName();

		PS_ReplayWriter replayWriter = PS_ReplayWriter.GetInstance();
		if (!replayWriter)
			return;

		RplId rplId = rpl.Id();
		if (vehicle.m_eVehicleType)
		{
			replayWriter.WriteVehicleRegistration(rplId, name, vehicle.m_eVehicleType, factionKey);
		}

		m_iRemoveRpl = rpl.Id();

		GetGame().GetCallqueue().CallLater(PositionLogger, 100, false, rplId, owner);
	}
}

modded class SCR_ChimeraCharacter
{
	override void RegisterToReplay()
	{
		PS_ReplayWriter replayWriter = PS_ReplayWriter.GetInstance();
		if (!replayWriter)
			return;

		RplComponent rpl = RplComponent.Cast(this.FindComponent(RplComponent));
		if (!rpl)
			return;

		SCR_CharacterDamageManagerComponent damageComponent = SCR_CharacterDamageManagerComponent.Cast(this.FindComponent(SCR_CharacterDamageManagerComponent));
		if (!damageComponent)
			return;

		ScriptInvoker damageEvent = damageComponent.GetOnDamageStateChanged();
		if (!damageEvent)
			return;

		damageEvent.Insert(DieLogger);
		replayWriter.WriteCharacterRegistration(rpl.Id(), this);
		GetGame().GetCallqueue().CallLater(PositionLogger, 0, false, rpl.Id());
	}
}
