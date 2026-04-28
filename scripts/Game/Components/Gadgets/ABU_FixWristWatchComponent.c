modded class RHS_WristWatchComponent
{
	override void UpdateTime()
	{
		if (!m_wMinuteArrow)
			return;

		super.UpdateTime();
	}

	override void TimeToDegrees()
	{
		if (!m_wUtcArrow)
			return;

		super.TimeToDegrees();
	}

	override void UpdateAltitude()
	{
		if (!m_wAltitude)
			return;

		super.UpdateAltitude();
	}

	override void CycleModes(int direction = 0)
	{
		m_eGarminMode += direction;
		if (m_eGarminMode == 3)
		{
			m_eGarminMode = 0;
		}

		GetGame().GetCallqueue().Remove(UpdateTime);
		GetGame().GetCallqueue().Remove(TimeToDegrees);
		GetGame().GetCallqueue().Remove(UpdateAltitude);
		GetGame().GetCallqueue().Remove(UpdateCompass);
		GetGame().GetCallqueue().Remove(UpdatePosition);

		if (!m_wMainFrame || !m_wCompassFrame || !m_wGpsFrame)
			return;

		if (m_eGarminMode == ERHS_GarminModes.WATCH)
		{
			m_wMainFrame.SetVisible(true);
			m_wCompassFrame.SetVisible(false);
			m_wGpsFrame.SetVisible(false);
			UpdateTime();
			UpdateAltitude();
		}
		else if (m_eGarminMode == ERHS_GarminModes.COMPASS)
		{
			m_wMainFrame.SetVisible(false);
			m_wCompassFrame.SetVisible(true);
			m_wGpsFrame.SetVisible(false);
			UpdateCompass();
		}
		else if (m_eGarminMode == ERHS_GarminModes.GPS)
		{
			m_wMainFrame.SetVisible(false);
			m_wCompassFrame.SetVisible(false);
			m_wGpsFrame.SetVisible(true);
			UpdatePosition();
		}
	}
}
