modded class SCR_SpawnRequestComponent
{
	protected override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		if (!GetGame().InPlayMode())
			return;

		SCR_RespawnSystemComponent respawnSystem = SCR_RespawnSystemComponent.GetInstance();
		if (!respawnSystem)
			return;

		if (!m_HandlerComponent)
			m_HandlerComponent = SCR_SpawnHandlerComponent.Cast(respawnSystem.FindComponent(GetHandlerType()));
	}
}
