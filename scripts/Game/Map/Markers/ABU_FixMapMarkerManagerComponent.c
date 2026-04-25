modded class SCR_MapMarkerManagerComponent
{
	override void Update(float timeSlice)
	{
		m_MapEntity.GetMapVisibleFrame(m_vVisibleFrameMin, m_vVisibleFrameMax);

		for (int i = m_aStaticMarkers.Count() - 1; i >= 0; i--)
		{
			SCR_MapMarkerBase marker = m_aStaticMarkers[i];
			if (!marker || !marker.GetRootWidget())
			{
				SetStaticMarkerDisabled(marker, true);
				continue;
			}

			if (!marker.OnUpdate(m_vVisibleFrameMin, m_vVisibleFrameMax))
				SetStaticMarkerDisabled(marker, true);
			else
				SetStaticMarkerDisabled(marker, false);
		}

		foreach (SCR_MapMarkerEntity markerEnt : m_aDynamicMarkers)
		{
			if (markerEnt)
				markerEnt.OnUpdate();
		}
	}
}
