//*****************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//*****************************************************************************
//
// Purpose:
//
//*****************************************************************************


class Registry {
public:
	Registry(void);

	void read_reg(void);
	void write_reg(void);

	// Window location and size
	int			manual_x, manual_y;

	// Last used macro
	CString		macro;

	// Popup menu location
	bool		unobstructivePopup;

};

