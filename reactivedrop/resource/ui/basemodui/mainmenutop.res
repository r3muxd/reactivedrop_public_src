"Resource/UI/MainMenuTop.res"
{
	"TopBar"
	{
		"ControlName"			"CRD_VGUI_Main_Menu_Top_Bar"
		"fieldName"				"TopBar"
		"xpos"					"0"
		"ypos"					"0"
		"wide"					"f0"
		"tall"					"32"
		"tabPosition"			"0"
		"PaintBackground"		"1"
		"navLeft"				"BtnSettings"
		"navRight"				"BtnQuit"
		"navUp"					"BtnLogo"
	}

	"BtnSettings"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnSettings"
		"xpos"					"0"
		"ypos"					"0"
		"wide"					"24"
		"tall"					"24"
		"navLeft"				"BtnSettings"
		"navRight"				"BtnLogo"
		"navUp"					"BtnSettings"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				""
		"tooltiptext"			"#L4D360UI_MainMenu_Options_Tip"
		"command"				"Settings"
	}

	"BtnLogo" 
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnLogo"
		"xpos"					"48"
		"ypos"					"0"
		"wide"					"64"
		"tall"					"32"
		"navLeft"				"BtnSettings"
		"navRight"				"BtnLoadout"
		"navUp"					"BtnLogo"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				""
		"command"				"MainMenu"
	}

	"BtnLoadout"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnLoadout"
		"xpos"					"c-168"
		"ypos"					"0"
		"wide"					"64"
		"tall"					"26"
		"navLeft"				"BtnLogo"
		//"navRight"				"BtnContracts"
		"navRight"				"BtnRecordings"
		"navUp"					"BtnLoadout"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				"#rd_collection_inventory_loadout"
		"tooltiptext"			""
		"command"				"Loadout"
	}

	//"BtnContracts"
	//{
	//	"ControlName"			"BaseModHybridButton"
	//	"fieldName"				"BtnContracts"
	//	"xpos"					"c-100"
	//	"ypos"					"0"
	//	"wide"					"64"
	//	"tall"					"26"
	//	"navLeft"				"BtnLoadout"
	//	"navRight"				"BtnRecordings"
	//	"navUp"					"BtnContracts"
	//	"navDown"				"TopBar"
	//	"style"					"ReactiveDropMainMenuTop"
	//	"labelText"				"#rd_mainmenu_contracts"
	//	"tooltiptext"			""
	//	"command"				"Contracts"
	//}

	"BtnRecordings"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnRecordings"
		//"xpos"					"c-32"
		"xpos"					"c-100"
		"ypos"					"0"
		"wide"					"64"
		"tall"					"26"
		//"navLeft"				"BtnContracts"
		"navLeft"				"BtnLoadout"
		"navRight"				"BtnSwarmopedia"
		"navUp"					"BtnRecordings"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				"#rd_mainmenu_recordings"
		"tooltiptext"			""
		"command"				"Recordings"
	}

	"BtnSwarmopedia"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnSwarmopedia"
		//"xpos"					"c36"
		"xpos"					"c-32"
		"ypos"					"0"
		"wide"					"64"
		"tall"					"26"
		"navLeft"				"BtnRecordings"
		"navRight"				"BtnWorkshop"
		"navUp"					"BtnSwarmopedia"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				"#rd_collection_swarmopedia"
		"tooltiptext"			""
		"command"				"Swarmopedia"
	}

	"BtnWorkshop"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnWorkshop"
		//"xpos"					"c104"
		"xpos"					"c36"
		"ypos"					"0"
		"wide"					"64"
		"tall"					"26"
		"navLeft"				"BtnSwarmopedia"
		"navRight"				"BtnInventory"
		"navUp"					"BtnWorkshop"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				"#rd_mainmenu_workshop"
		"tooltiptext"			""
		"command"				"Workshop"
	}

	"BtnInventory"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnInventory"
		//"xpos"					"c172"
		"xpos"					"c104"
		"ypos"					"0"
		"wide"					"64"
		"tall"					"26"
		"navLeft"				"BtnWorkshop"
		"navRight"				"BtnQuit"
		"navUp"					"BtnInventory"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				"#rd_mainmenu_inventory"
		"tooltiptext"			""
		"command"				"Inventory"
	}

	"BtnQuit"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnQuit"
		"xpos"					"r24"
		"ypos"					"0"
		"wide"					"24"
		"tall"					"24"
		"navLeft"				"BtnInventory"
		"navRight"				"BtnQuit"
		"navUp"					"BtnQuit"
		"navDown"				"TopBar"
		"style"					"ReactiveDropMainMenuTop"
		"labelText"				""
		"tooltiptext"			"#L4D360UI_MainMenu_Quit_Tip"
		"command"				"QuitGame"
	}
}
