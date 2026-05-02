modded class SCR_BaseGameMode
{
	protected bool m_bABU_OnPlayerRoleChangeActive = false;
	protected bool m_bABU_SkipRespawnOnPlayerKilled = false;

	protected override void OnPlayerKilled(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		m_bABU_SkipRespawnOnPlayerKilled = true;
		super.OnPlayerKilled(playerId, playerEntity, killerEntity, killer);
		m_bABU_SkipRespawnOnPlayerKilled = false;

		if (IsMaster() && m_pRespawnSystemComponent)
			m_pRespawnSystemComponent.OnPlayerKilled_S(playerId, playerEntity, killerEntity, killer);
	}

	protected override void OnPlayerRoleChange(int playerId, EPlayerRole roleFlags)
	{
		if (m_bABU_OnPlayerRoleChangeActive)
		{
			super.OnPlayerRoleChange(playerId, roleFlags);
			return;
		}
		m_bABU_OnPlayerRoleChangeActive = true;
		super.OnPlayerRoleChange(playerId, roleFlags);
		m_OnPlayerRoleChange.Invoke(playerId, roleFlags);
		m_bABU_OnPlayerRoleChangeActive = false;
	}

	protected override void OnControllableDeleted(IEntity entity)
	{
		super.OnControllableDeleted(entity);

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return;
		int playerId = playerManager.GetPlayerIdFromControlledEntity(entity);
		if (playerId > 0)
			OnPlayerDeleted(playerId, entity);
	}
}
