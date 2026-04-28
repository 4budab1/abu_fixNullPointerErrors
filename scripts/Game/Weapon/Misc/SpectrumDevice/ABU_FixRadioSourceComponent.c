modded class RHS_RadioSourceComponent
{
	override void Register()
	{
		if (!m_Owner || m_Owner.IsDeleted())
			return;
		if (!RHS_RadioSourcesManagerComponent.GetInstance())
			return;

		m_DamageManagerComponent = SCR_DamageManagerComponent.Cast(GetOwner().FindComponent(SCR_DamageManagerComponent));
		if (m_DamageManagerComponent)
		{
			SCR_HitZone hitZone = SCR_HitZone.Cast(m_DamageManagerComponent.GetDefaultHitZone());
			if (hitZone)
			{
				if (Replication.IsServer())
					hitZone.GetOnDamageStateChanged().Insert(OnDamageStateChanged);
			}
		}

		m_BaseRadioComponent = BaseRadioComponent.Cast(m_Owner.FindComponent(BaseRadioComponent));
		if (!m_BaseRadioComponent)
			return;
		BaseTransceiver radioTransceiver = m_BaseRadioComponent.GetTransceiver(0);
		if (!radioTransceiver || radioTransceiver.IsInherited(IntercomTransceiver))
			return;

		if (Replication.IsServer())
			SetEventMask(m_Owner, EntityEvent.FRAME);
		m_RplComponent = RplComponent.Cast(m_Owner.FindComponent(RplComponent));
		if (!m_RplComponent)
			return;
		m_RplId = m_RplComponent.Id();
		RHS_RadioSourcesManagerComponent.GetInstance().Register(this, m_RplId);
	}
}
