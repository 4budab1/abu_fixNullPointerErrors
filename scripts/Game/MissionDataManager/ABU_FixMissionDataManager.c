modded class PS_MissionDataManager
{
	override void OnDamaged(BaseDamageContext damageContext)
	{
		IEntity target = damageContext.hitEntity;
		Instigator instigator = damageContext.instigator;
		if (target && instigator)
		{
			int playerId = instigator.GetInstigatorPlayerID();
			if (playerId == -1)
				return;

			EntityID entityID = target.GetID();
			if (!m_EntityToRpl.Contains(entityID))
				return;
			RplId rplId = m_EntityToRpl.Get(entityID);

			IEntity instigatorEntity = instigator.GetInstigatorEntity();
			if (!instigatorEntity)
				return;

			GetGame().GetCallqueue().Call(SaveDamageEvent, playerId, rplId, damageContext.damageValue);
		}
	}
}
