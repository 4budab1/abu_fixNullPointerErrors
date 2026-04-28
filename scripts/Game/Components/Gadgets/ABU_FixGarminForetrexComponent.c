modded class RHS_GarminForetrexComponent
{
	override void ClearDevice()
	{
		IEntity owner = GetOwner();
		if (!owner || owner.IsDeleted())
		{
			m_wRoot = null;
			m_wRT = null;
			m_CurrentPage = null;
			m_iCurrentPage = 0;
			m_aPages.Clear();
			return;
		}

		super.ClearDevice();
	}
}
