"Resource/UI/DropDownCaption.res"
{
	"PnlBackground"
	{
		"ControlName"			"Panel"
		"fieldName"				"PnlBackground"
		"xpos"					"0"
		"ypos"					"0"
		"zpos"					"-1"
		"wide"					"156"
		"tall"					"105"
		"visible"				"1"
		"enabled"				"1"
		"paintbackground"		"1"
		"paintborder"			"1"
	}

	"BtnHeadphones"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnHeadphones"
		"xpos"					"0"
		"ypos"					"0"
		"wide"					"150"
		"tall"					"20"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"wrap"					"1"
		"navUp"					"Btn5Speakers"
		"navDown"				"Btn2Speakers"
		"labelText"				"#GameUI_Headphones"
		"tooltiptext"			"#GameUI_Headphones"
		"disabled_tooltiptext"	"#GameUI_Headphones"
		"style"					"FlyoutMenuButton"
		"command"				"#GameUI_Headphones"
		"OnlyActiveUser"		"1"
	}
	
	"Btn2Speakers"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"Btn2Speakers"
		"xpos"					"0"
		"ypos"					"20"
		"wide"					"150"
		"tall"					"20"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"wrap"					"1"
		"navUp"					"BtnHeadphones"
		"navDown"				"Btn4Speakers"
		"labelText"				"#GameUI_2Speakers"
		"tooltiptext"			"#GameUI_2Speakers"
		"disabled_tooltiptext"	"#GameUI_2Speakers"
		"style"					"FlyoutMenuButton"
		"command"				"#GameUI_2Speakers"
		"OnlyActiveUser"		"1"
	}
	
	"Btn4Speakers"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"Btn4Speakers"
		"xpos"					"0"
		"ypos"					"40"
		"wide"					"150"
		"tall"					"20"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"wrap"					"1"
		"navUp"					"Btn2Speakers"
		"navDown"				"Btn5Speakers"
		"labelText"				"#GameUI_4Speakers"
		"tooltiptext"			"#GameUI_4Speakers"
		"disabled_tooltiptext" 	"#GameUI_4Speakers"
		"style"					"FlyoutMenuButton"
		"command"				"#GameUI_4Speakers"
		"OnlyActiveUser"		"1"
	}
	
	"Btn5Speakers"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"Btn5Speakers"
		"xpos"					"0"
		"ypos"					"60"
		"wide"					"150"
		"tall"					"20"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"wrap"					"1"
		"navUp"					"Btn4Speakers"
		"navDown"				"Btn7Speakers"
		"labelText"				"#GameUI_5Speakers"
		"tooltiptext"			"#GameUI_5Speakers"
		"disabled_tooltiptext" 	"#GameUI_5Speakers"
		"style"					"FlyoutMenuButton"
		"command"				"#GameUI_5Speakers"
		"OnlyActiveUser"		"1"
	}
	
	"Btn5Speakers"
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"Btn7Speakers"
		"xpos"					"0"
		"ypos"					"80"
		"wide"					"150"
		"tall"					"20"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"wrap"					"1"
		"navUp"					"Btn5Speakers"
		"navDown"				"BtnHeadphones"
		"labelText"				"#GameUI_7Speakers"
		"tooltiptext"			"#GameUI_7Speakers"
		"disabled_tooltiptext" 	"#GameUI_7Speakers"
		"style"					"FlyoutMenuButton"
		"command"				"#GameUI_7Speakers"
		"OnlyActiveUser"		"1"
	}
}
