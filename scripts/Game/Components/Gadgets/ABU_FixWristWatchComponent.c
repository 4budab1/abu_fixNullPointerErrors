<<<<<<< Updated upstream
modded class RHS_WristWatchComponent
{
	override void UpdateTime()
	{
		if (!m_wMinuteArrow)
=======
modded class RHS_WristWatchComponent : SCR_GadgetComponent
{
	override protected void UpdateTime()
	{
		if (!m_wMinuteArrow || !m_wHoursArrow || !m_wSecondsArrow || !m_wDay)
>>>>>>> Stashed changes
			return;

		super.UpdateTime();
	}

<<<<<<< Updated upstream
	override void TimeToDegrees()
=======
	override protected void TimeToDegrees()
>>>>>>> Stashed changes
	{
		if (!m_wUtcArrow)
			return;

		super.TimeToDegrees();
	}

<<<<<<< Updated upstream
	override void UpdateAltitude()
=======
	override protected void UpdateAltitude()
>>>>>>> Stashed changes
	{
		if (!m_wAltitude)
			return;

		super.UpdateAltitude();
	}

	override void CycleModes(int direction = 0)
	{
<<<<<<< Updated upstream
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
=======
		if (!m_wMainFrame || !m_wCompassFrame || !m_wGpsFrame)
			return;

		super.CycleModes(direction);
>>>>>>> Stashed changes
	}
}
